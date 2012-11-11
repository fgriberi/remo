/**
 *  @file:      OutputsGenerator.h
 *  @details    System: R-emo \n
 *              Language: C++\n
 *
 *  @author     Franco Riberi
 *  @email      fgriberi AT gmail.com
 *
 *  @date       October 2012
 *  @version    1.0
 *
 * This file is part of R-emo.
 *
 * Copyright (C) 2012 - Franco Riberi, FuDePAN.
 *
 * R-emo is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * R-emo is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with R-emo. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef OUTPUTS_GENERATOR_H
#define OUTPUTS_GENERATOR_H

#include <string>
#include "biopp/biopp.h"
#include "fideo/fideo.h"
#include "biopp-filer/bioppFiler.h"
#include "remo/ICodonUsageModifier.h"

class OutputsGenerator
{
    /**
     * Parser file name
     * @param description of fasta file
     * @return file name
     */
    static std::string parseFileName(const std::string& fileName);

    /**
     * Parser miRNA name
     * @param name of miRNA sequence
     * @return name sequence
     */
    static std::string parseNameMicro(const std::string& microDescription);

    /**
     * File Name Generator
     * @param file name of messenger ARN
     * @param number of microARN
     * @return complete file name to generate
     */
    static std::string generateTableName(const std::string& RNAmName, size_t n);

public:

    /**
     * Generator output files
     * @param fasta file of messenger ARN
     * @param fasta file of microARN
     * @param sequence is circular (flag)
     * @param instance of humanizer
     * @param instance of folder
     * @return
     */
    static void generateOutput(bioppFiler::FastaParser<biopp::NucSequence>& fileRNAm, bioppFiler::FastaParser<biopp::NucSequence>& fileMiRNA, bool circ, ICodonUsageModifier* humanizer, IFold* folder, size_t org);

    static void generateOutput(bioppFiler::FastaParser<biopp::NucSequence>& fileRNAm, bioppFiler::FastaParser<biopp::NucSequence>& fileMiRNA, bool circ, ICodonUsageModifier* humanizer, IHybridize* hybrid, size_t org);

    /**
     *
     * @param
     * @param
     */
    static void getCodingSection(const biopp::NucSequence& src, biopp::AminoSequence& dest, size_t& i, size_t& j);

    /**
     *
     * @param
     * @param
     */
    static void reemplazeSectionHumanized(const biopp::NucSequence& originalSeq, const biopp::NucSequence&  humanizedSeq, biopp::NucSequence& toFoldSeq, size_t initIndex, size_t finalIndex);
};
#endif /* OUTPUTS_GENERATOR_H */
