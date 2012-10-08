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
 * but WITHOUT ANY WARRANTY; w  ithout even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with R-emo .  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <sstream>
#include "remo/OutputsGenerator.h"

using namespace biopp;

//OutputsGenerator::OutputsGenerator(const std::string& file_rna_m, const std::string& file_mi_rna)
//{
//}

std::string OutputsGenerator::generateTableName(const std::string& rna_m_name, size_t n)
{
    std::stringstream out;    
    out << rna_m_name << "_" << n;
    return out.str();    
}

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
