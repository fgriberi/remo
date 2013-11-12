/**
 * @file     BuildFile.h
 * @details  BuildFile provides the interface for build a output file with the proportions of unions AT and GC
 *
 * @author   Franco Riberi
 * @email    fgriberi AT gmail.com
 *
 * Contents: Header file for BuildFile.
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

#ifndef BUILD_FILE_H
#define BUILD_FILE_H

#include <string>
#include <biopp/biopp.h>
#include <acuoso/acuoso.h>
#include <getoptpp/getopt_pp.h>
#include <biopp-filer/bioppFiler.h>
#include "proportionsTable/Types.h"

namespace NSBuildFile
{

/**
 * @brief Build a output file with the proportions of unions AT and GC
 *
 */
class BuildFile
{
public:

	/**
     * @brief Build file
     * 
     * @param argument: inputs arguments
     * @return void
     */
	static void startBuild(const Arguments& argument);

private:	

	/**
     * @brief Counts the numbers of bases (AT, GC)
     * 
     * @param file: sequences containers
     * @param humanizer: backend to use for humanized
     * @return void
     */
	static void countBases(bioppFiler::FastaParser<biopp::NucSequence>& file, const acuoso::ICodonUsageModifier* humanizer);

	/** @brief Replaces the coding section
     *
     * Replaces in the original sequence, the largest subsequence humanized
     * @param originalSeq: original sequence
     * @param humanizedSeq: larger humanized subsequence    
     * @param initNucIndex: starting position to begin the replacement
     * @param toFoldSeq: to fill the originalSeq with humanizedSeq
     * @return void
     */
	static void replaceHumanizedSection(const biopp::NucSequence& originalSeq, const biopp::NucSequence& humanizedSeq,
                                        const size_t initNucIndex, biopp::NucSequence& toFoldSeq);
   
    /** @brief Get humanized sequence
     *
     * @param origSeq: original sequence     
     * @param humanizer: specific backend to humanize
     * @param humanizedSeq: to fill with humanized sequence
     * @return void
     */
    static void getHumanizedSequence(biopp::NucSequence& origSeq, const acuoso::ICodonUsageModifier* humanizer,
                                     biopp::NucSequence& humanizedSeq);

    /**
     * @brief Process current sequence
     * 
     * @param seq: current sequence to process 
     * @param result: container to fill with the sequences
     * @return void
     */    
    static void processSequence(const biopp::NucSequence& seq, Result& result);

	/**
     * @brief Add base in the container
     * 
     * @param base: current base (A, G, C, T)
     * @param result: container load the base
     * @return void
     */    
    static void addBase(char base, Result& result);

	/** @brief Parser file name
     *
     * @param fileName: description of fasta file
     * @param name: file name
     * @return void
     */
	static void parseFileName(const std::string& fileName, std::string& name);
	
	/**
     * @brief Clear container
     * 
     * @param result: container for clear
     * @return void
     */
	static void clearResultMap(Result& result);

	/**
     * @brief Controls the amount of processed nucleotides
     * 
     * @param res: container where stored processed bases
     * @param seq: original sequence
     * @return true whether the amount of bases is the same, otherwise false
     */
	static bool checkNucleotidAmount(const Result& res, const std::string& seq);
};

}// end namespace
#endif