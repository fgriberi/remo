/**
 *  @file:      OutputsGenerator.cpp
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

#include "remo/OutputsGenerator.h"

using namespace biopp;

/**
* Genera una lista de secuencias donde en cada una aparece 'M' si los nucleotidos se corresponden por complemento y el del rna_m esta apareado
*/
void OutputsGenerator::generateMaskedSequence(const biopp::NucSequence& rna_m, biopp::NucSequence& mi_rna, std::list<biopp::NucSequence>& list_masked)
{
    //obtengo la estructura secundaria del RNAm
    SecStructure secundary_structure;
    IFold* folder = mili::FactoryRegistry<IFold, std::string>::new_class("UNAFold");
    folder->fold(rna_m, secundary_structure, circ);

    //complemento el miRNA
    mi_rna.complement();

    int k, index;
    for (int i = 0; i < rna_m.length(); ++i)
    {
        NucSequence ns("");
        k = 0;
        for (int j = 0; j < mi_rna.length(); ++j)
        {
            if (circ)
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
                //to_mask_nucleotid(mi_rna[j], rna_m[index], secundary_structure, index, ns);
            }
            else
            {
                if ((j + i) < rna_m.length())
                {
                    //to_mask_nucleotid(mi_rna[j], rna_m[j+i], secundary_structure, j+i, ns);
                }
                else
                {
                    //no tengo mas elementos en el rnaM
                    //to_mask_nucleotid(mi_rna[j], rna_m[0], secundary_structure, 0, ns); //rna_m[0]
                }
            }
            list_masked.push_back(ns);
        }
    }
}

void OutputsGenerator::toMaskNucleotid(Nucleotide& nuc_mi_rna, Nucleotide& nuc_rna_m, SecStructure& structure_rna_m, int i, NucSequence& sequence)
{
    if (nuc_mi_rna == nuc_rna_m)
    {
        if (structure_rna_m.is_paired(i))
        {
            Nucleotide mask("M");
            sequence.addNucleotide(mask);
        }
        else
        {
            sequence.addNucleotide(nuc_mi_rna);
        }

    }
}

void OutputsGenerator::generateSequenceByComplement(const biopp::NucSequence& rna_m, biopp::NucSequence& mi_rna, std::list<biopp::NucSequence>& list_by_complement)
{
}

void OutputsGenerator::generateSequenceXYZ(const biopp::NucSequence& rna_m, biopp::NucSequence& mi_rna, std::list<biopp::NucSequence>& list_sequence_XYZ)
{
}
