/**
 * @file     HumanizedJobDistributable.cpp
 * @brief    This is the implementation of HumanizedJobDistributable interface.
 *
 * @author   Franco Riberi
 * @email    fgriberi AT gmail.com
 *
 * Contents: Source file for remo server providing class HumanizedJobDistributable implementation.
 *
 * System:   remo: RNAemo - RNA research project
 * Language: C++
 *
 * @date     August 2013
 *
 * This file is part of Remo.
 *
 * Copyright (C) 2013 - Franco Riberi, FuDePAN.
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

#include <fstream>
#include <iostream>
#include <mili/mili.h>
#include "CodingSectionObtainer.h"
#include "HumanizedJobDistributable.h"
#include "Exceptions.h"

using namespace fud;
using namespace mili;

HumanizedJobDistributable::HumanizedJobDistributable(const std::string& nameFile, const acuoso::ICodonUsageModifier* humanizer) :
    DistributableJobImplementation(),
    _fileFasta(nameFile.c_str()),
    _nextSequence(true)
{    
    _humanizer = humanizer;
}

//JobUnit
HumanizedJobDistributable::HumJobDistributableJobUnit::HumJobDistributableJobUnit(char* message,JobUnitSize size) :
    JobUnit(),
    _message()
{
    std::string msg(message,size);
    bostream<> bos;
    bos << msg;
    _message = bos.str();
    set_size(size);
}

const char*  HumanizedJobDistributable::HumJobDistributableJobUnit::method_name_required() const
{
    return "humJob";
}

const std::string& HumanizedJobDistributable::HumJobDistributableJobUnit::get_message() const
{
    return _message;
}

const char* HumanizedJobDistributable::get_name() const
{
    return "HumanizedJobDistributable";
}

static const size_t INPUT_SIZE = 3;
static const size_t NAME_SEQUENCE = 0;
static const size_t CT_FILE_CONTENT = 1;
static const size_t DET_FILE_CONTENT = 2;

void HumanizedJobDistributable::parseInput(const std::string& input, ResultLine& output)
{
    std::string accum;    
    for(std::string::const_iterator it = input.begin(); it != input.end(); ++it)    
    {
        if(*it != '@')
        {
            accum += *it;
        }
        else
        {
            output.push_back(accum);
            accum = "";            
        }        
    }
    output.push_back(accum);   
    mili::assert_throw<InvalidSizeInput>(output.size() == INPUT_SIZE);     
}

void HumanizedJobDistributable::stringToFile(const std::string& inputLine, const std::string& nameOutputFile)
{
    std::ofstream file(nameOutputFile.c_str());
    mili::assert_throw<FileNotFound>(file);
    file << inputLine;       
}

static const std::string PREFIX = "hum-";
static const std::string DET = ".det";
static const std::string DIR_PATH = "/tmp/";

void HumanizedJobDistributable::generateFiles(const ResultLine& data)
{
    stringToFile(data[CT_FILE_CONTENT], DIR_PATH + data[NAME_SEQUENCE]); 
    stringToFile(data[DET_FILE_CONTENT], DIR_PATH + data[NAME_SEQUENCE] + DET); 
}

void HumanizedJobDistributable::handle_results (JobUnitID id,InputMessage& input)
{
    std::string inputLine;
    input >> inputLine;
    ResultLine result;
    parseInput(inputLine, result);
    generateFiles(result);
}

void HumanizedJobDistributable::getNameSequence(const std::string& lineToParse, std::string& nameSeq)
{
    std::stringstream ss(lineToParse);    
    ResultLine output;
    ss >> mili::Separator(output, '|');
    nameSeq = output[3];   
}

DistributableJobStatus HumanizedJobDistributable::get_status() const
{ 
    if(_nextSequence)
    {
        return ReadyToProduce;
    }
    else
    {
        return FinishedGenerating;
    }    
}

void HumanizedJobDistributable::replaceHumanizedSection(const biopp::NucSequence& originalSeq, const biopp::NucSequence& humanizedSeq,
                                                        const size_t initNucIndex, biopp::NucSequence& toFoldSeq)
{
    toFoldSeq = originalSeq;
    for (size_t i = 0; i < humanizedSeq.length(); i++)
    {
        toFoldSeq[i + initNucIndex] = humanizedSeq[i];
    }
}

void HumanizedJobDistributable::getHumanizedSequence(const biopp::NucSequence& origSeq, biopp::NucSequence& humanizedSeq)
{
    biopp::AminoSequence aminoSequence;
    biopp::NucSequence humRnaM;
    size_t initIndex;
    CodingSectionObtainer helper;
    helper.getCodingSection(origSeq, aminoSequence, initIndex);
    _humanizer->changeCodonUsage(aminoSequence, humRnaM);
    replaceHumanizedSection(origSeq, humRnaM, initIndex, humanizedSeq);
}

JobUnit* HumanizedJobDistributable::produce_next_job_unit(JobUnitSize size)
{
    JobUnit* ret = NULL;
    if (get_status() != FinishedGenerating)
    {
        std::string description;
        biopp::NucSequence sequence;
        if(_fileFasta.getNextSequence(description, sequence))
        {
            biopp::NucSequence humanizedSeq;
            getHumanizedSequence(sequence, humanizedSeq);

            std::string nameSeq;
            getNameSequence(description, nameSeq);       
            std::string dataToClient = PREFIX + nameSeq; 
            dataToClient += '@';
            dataToClient += humanizedSeq.getString();
            dataToClient += '@';
            dataToClient += "true";

            char* message = new char[dataToClient.length() + 1];
            strcpy(message, dataToClient.c_str());

            //message: "nameSeq" + '@' + "sequence" + '@' + "isCirc"
            JobUnit* res = new HumJobDistributableJobUnit(message, dataToClient.length()); /// VER DE MANDAR EL SIZE CORRECTO        
            delete[] message;
            ret = res;
        }
        else
        {
            _nextSequence = false;
        }           
    }
    return ret;
}