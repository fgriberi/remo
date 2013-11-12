/*
 * @file    Typess.h
 * @brief   This file contains all the definitions needed in folding summary
 *
 * @author   Franco Riberi
 * @email    fgriberi AT gmail.com
 *
 * Contents: Header file providing folding summary definitions.
 *
 * System:   remo: RNAemo - RNA research project
 * Language: C++
 *
 * @date October 27, 2010, 2012 6:42 PM
 *
 * Copyright (C) 2010  Franco Riberi, FuDePAN
 *
 * This file is part of Remo
 *
 * Remo is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Remo is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Remo.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
 
#ifndef TYPES_H
#define TYPES_H

#include <map>
#include <vector>

namespace NSAnalyse
{

/**
 * @brief Represents sequences analized
 */
typedef std::string MicroAndMsgSeq;

/**	
 * @brief Represents the best score of original sequence
 */
typedef int BestOrigScore;

/**	
 * @brief Represents the best score of humanized sequence
 */
typedef int BestHumScore;

struct Result
{
	MicroAndMsgSeq _microAndMsgSeq;
	BestOrigScore _bestOrigScore;
	BestHumScore _bestHumScore;
};

/**
 * @brief Represents a container to important data
 */
typedef Result SummaryData;

}// end namespace

#endif
