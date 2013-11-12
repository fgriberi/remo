/*
 * @file    Typess.h
 * @brief   This file contains all the definitions needed in proportions table
 *
 * @author   Franco Riberi
 * @email    fgriberi AT gmail.com
 *
 * Contents: Header file providing proportions table definitions.
 *
 * System:   remo: RNAemo - RNA research project
 * Language: C++
 *
 * @date October 28, 2010, 2012 6:42 PM
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

namespace NSBuildFile
{

typedef std::vector<std::string> SplitString;

typedef std::string OptionUsage;

/**
 * @brief to fill with the inputs arguments
 */
struct Arguments
{
        OptionUsage fileNameRNAm;               
        OptionUsage humanizer;        
        size_t organism;
};

/**
 * @brief Represents a bases or nucleotides
 */
enum Nucleotides
{
	NucG, 
	NucC,
	NucA,
	NucT,
	NucCount
};

typedef size_t AmountNucleotide;

typedef std::map<Nucleotides, AmountNucleotide> Result;

}// end namespace
#endif