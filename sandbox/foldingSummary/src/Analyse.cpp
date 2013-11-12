/**
 * @file     Analyse.cpp
 * @brief    Analyse provides the implementation of analyse interface.
 *
 * @author   Franco Riberi
 * @email    fgriberi AT gmail.com
 *
 * Contents: Source file for Analyse.
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

#include <fstream>
#include <mili/mili.h>
#include <biopp/biopp.h>
#include <biopp-filer/bioppFiler.h>
#include "foldingSummary/Analyse.h"

using mili::operator>>;

namespace NSAnalyse
{

static const size_t F_NAME = 3;

void Analyse::parseFileName(const FileName& fileName, std::string& name)
{
    std::stringstream ss(fileName);
    SplitString result;
    ss >> mili::Separator(result, '|');
    result.size() > F_NAME ? name = result[F_NAME] : name = fileName;
}

void Analyse::processLine(const ResultLine& line, SummaryData& temporalData)
{
	if(line.size() != CountFields)
	{
		std::cout << "Invalid format line." << std::endl;
	}
	else
	{		
		temporalData._microAndMsgSeq = line[MicroNameField];
		mili::from_string(line[ScoreZukOrigField], temporalData._bestOrigScore);
		mili::from_string(line[ScoreZukHumField], temporalData._bestHumScore);
	}
}

void Analyse::updateBestScore(const SummaryData& temporalData, SummaryData& currentBestData)
{
	if(temporalData._bestOrigScore > currentBestData._bestOrigScore)
    {
    	currentBestData._bestOrigScore = temporalData._bestOrigScore;	
    }
    if(temporalData._bestHumScore > currentBestData._bestHumScore)
    {
		currentBestData._bestHumScore = temporalData._bestHumScore;
    }
}
        
static const std::string FILE_NAME = "/tmp/MicroVsRnaMSummary.csv";

void Analyse::processFile(const FileName& fileName, const FileName& nameRNAm, OutputGenerator& outFile)
{	
	File inFile;
	inFile.open(fileName.c_str());
	if(!inFile)
	{
		std::cout << "File not found." << std::endl;
	}
	SummaryData currentBestData;
	SummaryData temporalData;
	std::string oldMicro;
	std::string currentMicro;
	LineContainer fileLine;
	ResultLine resultParseLine;
	bool isFirstMicro = false;
	getline(inFile, fileLine); //title line
    while (getline(inFile, fileLine))    	
    {
    	resultParseLine.clear();
    	std::stringstream ss(fileLine);
        ss >> mili::Separator(resultParseLine, ',');
    
     	currentMicro = resultParseLine[MicroNameField];
    	if(oldMicro == currentMicro)
     	{
     		//only same micro name
     		processLine(resultParseLine, temporalData);    	
	 		updateBestScore(temporalData, currentBestData);
     	}
     	else
     	{    		
     		if(isFirstMicro)
     		{    			
     			outFile.save(currentBestData);    			
     		}     		
			//clear data
     		currentBestData._microAndMsgSeq.clear();
     		currentBestData._bestOrigScore = 0;
     		currentBestData._bestHumScore = 0;

     		currentBestData._microAndMsgSeq = currentMicro + "/" +nameRNAm;	    	
	 		processLine(resultParseLine, temporalData);    	
	 		updateBestScore(temporalData, currentBestData);
	 		isFirstMicro = true;
     	}
    	oldMicro = currentMicro;
    }
    if(oldMicro == currentMicro)
    	outFile.save(currentBestData);    			
}

static const std::string EXTENSION_FILE = ".csv";

void Analyse::startAnalysis(const Arguments& argument)
{
	bioppFiler::FastaParser<biopp::NucSequence> file(argument.fileNameRNAm);

    std::string description;
	biopp::NucSequence origSeq;	
	std::string nameFile;
	OutputGenerator outFile(FILE_NAME.c_str());
	std::string fileToProcess;
	while (file.getNextSequence(description, origSeq))
	{
		parseFileName(description, nameFile);		
		fileToProcess = argument.pathFiles + nameFile + EXTENSION_FILE;	
		processFile(fileToProcess, nameFile, outFile);		
	}   
}

} //end namespace 