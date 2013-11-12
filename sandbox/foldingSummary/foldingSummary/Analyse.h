/**
 * @file     Analyse.h
 * @brief    Analyse provides the interface to analyse the inputs files
 *
 * @author   Franco Riberi
 * @email    fgriberi AT gmail.com
 *
 * Contents: Header file for Analyse.
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

#ifndef ANALYSE_H
#define ANALYSE_H

#include <vector>
#include "foldingSummary/OutputGenerator.h"
#include "foldingSummary/Types.h"

namespace NSAnalyse
{

/**
 * @brief Represents a input option
 */
typedef std::string OptionType;

/**
 * @brief To fill with input options
 */
struct Arguments
{
    OptionType fileNameRNAm;                   
    OptionType pathFiles;
};

/**
 * @brief Parse and analyse a inputs files
 */
class Analyse
{
public:

	/**
	 * @brief
	 */
	typedef std::vector<std::string> ResultLine;
			
	/**
	 * @brief Begin analisis of inputs files (csv files produced for Remo) 
	 * @param argument contain input options
	 * @retun void
	 */
    void startAnalysis(const Arguments& argument);

private:

	/**
	 * @brief Represents a file line
	 */
	typedef std::string LineContainer;

	/**
	 * @brief Represents file name
	 */
	typedef std::string FileName;

	/**
	 * @breif Represents a input file
	 */
	typedef std::ifstream File;

	/**
	 * @brief Represents the fields of a file line
	 */
	enum FieldFile
	{
		MicroNameField,
		IndexField,
		MatchingOrgField,
		MaskedOrigField,
		OthersOrigField,
		UpperCaseCountOrigField,
		MaskedCountOrigField,
		MatchingHumField,
		MaskedHumField,
		OthersHumField,
		UpperCaseCountHumField,
		MaskedCountHumField,
		ScoreZukOrigField,
		ScoreZukHumField,
		CountFields
	};

	/**
	 * @brief Represents a field of output file
	 */
	enum ResultField
	{
		MicroName,
		ScoreOrig,
		ScoreHum,
		Count
	};

	/**
	 * @brief
	 */
	typedef std::vector<std::string> SplitString;

	/**
	 * @brief Process a current line
	 *
	 * @param line: current line of file
	 * @param temporalData: to fill with important information from line
	 * @return void
	 */
	void processLine(const ResultLine& line, SummaryData& temporalData);	

	/**
	 * @brief Compare data and get the major information
	 *
	 * @param temporalData: contain information if current line
	 * @param currentBestData: contain the best data
	 * @return void
	 */
	void updateBestScore(const SummaryData& temporalData, SummaryData& currentBestData);

	/**
	 * @brief Parse a description file name and obtain real name
	 * @param fileName: complete description of file name 
	 * @param name: to fill  with real name
	 * @return void
	 */
	void parseFileName(const FileName& fileName, std::string& name);

	/**
	 * @brief Process a file
	 *
	 * @param fileName: input file name
	 * @param nameRNAn: input file name without .cvs extensions
	 * @return void
	 */
	void processFile(const FileName& fileName, const FileName& nameRNAm, OutputGenerator& outFile);

	/**
	 * @brief To load summary data
	 */
	SummaryData _summaryData;
};

} // end namespace 

#endif
