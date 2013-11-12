/**
 * @file:     OutputGenerator.cpp
 * @brief     This is the implementation of OutputGenerator interface.
 *
 * author     Franco Riberi
 * @email     fgriberi AT gmail.com
 *
 * Contents:  Source file providing OutputGenerator implementation.
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


#include <iostream>
#include "foldingSummary/OutputGenerator.h"

namespace NSAnalyse
{

OutputGenerator::OutputGenerator(const File& name)
{
	if (_outFile)
    {
        _outFile.close();
    }
    _outFile.open(name.c_str());
    if(!_outFile)
    {
        std::cout << "File not created." << std::endl;
    }
    generateHeader();
}


void OutputGenerator::generateHeader()
{
	_outFile << "miRna/RNAm,";    
    _outFile << " BestScoreOrig ";    
    _outFile << " , BestScoreHun " << std::endl;
}

void OutputGenerator::save(const SummaryData& currentBestData)
{
    _outFile << currentBestData._microAndMsgSeq;
    _outFile << ", ";
    _outFile << currentBestData._bestOrigScore;
    _outFile << ", ";
    _outFile << currentBestData._bestHumScore;    
    _outFile << std::endl;
}

} // end namespace