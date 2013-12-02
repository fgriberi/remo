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
#include <acuoso/acuoso.h>
#include "remo/OutputsGenerator.h"
#include "remo/Exceptions.h"
#include "remo/CodingSectionObtainer.h"

using mili::operator>>;

namespace remo
{

const size_t OutputsGenerator::NAME = 3;
const size_t OutputsGenerator::SIZE_TO_MICRO_NAME = 2;
const size_t OutputsGenerator::CANT_NUC = 3;
const size_t OutputsGenerator::NAME_MICRO = 1;

void OutputsGenerator::parseFileName(const std::string& fileName, std::string& name)
{
    std::stringstream ss(fileName);
    SplitString result;
    ss >> mili::Separator(result, '|');
    result.size() > NAME ? name = result[NAME] : name = fileName;
}

void OutputsGenerator::parseNameMicro(const std::string& microDescription, std::string& name)
{
    std::stringstream ss(microDescription);
    SplitString result;
    ss >> result;
    mili::assert_throw<InvalidDescriptionMiRNA>(result.size() == SIZE_TO_MICRO_NAME);
    name = result[NAME_MICRO];
}


void OutputsGenerator::replaceHumanizedSection(const biopp::NucSequence& originalSeq, const biopp::NucSequence& humanizedSeq,
        const size_t initNucIndex, biopp::NucSequence& toFoldSeq)
{
    toFoldSeq = originalSeq;
    for (size_t i = 0; i < humanizedSeq.length(); i++)
    {
        toFoldSeq[i + initNucIndex] = humanizedSeq[i];
    }
}

void OutputsGenerator::getHumanizedSequence(biopp::NucSequence& origSeq, const acuoso::ICodonUsageModifier* humanizer, biopp::NucSequence& humanizedSeq)
{
    biopp::AminoSequence aminoSequenceRNAm;
    biopp::NucSequence humRnaM;
    size_t initIndex;
    CodingSectionObtainer helper;
    helper.getCodingSection(origSeq, aminoSequenceRNAm, initIndex);
    //humanized correct sequence sequence
    humanizer->changeCodonUsage(aminoSequenceRNAm, humRnaM);
    replaceHumanizedSection(origSeq, humRnaM, initIndex, humanizedSeq);
}

bool OutputsGenerator::validateSizeOfSequece(const biopp::NucSequence& /*sequence*/, const std::string& /*description*/)
{
    /*****************************************************************************************
    * Temporarily obsolete lines because sequences are already in the correct reading frame  *
    ******************************************************************************************/
    /*  
    bool ret;
    if ((sequence.length() % CANT_NUC) != 0)
    {
        std::cout << "\n Invalid size in sequence: " << description << std::endl;
        ret = false;
    }
    else
    {
        ret = true;
    }
    return ret;
    */
    return true;
}

void OutputsGenerator::generateOutput(bioppFiler::FastaParser<biopp::NucSequence>& fileRNAm, const bool circ,
                                      bioppFiler::FastaParser<biopp::NucSequence>& fileMiRNA,
                                      const acuoso::ICodonUsageModifier* humanizer, const bool dontFold, TablesGenerator* tGen)
{
    biopp::NucSequence origRNAm;
    biopp::NucSequence humRnaM;
    biopp::NucSequence newHumanizedSeq;
    std::string tableName;
    biopp::NucSequence microRNA;
    std::string nameMicro;
    std::string description;    
    fileRNAm.reset();
    while (fileRNAm.getNextSequence(description, origRNAm))
    {
        if (validateSizeOfSequece(origRNAm, description))
        {
            getHumanizedSequence(origRNAm, humanizer, newHumanizedSeq);
            std::string microDescription;
            parseFileName(description, tableName);
            tableName += ".csv";
            tGen->_dontFold = dontFold;
            tGen->generate(tableName, origRNAm, newHumanizedSeq, circ);
            while (fileMiRNA.getNextSequence(microDescription, microRNA))
            {
                parseNameMicro(microDescription, nameMicro);
                tGen->appendMicro(microRNA, nameMicro);
            }
            fileMiRNA.reset();
        }
    }
}

} // namespace remo