/**
 * @file      PreFold.cpp
 * @brief     Provide the implements of pre-fold of sequence.
 *
 * @author    Franco Riberi
 * @email     fgriberi AT gmail.com
 *
 * Contents:  Source file for remo providing PreFold implementation.
 *
 * System:    remo: RNAemo - RNA research project
 * Language:  C++
 *
 * @date      October 2012
 *
 * This file is part of Remo.
 *
 * Copyright (C) 2012 - Franco Riberi, FuDePAN.
 *
 * Remo is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Remo is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Remo. If not, see <http://www.gnu.org/licenses/>.
 *
 */
#include <memory>
#include <etilico/etilico.h>
#include "remo/PreFold.h"
#include "remo/OutputsGenerator.h"
#include "remo/Exceptions.h"

/** @brief Temporal methods to execute remo
 *
 */
fideo::IFold* getDerivedFold(const std::string& derivedKey);

namespace remo
{

static const std::string BACKEND_TO_FOLD = "UNAFold";
static const etilico::DirectoryPath DIRECTORY = "/tmp/";

PreFold::PreFold()
{
    _folderImpl = getDerivedFold(BACKEND_TO_FOLD);
    etilico::getCurrentPath(_currentPath);
}

PreFold::~PreFold()
{
    delete _folderImpl;
    mili::assert_throw<InvalidPathChdir>(chdir(_currentPath.c_str()) == 0);
}

void PreFold::preFoldSpecificSequence(biopp::NucSequence& sequence, const bool isCirc, const std::string& nameOutputFile, biopp::SecStructure& structure)
{
    fideo::FilePath fileToFill = DIRECTORY + nameOutputFile;
    _folderImpl->foldTo(sequence, isCirc, structure, fileToFill);
}

static const std::string PREFIX_ORIG = "orig-";
static const std::string PREFIX_HUM = "hum-";

void PreFold::prefold(bioppFiler::FastaParser<biopp::NucSequence>& fileRNAm, const bool circ, const acuoso::ICodonUsageModifier* humanizer)
{
    biopp::NucSequence originalSequence;
    biopp::NucSequence humanizedSequence;
    biopp::SecStructure structureOrig;
    biopp::SecStructure structureHumanized;
    std::string description;
    std::string fileName;
    while (fileRNAm.getNextSequence(description, originalSequence))
    {
        if (OutputsGenerator::validateSizeOfSequece(originalSequence, description))
        {
            OutputsGenerator::parseFileName(description, fileName);

            //prefold original sequence
            preFoldSpecificSequence(originalSequence, circ, PREFIX_ORIG + fileName, structureOrig);

            //obtain humanized sequence
            OutputsGenerator::getHumanizedSequence(originalSequence, humanizer, humanizedSequence);

            //prefold humanized sequence
            preFoldSpecificSequence(humanizedSequence, circ, PREFIX_HUM + fileName, structureHumanized);
        }
    }
}

} //namespace remo