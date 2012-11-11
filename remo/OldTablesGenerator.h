/**
 *  @file:      OldTablesGenerator.h
 *  @details    System: R-emo \n
 *              Language: C++\n
 *  @author     Franco Riberi
 *
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

#ifndef OLD_TABLES_GENERATOR_H
#define OLD_TABLES_GENERATOR_H

#include <string>
#include <fstream>
#include "biopp/biopp.h"
#include "biopp-filer/bioppFiler.h"
#include "remo/ICodonUsageModifier.h"
#include "remo/TablesGenerator.h"

class OldTablesGenerator : public TablesGenerator
{
    /**
     * Enumerated type representing unions
     */
    enum PairedType
    {
        Unpaired, auType, cgType, guType, othersType, typeCount
    };

    /**
    * Method that determines the type of union considering secondary structure
    * @param index in the sequence
    * @param secondary structure of sequence
    * @param sequence
    * @return type of union
    */
    static PairedType get_pairedType(biopp::SeqIndex i, const biopp::SecStructure& structure, const biopp::NucSequence& sequence);

    /**
    * Method that determines the type of union between two nucleotidados
    * @param nucleotide
    * @param nucleotide
    * @return type of union
    */
    static PairedType get_ComplementType(const biopp::Nucleotide n1, const biopp::Nucleotide n2);

    typedef size_t PairedTypeArray[typeCount];

    /**
    * Method that determines the amount of paired
    * @param secondary structure of messenger ARN
    * @param sequence of ARN
    * @param index in the sequence
    * @param
    * @return
    */
    static void countPaired(const biopp::SecStructure& structure, const biopp::NucSequence& sequence, size_t microStart, size_t microRnaLength, PairedTypeArray& pCount);

    /**
    * Method that determines the amount of paired
    * @param sequence of messenger ARN
    * @param sequence of microARN
    * @param index in the sequence
    * @param
    * @return
    */
    static void countPaired(const biopp::NucSequence& rnamSequence, const biopp::NucSequence& microSequence, size_t microStart, PairedTypeArray& pCount);

    /**
     * Allows comparison between two nucleotides
     */
    struct Comp
    {
        const biopp::Nucleotide nuc1;
        const biopp::Nucleotide nuc2;

        Comp(biopp::Nucleotide n1, biopp::Nucleotide n2) : nuc1(n1), nuc2(n2) {}

        bool compare(biopp::Nucleotide c1, biopp::Nucleotide c2) const
        {
            return ((nuc1 == c1 && nuc2 == c2) || (nuc1 == c2 && nuc2 == c1));
        }
    };

    class IndexConverter
    {
        const size_t seqRNAmSize;
        const bool circ;
        const size_t microRNASize;

    public:
        /**
         * Class constructor
         */
        IndexConverter(const size_t seqSize, bool isCirc, size_t mirnaSize)
            : seqRNAmSize(seqSize), circ(isCirc), microRNASize(mirnaSize)
        {}

        /**
         * Method that calculates the maximum position to move into messenger RNA
         * @return Maximum index possible in the messenger RNA sequence
         */
        inline size_t getMaxPos() const;

        /**
         * Converting index depending on whether the sequence is circular or not.
         * @param index in the sequence
         * @return idx if less than the size of the sequence, otherwise, if is circula, idx - size of the sequence
         */
        inline size_t convertIndex(size_t idx) const;
    };

public:
    /**
     * Method that populates a file by rows
     */
    void generate(const TableData& td);

    /**
     * Method that append one sequence of miRNA in table. For position.
     */
    void appendMicro(const TableData& td);

    /**
     * Method that prints the header files
     */
    void generateHeader();

    /**
     * Method that generates a full row for a file
     * @param sequence of original messenger ARN
     * @param sequence of humanized messenger ARN
     * @param sequence of microRNA
     * @param secondary structure of original messenger ARN
     * @param secondary structure of humanized messenger ARN
     * @param
     * @param index in the sequence
     * @return
     */
    void generateTableRow(const std::string nameMicro, const biopp::NucSequence& RNAm, const biopp::NucSequence& rnaHumanized, const biopp::NucSequence& miRNA, const biopp::SecStructure& secondaryStructureRNAm, const biopp::SecStructure& secondaryStructureHum, IndexConverter& idxConvert, const size_t miRnaStart);

    /**
     * Method that generates a row with the desired sequences 3
     * @param sequence of messenger ARN
     * @param sequence of microRNA
     * @param secondary structure of messenger ARN
     * @param
     * @param index in the sequence
     * @return
     */
    void generateSequencesGroupRow(const biopp::NucSequence& sequenceRNA, const biopp::NucSequence& miRNA, const biopp::SecStructure& secondaryStructure, const IndexConverter& converter, const size_t miRnaStart);

    /**
     * Method that shows in uppercase one nucleotide as appropriate.
     * @param nucleotide of microARN
     * @param nucleotide of messenger ARN
     * @return uppercase, if matching nucleotides, otherwise lowercase
     */
    static char column1Seq(const biopp::Nucleotide nucMiRNA, const biopp::Nucleotide nucRNAm);

    /**
     * Method masking a nucleotide
     * @param nucleotide of microARN
     * @param nucleotide of messenger ARN
     * @param is paired nucleotide of messenger ARN in the secondary structure
     * @return 'M' if matching nucleotides and the nucleotide of rnam. is paired
     */
    static char column2Seq(const biopp::Nucleotide nucMiRNA, const biopp::Nucleotide nucRNAm, bool isMsgPaired);

    /**
     * Method that shows the nucleotide not available through XYZ from type of union
     * @param index in sequence
     * @param secondary structure of sequence
     * @param sequence of messenger ARN
     * @return 'X' if A=U; 'Y' if G=C; 'Z' if G=C; otherwise '?' (A=G,C=T, A=C)
     */
    static char column3Seq(size_t index, const biopp::SecStructure& structure, const biopp::NucSequence& sequence);

    /**
     * Method that generate score using zuker values
     * @param secundary structure of messenger ARN
     * @param sequence of messenger ARN
     * @param sequence of microARN
     * @param position where begin the comparison
     * @return
     */
    void generateScoreColumn(const biopp::SecStructure& structure, const biopp::NucSequence& seqRna, const biopp::NucSequence& microRna, const size_t microStart);

};
#endif /* OLD_TABLES_GENERATOR_H */
