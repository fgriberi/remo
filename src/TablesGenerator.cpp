/**
 *  @file:      TablesGenerator.cpp
 *  @details    Generator tables.\n
 *              System: R-emo \n
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

#include "remo/Definitions.h"
#include "remo/TablesGenerator.h"

using namespace biopp;
using namespace std;
using namespace biopp;

//Zuker const
static const DeltaG ZUKER_AU = -2;
static const DeltaG ZUKER_GC = -3;

inline size_t TablesGenerator::IndexConverter::getMaxPos() const
{
    return circ ? seqRNAmSize - 1 :  seqRNAmSize - microRNASize;
}

inline size_t TablesGenerator::IndexConverter::convertIndex(size_t idx) const
{
    size_t ret;
    if (idx < seqRNAmSize)
        ret = idx;
    else
    {
        assert(circ);
        assert(idx < seqRNAmSize + microRNASize);
        ret = idx - seqRNAmSize;
    }
    return ret;
}

void TablesGenerator::generateHeader()
{
    oFile << "Index ," ;
    oFile << "MatchingOrg ," ;
    oFile << "MaskedOrig ,";
    oFile << "XYZ?Orig ,";
    oFile << "upperCaseCountOrig ,";
    oFile << "mCountOrig ,";
    oFile << "MatchingHum ,";
    oFile << "MaskedHum ,";
    oFile << "XYZ?Hum ,";
    oFile << "upperCaseCountHum ,";
    oFile << "mCountHum ,";
    oFile << "ScoreZukOrig ,";
    oFile << "ScoreZukHum" << endl;
}

void TablesGenerator::generateSequencesGroupRow(const NucSequence& sequenceRNA, const NucSequence& miRNA, const SecStructure& secondaryStructure, const IndexConverter& converter, const size_t miRnaStart)
{
    string col1;
    string col2;
    string col3;
    char col1Char;
    char col2Char;
    size_t uppercaseCount = 0;
    size_t mCount = 0;
    for (size_t i = 0; i < miRNA.length(); ++i)
    {
        const size_t idx = converter.convertIndex(i + miRnaStart);
        col1Char = column1Seq(miRNA[idx], sequenceRNA[idx]);
        if (col1Char == toupper(col1Char))
    		uppercaseCount++;
	    col1 += col1Char;

        col2Char = column2Seq(miRNA[idx], sequenceRNA[idx], secondaryStructure.is_paired(i));
    	if (col2Char == 'M')
	    	mCount++;
    	col2 += col2Char;

        col3 += column3Seq(idx, secondaryStructure, sequenceRNA);
    }
    oFile << col1 << "," << col2 << "," << col3 << "," << uppercaseCount << "," << mCount;
}

void TablesGenerator::generateScoreColumn(const SecStructure& structureRNA, const NucSequence& seqRna, const NucSequence& microRna, const size_t microStart)
{
    PairedTypeArray counterMsgMsg;
    PairedTypeArray counterMsgMicro;

    countPaired(structureRNA, seqRna, microStart, microRna.length(), counterMsgMsg);
    countPaired(seqRna, microRna, microStart, counterMsgMicro);

    DeltaG col =  ZUKER_AU * (DeltaG(counterMsgMicro[auType]) - DeltaG(counterMsgMsg[auType])) +  ZUKER_GC * (DeltaG(counterMsgMicro[cgType]) - DeltaG(counterMsgMsg[cgType]));

    if (col != -0.0)
        oFile << col;
    else
        oFile << 0;
}

void TablesGenerator::generateTableRow(const NucSequence& RNAm, const NucSequence& rnaHumanized, const NucSequence& miRNA, const SecStructure&       secondaryStructureRNAm, const SecStructure& secondaryStructureHum, IndexConverter& idxConvert, const size_t miRnaStart)
{
    oFile << miRnaStart + 1;
    oFile << ",";
    generateSequencesGroupRow(RNAm, miRNA, secondaryStructureRNAm, idxConvert, miRnaStart);
    oFile << ",";
    generateSequencesGroupRow(rnaHumanized, miRNA, secondaryStructureHum, idxConvert, miRnaStart);
    oFile << ",";
    generateScoreColumn(secondaryStructureRNAm, RNAm, miRNA, miRnaStart);
    oFile << ",";
    generateScoreColumn(secondaryStructureHum, rnaHumanized, miRNA, miRnaStart);
    oFile << endl;
}

char TablesGenerator::column1Seq(const Nucleotide nucMiRNA, const Nucleotide nucRNAm)
{
    char ret;
    if (nucMiRNA == nucRNAm)
        ret = toupper(nucRNAm.as_char());
    else
        ret = tolower(nucRNAm.as_char());
    return ret;
}

char TablesGenerator::column2Seq(const Nucleotide nucMiRNA, const Nucleotide nucRNAm, bool isMsgPaired)
{
    char ret;
    if (nucMiRNA == nucRNAm)
    {
        if (isMsgPaired)
        {
            ret = 'M';
        }
        else
        {
            ret = toupper(nucRNAm.as_char());
        }
    }
    else
        ret = tolower(nucRNAm.as_char());
    return ret;
}

TablesGenerator::PairedType TablesGenerator::get_pairedType(SeqIndex i, const biopp::SecStructure& structure, const biopp::NucSequence& sequence)
{
    PairedType ret;
    if (!structure.is_paired(i))
        ret = Unpaired;
    else
    {
        Comp c(sequence[i], sequence[structure.paired_with(i)]);
        if (c.compare(Nucleotide(Nucleotide::A), Nucleotide(Nucleotide::U)))
            ret = auType;
        else if (c.compare(Nucleotide(Nucleotide::C), Nucleotide(Nucleotide::G)))
            ret = cgType;
        else if (c.compare(Nucleotide(Nucleotide::G), Nucleotide(Nucleotide::U)))
            ret = guType;
        else
            ret = othersType;
    }
    return ret;
}

TablesGenerator::PairedType TablesGenerator::get_ComplementType(const biopp::Nucleotide n1, const biopp::Nucleotide n2)
{
    PairedType ret;
    Comp c(n1, n2);
    if (c.compare(Nucleotide(Nucleotide::A), Nucleotide(Nucleotide::U)))
        ret = auType;
    else if (c.compare(Nucleotide(Nucleotide::C), Nucleotide(Nucleotide::G)))
        ret = cgType;
    else if (c.compare(Nucleotide(Nucleotide::G), Nucleotide(Nucleotide::U)))
        ret = guType;
    else
        ret = Unpaired;
    return ret;
}

char TablesGenerator::column3Seq(size_t index, const SecStructure& structure, const NucSequence& sequence)
{
    const PairedType pType = get_pairedType(index, structure, sequence);
    char ret;
    switch (pType)
    {
        case Unpaired :
            ret = sequence[index].as_char();
            break;
        case auType :
            ret = 'X';
            break;
        case cgType :
            ret = 'Y';
            break;
        case guType :
            ret = 'Z';
            break;
        case othersType :
            ret = '?';
            break;
        default:
            assert(false);
    }
    return ret;
}

void TablesGenerator::countPaired(const SecStructure& structure, const NucSequence& sequence, size_t microStart, size_t microRnaLength, PairedTypeArray& pCount)
{
    for (size_t i = 0; i < typeCount; ++i)
    {
        pCount[i] = 0;
    }
    for (size_t i = 0; i < microRnaLength; ++i)
    {
        pCount[get_pairedType(i + microStart, structure, sequence)]++;
    }
}

//Should disappear in iteracion4. The hybridization provides structure between mRNA and microRNA
void TablesGenerator::countPaired(const NucSequence& rnamSequence, const NucSequence& microSequence, size_t microStart, PairedTypeArray& pCount)
{
    for (size_t i = 0; i < typeCount; ++i)
    {
        pCount[i] = 0;
    }
    const size_t indexMax = microSequence.length();
    Nucleotide nucComp;
    for (size_t i = 0; i < indexMax; ++i)
    {
        nucComp = microSequence[i];
        nucComp.complement();
        pCount[get_ComplementType(nucComp, rnamSequence[i + microStart])]++;
    }
}

void TablesGenerator::generate(const TableData& td)
{
    assert(td.rnaM.length() == td.rnaMHumanized.length());
    assert(td.structRNAm.size() == td.structHumanized.size());

    oFile.open(td.tableName.c_str());
    if (!oFile)
        throw "Can't create output file.";
    IndexConverter cIndex(td.rnaM.length(), td.circ, td.miRna.length()); 
    NucSequence mirnaCompl(td.miRna);
    mirnaCompl.complement();
    const size_t maxIndex = cIndex.getMaxPos();
    generateHeader();
    for (size_t i = 0; i < maxIndex ; ++i)
    {
        generateTableRow(td.rnaM, td.rnaMHumanized, mirnaCompl, td.structRNAm, td.structHumanized, cIndex, i);
    }
    oFile.close();
}
