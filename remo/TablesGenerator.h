/**
 *  @file:      TablesGenerator.h
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with R-emo .  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef TABLES_GENERATOR_H
#define TABLES_GENERATOR_H

#include <string>
#include <fstream>
#include "biopp/biopp.h"
#include "biopp-filer/bioppFiler.h"
#include "remo/IHumanizer.h"

class TablesGenerator
{
    enum PairedType
    {
        Unpaired, auType, cgType, guType, othersType
    };
    static PairedType get_pairedType(biopp::SeqIndex i, const biopp::SecStructure& structure, const biopp::NucSequence& sequence);

    class IndexConverter
    {
        const size_t seqSize;
        const bool circ;
        const size_t microRNASize;

    public:
        IndexConverter(const size_t seqSize, bool isCirc, size_t mirnaSize)
            : seqSize(seqSize), circ(isCirc), microRNASize(mirnaSize)
        {}

        inline size_t getMaxPos() const;
        inline size_t convertIndex(size_t idx) const;
    };

    std::ofstream oFile;

public:
    struct TableData
    {
        std::string tableName;
        biopp::NucSequence rnaM;
        biopp::NucSequence rnaMHumanized;
        biopp::NucSequence miRna;
        bool circ;
        biopp::SecStructure structRNAm;
        biopp::SecStructure structHumanized;
    };

    //completa una ffila
    void generate(const TableData& td);

    void generateHeader();

    //completa columna por grupo de una fila
    void generateTableRow(const biopp::NucSequence& rna_m, const biopp::NucSequence& rna_humanized, const biopp::NucSequence& mi_rna, const biopp::SecStructure& secondary_structure_rnam, const biopp::SecStructure& secondary_structure_hum, IndexConverter& idxConvert, const size_t mirna_start);

    void generateSequencesGroupRow(const biopp::NucSequence& sequence, const biopp::NucSequence& mi_rna, const biopp::SecStructure& secondary_structure, const IndexConverter& converter, const size_t mirna_start);
    void generateScoresGroupRow(biopp::NucSequence& sequence);

    static char column1Seq(const biopp::Nucleotide nuc_mi_rna, const biopp::Nucleotide nuc_rna_m);
    static char column2Seq(const biopp::Nucleotide nuc_mi_rna, const biopp::Nucleotide nuc_rna_m, bool isMsgPaired);

    //se muestran los nucleotidos no disponibles mediante XYZ, segun el tipo de union
    // [A=U -> 'W', G=C -> 'X', G=U -> 'Y', resto (A=G,C=T, A=C) Z]
    static char column3Seq(size_t i, const biopp::SecStructure& structure, const biopp::NucSequence& sequence);

//    static double calculateScore(const std::string& sequence, const int constAT, const DeltaG constGT);


    double scoreByPercentage(const biopp::NucSequence& sequence);
    double scoreByZuker(const biopp::NucSequence& sequence);
    int countNucleotid(const std::string& sequence, const char nucleotid);
};
#endif /* TABLES_GENERATOR_H */
