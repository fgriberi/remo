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

static const int unsigned PERCENTAGE_AU = 1;
static const int unsigned PERCENTAGE_GC = 1;

static const DeltaG ZUKER_AU = -2;
static const DeltaG ZUKER_GC = -3;

/**
* Genera una lista de secuencias donde en cada una aparece 'M' si los nucleotidos se corresponden por complemento y el del rna_m esta apareado
*/
void TablesGenerator::generateMaskedSequence(std::string& rna_m, std::string& mi_rna)
{
    //obtengo la estructura secundaria del RNAm
    SecStructure secundary_structure;
    NucSequence rnaM(rna_m);
    IFold* folder = mili::FactoryRegistry<IFold, std::string>::new_class("UNAFold");
    folder->fold(rnaM, secundary_structure, oneTableData.circ);

    //complemento el miRNA
    NucSequence miRNA(mi_rna);
    miRNA.complement();

    std::string mirna_complemented = miRNA.getString();

    int k, index;   
    for (int i = 0; i < rna_m.length(); ++i)   
    {
        std::string sequence_generated;
        k = 0;
        for (int j = 0; j < mi_rna.length(); ++j)
        {
            if (oneTableData.circ)
            {
                if ((j + i) >= rna_m.length())
                {
                    index = k;
                    k++;
                }
                else
                {
                    index = j + i;
                }
                toMaskNucleotid(mirna_complemented.at(i), rna_m.at(index), secundary_structure, index, sequence_generated);
            }
            else
            {
                if ((j + i) < rna_m.length())
                {
                    toMaskNucleotid(mirna_complemented.at(j), rna_m.at(j+i), secundary_structure, j+i, sequence_generated);
                }                    
                else
                {
                    //no tengo mas elementos en el rnaM
                    sequence_generated += mirna_complemented.at(j);                        
                }
            }
            //list_masked.push_back(ns);
        }
    }
}

void TablesGenerator::toMaskNucleotid(char nuc_mi_rna, char nuc_rna_m, SecStructure& structure_rna_m, int i, std::string sequence)
{
    if (nuc_mi_rna == nuc_rna_m)
    {
        if (structure_rna_m.is_paired(i))
        {
            sequence += "M";    
        }
        else
        {
            sequence += nuc_mi_rna;
        }
    }
}


//void TablesGenerator::generateSequenceByComplement(const biopp::NucSequence& rna_m, biopp::NucSequence& mi_rna, std::list<biopp::NucSequence>& list_by_complement)
//{
//}

//void TablesGenerator::generateSequenceXYZ(const biopp::NucSequence& rna_m, biopp::NucSequence& mi_rna, std::list<biopp::NucSequence>& list_sequence_XYZ)
//{
//}

//void TablesGenerator::complementSequence(biopp::NucSequence& mi_rna, biopp::NucSequence& mirna_complemented)
//{
//}

//double TablesGenerator::scoreByPercentage(const biopp::NucSequence& sequence)
//{
//}

//double TablesGenerator::scoreByZuker(const biopp::NucSequence& sequence)
//{
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
