/**
 * @file     OriginalJobDistributable.cpp
 * @brief    This is the implementation of OriginalJobDistributable interface.
 *
 * @author   Franco Riberi
 * @email    fgriberi AT gmail.com
 *
 * Contents: Source file for remo server providing class OriginalJobDistributable implementation.
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
#include "Exceptions.h"
#include "OriginalJobDistributable.h"

using namespace fud;
using namespace mili;

OriginalJobDistributable::OriginalJobDistributable(const std::string& nameFile) :
    DistributableJobImplementation(),
    _fileFasta(nameFile.c_str()),
    _nextSequence(true)
{}
  
//JobUnit
OriginalJobDistributable::OrigJobDistributableJobUnit::OrigJobDistributableJobUnit(char* message,JobUnitSize size) :
    JobUnit(),
    _message()
{
    std::string msg(message,size);
    bostream<> bos;
    bos << msg;
    _message = bos.str();
    set_size(size);
}

const char*  OriginalJobDistributable::OrigJobDistributableJobUnit::method_name_required() const
{
    return "origJob";
}

const std::string& OriginalJobDistributable::OrigJobDistributableJobUnit::get_message() const
{
    return _message;
}

const char* OriginalJobDistributable::get_name() const
{
    return "OriginalJobDistributable";
}

static const size_t INPUT_SIZE = 3;
static const size_t NAME_SEQUENCE = 0;
static const size_t CT_FILE_CONTENT = 1;
static const size_t DET_FILE_CONTENT = 2;

void OriginalJobDistributable::parseInput(const std::string& input, ResultLine& output)
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

void OriginalJobDistributable::stringToFile(const std::string& inputLine, const std::string& nameOutputFile)
{
    std::ofstream file(nameOutputFile.c_str());
    mili::assert_throw<FileNotFound>(file);
    file << inputLine;       
}

static const std::string PREFIX = "orig-";
static const std::string DET = ".det";
static const std::string DIR_PATH = "/tmp/";

void OriginalJobDistributable::generateFiles(const ResultLine& data)
{    
    stringToFile(data[CT_FILE_CONTENT], DIR_PATH + data[NAME_SEQUENCE]);     
    stringToFile(data[DET_FILE_CONTENT], DIR_PATH + data[NAME_SEQUENCE] + DET); 
}

void OriginalJobDistributable::handle_results (JobUnitID id,InputMessage& input)
{
    std::string inputLine;
    input >> inputLine;
    ResultLine result;
    parseInput(inputLine, result);
    generateFiles(result);
}

void OriginalJobDistributable::getNameSequence(const std::string& lineToParse, std::string& nameSeq)
{
    std::stringstream ss(lineToParse);    
    ResultLine output;
    ss >> mili::Separator(output, '|');
    nameSeq = output[3];   
}

DistributableJobStatus OriginalJobDistributable::get_status() const
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


JobUnit* OriginalJobDistributable::produce_next_job_unit(JobUnitSize size)
{    
    JobUnit* ret = NULL;
    if (get_status() != FinishedGenerating)
    { 
        std::string description;
        biopp::NucSequence sequence;
        if(_fileFasta.getNextSequence(description, sequence))
        {
            std::string nameSeq;
            getNameSequence(description, nameSeq);       
            std::string dataToClient = PREFIX + nameSeq; 
            dataToClient += '@';
            dataToClient += sequence.getString();
            dataToClient += '@';
            dataToClient += "true";
    
            char* message = new char[dataToClient.length() + 1];
            strcpy(message, dataToClient.c_str());

            //message: nameSeq + @ + seq + @ + circ
            JobUnit* res = new OrigJobDistributableJobUnit(message, dataToClient.length()); /// VER DE MANDAR EL SIZE CORRECTO            
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