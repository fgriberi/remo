/**
 *  @file:      TablesGenerator.cpp
 *  @details    Main file.\n
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with R-emo .  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "remo/Definitions.h"
#include "remo/TablesGenerator.h"

using namespace biopp;
using namespace std;

static const int unsigned PERCENTAGE_AU = 1;
static const int unsigned PERCENTAGE_GC = 1;

static const DeltaG ZUKER_AU = -2;
static const DeltaG ZUKER_GC = -3;

using namespace std;       
using namespace biopp;       

inline size_t TablesGenerator::IndexConverter::getMaxPos() const 
{
    return circ ? seqSize - 1 :  seqSize - microRNASize;
}

inline size_t TablesGenerator::IndexConverter::convertIndex(size_t idx) const
{
    size_t ret;
    if (idx < seqSize)
        ret = idx;
    else
    {
        assert(circ);
        assert(idx < seqSize + microRNASize);
        ret = idx - seqSize;
    }
    return ret;
}


void TablesGenerator::generateHeader()
{
    oFile << "Index" << "," ;

    oFile << "MatchingOrg ," ;
    oFile << "MaskedOrig ,";
    oFile << "XYZ?Orig ,";

    oFile << "MatchingHum ,";
    oFile << "MaskedHum ,";
    oFile << "XYZ?Hum" << endl;

//    oFile << "Score%Orig ," ;
//    oFile << "ScoreZukOrig ,";
//    oFile << "Score%OrigMask ,";
//    oFile << "ScoreZukOrigMask ,";

//    oFile << "Score%Hum ," ;
//    oFile << "ScoreZukHum ,";
//    oFile << "Score%HumMask ,";
//    oFile << "ScoreZukHumMask" << endl;
}

void TablesGenerator::generateSequencesGroupRow(const NucSequence& sequence, const NucSequence& mi_rna, const SecStructure& secondary_structure, const IndexConverter& converter, const size_t mirna_start)
{
    string col1;
    string col2;
    string col3;
    for(size_t i = 0; i < mi_rna.length(); ++i)
    {   
        const size_t idx = converter.convertIndex(i + mirna_start);
        col1 += column1Seq(mi_rna[idx], sequence[idx]);    
        col2 += column2Seq(mi_rna[idx], sequence[idx], secondary_structure.is_paired(i));
        col3 += column3Seq(idx, secondary_structure, sequence);        
    }
    oFile << col1 << "," << col2 << "," << col3;
}

//void generateScoresGroupRow(biopp::NucSequence& sequence)
//{
//}


void TablesGenerator::generateTableRow(const NucSequence& rna_m, const NucSequence& rna_humanized, const NucSequence& mi_rna, const SecStructure&       secondary_structure_rnam, const SecStructure& secondary_structure_hum, IndexConverter& idxConvert, const size_t mirna_start)
{        
    oFile << mirna_start;
    oFile << ",";    
    generateSequencesGroupRow(rna_m, mi_rna, secondary_structure_rnam, idxConvert, mirna_start);
    oFile << ",";    
    generateSequencesGroupRow(rna_humanized, mi_rna, secondary_structure_hum, idxConvert, mirna_start);
//    oFile << ",";    
//    generateScoresGroupRow(rna_m);
//    oFile << ",";    
//    generateScoresGroupRow(rna_humanized);
    oFile << endl;
}

char TablesGenerator::column1Seq(const Nucleotide nuc_mi_rna, const Nucleotide nuc_rna_m)
{
    char ret;
    if (nuc_mi_rna == nuc_rna_m)
        ret = toupper(nuc_rna_m.as_char());
    else
        ret = tolower(nuc_rna_m.as_char());
    return ret;
}

char TablesGenerator::column2Seq(const Nucleotide nuc_mi_rna, const Nucleotide nuc_rna_m, bool isMsgPaired)
{
    char ret;
    if (nuc_mi_rna == nuc_rna_m)
    {
        if (isMsgPaired)
        {
            ret = 'M';    
        }
        else
        {
            ret = toupper(nuc_rna_m.as_char());
        }
    }
    else
        ret = tolower(nuc_rna_m.as_char());    
    return ret;
}

TablesGenerator::PairedType TablesGenerator::get_pairedType(SeqIndex i, const biopp::SecStructure& structure, const biopp::NucSequence& sequence)
{    
    struct Comp
    {
        const Nucleotide n1;
        const Nucleotide n2;
        Comp(Nucleotide n1, Nucleotide n2) : n1(n1), n2(n2) {}

        bool compare(Nucleotide c1, Nucleotide c2) const
        {
            return ((n1 == c1 && n2 == c2) || (n1 == c2 && n2 == c1));
        }          
    };

    PairedType ret;
    if (!structure.is_paired(i))
        ret = Unpaired;
    else
    {
//        Nucleotide nucleotideCompl(sequence[i]);
//        nucleotideCompl.complement();
        Comp c(sequence[i], sequence[structure.paired_with(i)]);
        if (c.compare(Nucleotide(Nucleotide::A),Nucleotide(Nucleotide::U)))            
            ret = auType;          
        else if (c.compare(Nucleotide(Nucleotide::C), Nucleotide(Nucleotide::G)))                         
            ret = cgType;        
        else if (c.compare(Nucleotide(Nucleotide::G),Nucleotide(Nucleotide::U)))                         
            ret = guType;        
        else
            ret = othersType;
    }    
    return ret;
}

// [A=U -> 'W', G=C -> 'X', G=U -> 'Y', resto (A=G,C=T, A=C) Z]  
char TablesGenerator::column3Seq(size_t i, const SecStructure& structure, const NucSequence& sequence)
{
    const PairedType pType = get_pairedType(i,structure,sequence); 
    char ret;
    switch (pType)
    {
    case Unpaired : ret = sequence[i].as_char();
                   break; 
    case auType : ret = 'X';
                   break; 
    case cgType : ret = 'Y';
                   break; 
    case guType : ret = 'Z';
                   break; 
    case othersType : ret = '?';
                   break; 
    }         
    return ret;
}


//double TablesGenerator::calculateScore(const std::string& sequence, const int constAT, const DeltaG constGT);
//{
//    return 0;
//}

//void TablesGenerator::generateSequenceXYZ(const biopp::NucSequence& rna_m, biopp::NucSequence& mi_rna, std::list<biopp::NucSequence>& list_sequence_XYZ)
//{
//}
//void TablesGenerator::complementSequence(biopp::NucSequence& mi_rna, biopp::NucSequence& mirna_complemented)

//{
//}

//double TablesGenerator::scoreByPercentage(const biopp::NucSequence& sequence)
//{    
//    return 1;
//}

//double TablesGenerator::scoreByZuker(const biopp::NucSequence& sequence)
//{
//    return 0.1;
//}

int TablesGenerator::countNucleotid(const std::string& sequence, const char nucleotid)   
{
    int count = 0;
    for(int i = 0; i < sequence.length(); ++i)
    {
        if (sequence.at(i) == nucleotid)
            count++;
    }   
    return count;
}

//fila. 
void TablesGenerator::generate(const TableData& td)
{      
    assert(td.rnaM.length() == td.rnaMHumanized.length());   
    assert(td.structRNAm.size() == td.structHumanized.size());

    oFile.open(td.tableName.c_str());
    if(!oFile)
        throw "Can't create output file.";
    IndexConverter cIndex(td.rnaM.length(),td.circ, td.miRna.length()); //mismo length
    NucSequence mirnaCompl(td.miRna);
    mirnaCompl.complement(); 
    const size_t maxIndex = cIndex.getMaxPos();
    generateHeader();
    for(size_t i = 0; i <maxIndex ; ++i)
    {   
        generateTableRow(td.rnaM, td.rnaMHumanized, mirnaCompl, td.structRNAm, td.structHumanized, cIndex, i);
    }    
    oFile.close();
}
