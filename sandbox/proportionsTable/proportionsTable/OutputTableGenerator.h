/**
 * @file     OutputTableGenerator.h
 * @details  OutputTableGenerator provides the interface for build a output table
 *
 * @author   Franco Riberi
 * @email    fgriberi AT gmail.com
 *
 * Contents: Header file for OutputTableGenerator.
 *
 * System:   remo: RNAemo - RNA research project
 * Language: C++
 *
 * @date    March 26, 2013
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

#ifndef OUTPUT_TABLE_GENERATOR_H
#define OUTPUT_TABLE_GENERATOR_H

#include <fstream>
#include "proportionsTable/Types.h"

namespace NSBuildFile
{

/**
 * @brief Provides the interface for build a output table
 */
class OutputTableGenerator
{
public:

	/**
	 * @brief Represent a file
	 */
	typedef std::string File;

	/**
	 * @brief Constructor of class with parameter
	 *
	 * @param name: file name
	 */
	OutputTableGenerator(const File& name);

	/**
	 * @brief Save current data into a file
	 * 
	 * @param name: sequence name
	 * @param origRes: results obtained in the original sequence 
	 * @param humRes: results obtained in the humanized sequence
	 * @param sizeOrig: size of original sequence
	 * @param sizeHum: size of humanized sequence
	 * @return void
	 */
	void save(const std::string& name, const Result& origRes, const Result& humRes, const size_t sizeOrig, const size_t sizeHum);

private:	
	/**
	 * @brief Generate a header 
	 */
    void generateHeader();

    /**
     * @brief Fill a column
     *
     * @param res: data to load in the column
     * @param return void
     */
    void fillColumn(const Result& res);

    /**
     * @brief Represent a output file
     */
    typedef std::ofstream OutputFile;
    
    OutputFile _outFile;
};

}// end namespace
#endif