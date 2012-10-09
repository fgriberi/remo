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
#include <biopp/biopp.h>
#include <fideo/fideo.h>

class TablesGenerator
{
public:
    struct
    {
      std::string tableName;
      biopp::NucSequence rnaM;
      biopp::NucSequence rnaMHumanized;
      biopp::NucSequence miRna;    
      bool circ;  
      biopp::SecStructure structRNAm;
      biopp::SecStructure structHumanized;
  
    } oneTableData;
        
    TablesGenerator();
    ~TablesGenerator();

    void setOneTableData(const std::string& tName, const biopp::NucSequence& rnam, const biopp::NucSequence& rnamhumanized,const
                         biopp::NucSequence& mirna, bool circular, biopp::SecStructure& sRNAm, biopp::SecStructure& sHumanized);
    /**
    * Genera una lista de secuencias donde en cada una aparece 'M' si los nucleotidos se corresponden por complemento y el del rna_m esta apareado
    */
    void generateMaskedSequence(std::string& rna_m, std::string& mi_rna);

    /**
    * Toma un nucleotid del RNAm y una del miRNA, y los enmascara en caso correspondiente, de lo contrario deja uno de ellos
    */
    void toMaskNucleotid(char nuc_mi_rna, char nuc_rna_m, biopp::SecStructure& structure_rna_m, int i, std::string sequence);

    /**
    * Genera una lista de secuencias donde en cada una aparece en mayuscula los nucleotidos que hagan matching por complemento, caso contrario en
    * minuscula.
    */
    void generateSequenceByComplement(const biopp::NucSequence& rna_m, biopp::NucSequence& mi_rna, std::list<biopp::NucSequence>& list_by_complement);

    /**
    * Genera una lista de secuencias donde en cada una se muestran los nucleotidos no disponibles mediante XYZ, segun el tipo de union
    * [A=U -> 'X', G=C -> 'Y', G=U -> 'Z']
    */
    void generateSequenceXYZ(const biopp::NucSequence& rna_m, biopp::NucSequence& mi_rna, std::list<biopp::NucSequence>& list_sequence_XYZ);
   
    /**
    * Complementa una secuencia complementada.
    */
    void complementSequence(biopp::NucSequence& mi_rna, biopp::NucSequence& mirna_complemented);

    //int toupper(int c);
    //int tolower(int c);



    /**
    * Toma una secuencia y calcula el score por porcentaje. Constante = 1
    */
    double scoreByPercentage(const biopp::NucSequence& sequence);

    /**
    * Toma una secuencia y calcula el score por zuker. Constante valores especificos
    */
    double scoreByZuker(const biopp::NucSequence& sequence);

    /**
    * Cuenta la cantidad de nucleotid en sequence.
    */
    int countNucleotid(const std::string& sequence, const char nucleotid);
};
#endif /* TABLES_GENERATOR_H */
