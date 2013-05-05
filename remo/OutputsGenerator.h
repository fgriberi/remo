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

#include <biopp-filer/bioppFiler.h>
#include "remo/TablesGenerator.h"

using namespace fideo;

class OutputsGenerator
{
public:
    /**
     * Replace humanized section
     * @param
     * @param
     * @param
     * @param
     */
    static void replaceHumanizedSection(const biopp::NucSequence& originalSeq, const biopp::NucSequence& humanizedSeq, biopp::NucSequence& toFoldSeq, size_t initNucIndex);

    /**
     * Generator output files
     * @param fasta file of messenger ARN
     * @param fasta file of microARN
     * @param sequence is circular (flag)
     * @param instance of humanizer
     * @param instance of folder
     * @return
     */
    static void generateOutput(bioppFiler::FastaParser<biopp::NucSequence>& fileRNAm, bioppFiler::FastaParser<biopp::NucSequence>& fileMiRNA, ICodonUsageModifier* humanizer, TablesGenerator* tGen, bool circ);

private:
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
};

#endif /* OUTPUTS_GENERATOR_H */
