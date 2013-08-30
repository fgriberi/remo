/**
 * @file     FoldProcessor.cpp
 * @brief    Is the implementation of FoldProcessor interface
 *
 * @author   Franco Riberi
 * @email    fgriberi AT gmail.com
 *
 * Contents: Source file for remo client providing FoldProcessor implementation.
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
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Remo. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <string>
#include <fstream>
#include <unistd.h>
#include <mili/mili.h>
#include <etilico/etilico.h>
#include <biopp/biopp.h>
#include <stdlib.h>     
#include <time.h>
#include "FoldProcesor.h"
#include "Exceptions.h"

using namespace fud;

fideo::IFold* getDerivedFold(const std::string& derivedKey);

const std::string FoldProcessor::_backend = "UNAFold";
const std::string FoldProcessor::_det = ".det";

FoldProcessor::FoldProcessor() :
    ClientProcessor()
{
    _folder = getDerivedFold(_backend.c_str());
}

FoldProcessor::~FoldProcessor()
{
    delete _folder;
}


static const size_t INPUT_SIZE = 3;
void FoldProcessor::parseInput(const std::string& input, ResultLine& result)
{
    std::stringstream ss(input);    
    ss >> mili::Separator(result, '@');
    mili::assert_throw<InvalidSizeInput>(result.size() == INPUT_SIZE);
}

void FoldProcessor::processSequence(const std::string& sequence, fideo::FilePath& nameOutputFile)
{   
    biopp::NucSequence seq(sequence);
    biopp::SecStructure structure;
    const bool isCirc = true;
    _folder->foldTo(seq, isCirc, structure, nameOutputFile);    
}

void FoldProcessor::fileToString(const std::string& nameFile, std::string& outputData)
{
    std::ifstream file(nameFile.c_str());
    mili::assert_throw<FileNotFound>(file);
    std::string currentLine;
    while(getline(file, currentLine))
    {
        outputData += currentLine;
        outputData += '\n';
    }
}

void FoldProcessor::buildOutput(const std::string& nameSeq, const std::string& nameFile, std::string& output)
{
    output = nameSeq;
    output += '@';        
    fileToString(nameFile, output); //.ct file content     
    output += '@';        
    fileToString(nameFile + _det, output); //.det file content  
    mili::assert_throw<UnlinkException>(unlink(nameFile.c_str()) == 0);    
    mili::assert_throw<UnlinkException>(unlink((nameFile + _det).c_str()) == 0);    
}

static const size_t NAME_SEQUENCE = 0;
static const size_t SEQUENCE = 1;
static const std::string DIR_TMP = "/tmp/";

/**
 * Input format => "nameSeq" + '@'' + "sequence" + '@' + "isCirc"
 */
bool FoldProcessor::process(InputMessage& input, OutputMessage& output)
{
    std::string inputLine;
    input  >> inputLine;

    ResultLine data;
    parseInput(inputLine, data);

    std::string prefix = "fideo-XXXXXX";
    std::string temporalFile;
    etilico::createTemporaryFile(temporalFile, DIR_TMP, prefix);
    processSequence(data[SEQUENCE], temporalFile); 

    std::string outputLine;
    buildOutput(data[NAME_SEQUENCE], temporalFile, outputLine);
    output << outputLine;    
    return true;
}