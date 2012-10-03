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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with R-emo .  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef OUTPUTS_GENERATOR_H
#define OUTPUTS_GENERATOR_H

#include <string>
#include <biopp/biopp.h>
#include <fideo/fideo.h>
//#include <biopp-filer/bioppFiler.h>

class OutputsGenerator
{
    IFold* rFolder;
    //FastaParse rna_m;
    //FastaParse mi_rna;
    bool circ;
public:
    OutputsGenerator() {}

    /**
    * Genera una lista de secuencias donde en cada una aparece 'M' si los nucleotidos se corresponden por complemento y el del rna_m esta apareado
    */
    std::list<biopp::NucSequence> generate_masked_sequence(const biopp::NucSequence& rna_m, biopp::NucSequence& mi_rna);

    /**
    * Genera una lista de secuencias donde en cada una aparece en mayuscula los nucleotidos que hagan matching por complemento, caso contrario en
    * minuscula.
    */
    std::list<biopp::NucSequence> generate_sequence_by_complement(const biopp::NucSequence& rna_m, biopp::NucSequence& mi_rna);

    /**
    * Genera una lista de secuencias donde en cada una se muestran los nucleotidos no disponibles mediante XYZ, segun el tipo de union
    * [A=U -> 'X', G=C -> 'Y', G=U -> 'Z']
    */
    std::list<biopp::NucSequence> generate_sequence_XYZ(const biopp::NucSequence& rna_m, biopp::NucSequence& mi_rna);

    /**
    * Devuelve una secuencia complementada.
    */
    biopp::NucSequence to_complemente_sequence(biopp::NucSequence& mi_rna);

    /**
    * Toma una secuencia y calcula el score por porcentaje. Constante = 1
    */
    n_double score_by_percentage(const biopp::NucSequence& sequence);

    /**
    * Toma una secuencia y calcula el score por zuker. Constante valores especificos
    */
    n_double score_by_zuker(const biopp::NucSequence& sequence);

    /**
    * Cuenta la cantidad de nucleotid en sequence.
    */
    int count_nucleotid(const biopp::NucSequence& sequence, const char nucleotid);

    /**
    * Retorna un string que sera el nombre de un archivo.
    */
    std::string generate_table_name(const std::string rna_m_name, n_int n);

    /*
    Pseudo-codigo
    try{
        Para todo rnaM
            humanized = humanizar rnaM
            foldear rnaM original   -> (biopp::SecStructure structRNAm)
            foldear rnaM humanizado -> ( biopp::SecStructure structHumanized)
            miRNA.restart()
            miRnacount = 0;
            Para todo micro_rna
                table_name(rnam.name,miRnacount)
                generarTable(rnaM, structRNAm, structHumanized, micro_rna, circl ) -> CSV file
    }
    catch{
    }
    */
};
#endif /* OUTPUTS_GENERATOR_H */
