/**
 * @file     OutputGenerator.h
 * @brief    OutputGenerator provides the interface to get the output file result
 *
 * @author   Franco Riberi
 * @email    fgriberi AT gmail.com
 *
 * Contents: Header file for OutputGenerator.
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

#ifndef OUTPUT_GENERATOR_H
#define OUTPUT_GENERATOR_H

#include <fstream>
#include "foldingSummary/Types.h"

namespace NSAnalyse
{

class OutputGenerator
{
public:

	/**
	 * @brief Represents a File
	 */
	typedef std::string File;

	/**
	 * @brief Constructor of class with parameter
	 * @param name: name of file
	 */
	OutputGenerator(const File& name);

	/**
	 * @brief Save a current data in a file
	 * @param currentBesrData: to save in a file
	 * @return void	
	 */
	void save(const SummaryData& currentBestData);

private:

	/**
	 * @brief Generate a header of file
	 */
	void generateHeader();

	/**
	 * @brief Represents a output file
	 */
    typedef std::ofstream OutputFile;

    OutputFile _outFile;

};

} // end namespace 

#endif 
