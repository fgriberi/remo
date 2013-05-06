/**
 * @file:     OutputsGenerator.cpp
 * @brief     This is the implementation of OutputGenerator interface.
 *
 * author     Franco Riberi
 * @email     fgriberi AT gmail.com
 *
 * Contents:  Source file for remo providing OutputGenerator implementation.
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
 * but WITHOUT ANY WARRANTY; w  ithout even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Remo. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <sstream>
#include <fideo/fideo.h>
#include "remo/OutputsGenerator.h"
#include "remo/ICodonUsageModifier.h"
#include "remo/Exceptions.h"
#include "remo/CodingSectionObtainer.h"

using namespace mili;

typedef std::vector<std::string> Result;

std::string OutputsGenerator::parseFileName(const std::string& fileName)
{
    std::stringstream ss(fileName);
    Result result;
    ss >> mili::Separator(result, '|');
    std::string ret;
    if (result.size() > 3)
    {
        ret = result[3];
    }
    else
    {
        ret = fileName;
    }
    return ret;
}

std::string OutputsGenerator::parseNameMicro(const std::string& microDescription)
{
    std::stringstream ss(microDescription);
    Result result;
    ss >> result;
    if (result.size() != 2)
    {
        throw RemoTools::InvalidDescriptionMiRNA();
    }
    else
    {
        return result[1];
    }
}

void OutputsGenerator::replaceHumanizedSection(const biopp::NucSequence& originalSeq, const biopp::NucSequence& humanizedSeq, const size_t initNucIndex, biopp::NucSequence& toFoldSeq)
{
    toFoldSeq = originalSeq;
    for (size_t i = 0; i < humanizedSeq.length(); i++)
    {
        toFoldSeq[i + initNucIndex] = humanizedSeq[i];
    }
}

void OutputsGenerator::generateOutput(bioppFiler::FastaParser<biopp::NucSequence>& fileRNAm, bool circ, bioppFiler::FastaParser<biopp::NucSequence>& fileMiRNA, ICodonUsageModifier* humanizer, TablesGenerator* tGen)
{
    biopp::NucSequence origRNAm;
    biopp::NucSequence humRnaM;
    biopp::NucSequence newHumanizedSeq;
    std::string tableName;
    biopp::NucSequence microRNA;
    std::string nameMicro;
    std::string description;
    size_t initIndex;
    CodingSectionObtainer helper;
    while (fileRNAm.getNextSequence(description, origRNAm))
    {
        if ((origRNAm.length() % 3) != 0)
        {
            std::cout << "\n Invalid size in sequence: " << description << std::endl;
        }
        else
        {
            biopp::AminoSequence aminoSequeRNAm;

            helper.getCodingSection(origRNAm, aminoSequeRNAm, initIndex);

            //humanized correct sequence sequence
            humanizer->changeCodonUsage(aminoSequeRNAm, humRnaM);

            replaceHumanizedSection(origRNAm, humRnaM, initIndex, newHumanizedSeq);

            std::string microDescription;
            tableName = parseFileName(description) + "csv"; //.csv
            tGen->generate(tableName, origRNAm, newHumanizedSeq, circ);
            while (fileMiRNA.getNextSequence(microDescription, microRNA))
            {
                nameMicro = parseNameMicro(microDescription);
                tGen->appendMicro(microRNA, nameMicro);
            }
            fileMiRNA.reset();
        }
    }
}