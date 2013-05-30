/**
 * @file     OutputsGenerator.h
 * @brief    OutputsGenerator provides the interface to get the output files results
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

#ifndef OUTPUTS_GENERATOR_H
#define OUTPUTS_GENERATOR_H

#include <acuoso/acuoso.h>
#include <biopp-filer/bioppFiler.h>
#include "remo/TablesGenerator.h"

namespace remo
{

/** @briel Class that provides the interface to get the output files results
*
*/
class OutputsGenerator
{
public:

    /** @brief Replaces the coding section
     *
     * Replaces in the original sequence, the largest subsequence humanized
     * @param originalSeq: original sequence
     * @param humanizedSeq: larger humanized subsequence
     * @param toFoldSeq: to fill the originalSeq with humanizedSeq
     * @param initNucIndex: starting position to begin the replacement
     * @return void
     */
    static void replaceHumanizedSection(const biopp::NucSequence& originalSeq, const biopp::NucSequence& humanizedSeq,
                                        const size_t initNucIndex, biopp::NucSequence& toFoldSeq);

    /** @brief Get humanized sequence
     *
     * @param origSeq: original sequence 
     * @param humanizedSeq: to fill with humanized sequence
     * @param humanizer: specific backend to humanize
     * @return void
     */
    static void getHumanizedSequence(biopp::NucSequence& origSeq, const acuoso::ICodonUsageModifier* humanizer, 
                                     biopp::NucSequence& humanizedSeq);

    /** @brief Generates output files of remo project
     *
     * @param fileRNAm: fasta file of messenger RNA sequences
     * @param fileMiRNA: fasta file of microRNA sequences
     * @param humanizer: concrete instance of ICodonUsageModifier
     * @param tGen: instance of service (folder or hybridize)
     * @param circ: sequence is circular
     * @return void
     */
    static void generateOutput(bioppFiler::FastaParser<biopp::NucSequence>& fileRNAm, const bool circ,
                               bioppFiler::FastaParser<biopp::NucSequence>& fileMiRNA,
                               const acuoso::ICodonUsageModifier* humanizer, TablesGenerator* tGen);

    /** @brief Generates output files of remo project
     *
     * @param fileRNAm: fasta file of messenger RNA sequences
     * @return true if size of sequence is correct, otherwise false
     */
    static bool validateSizeOfSequece(const biopp::NucSequence sequence, const std::string& description);
    
private:

    typedef std::vector<std::string> Result;

    /** @brief Parser file name
     *
     * @param description of fasta file
     * @return file name
     */
    static void parseFileName(const std::string& fileName, std::string& name);

    /** @brief Parser miRNA name
     *
     * @param name of miRNA sequence
     * @return name sequence
     */
    static void parseNameMicro(const std::string& microDescription, std::string& name);
};

} // namespace remo
#endif /* OUTPUTS_GENERATOR_H */