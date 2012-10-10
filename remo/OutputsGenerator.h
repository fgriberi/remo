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
#include "biopp/biopp.h"
#include "fideo/fideo.h"
#include "biopp-filer/bioppFiler.h"
#include "remo/IHumanizer.h"

class OutputsGenerator
{            
    /**
    * Retorna un string que sera el nombre de un archivo.
    */    
    static std::string generateTableName(const std::string& rna_m_name, size_t n);
public:
   
    static void generateOutput(bioppFiler::FastaParser<biopp::NucSequence>& file_rna_m, bioppFiler::FastaParser<biopp::NucSequence>& file_mi_rna, 
                     bool circ, IHumanizer* humanizer, IFold* folder);
    
};
#endif /* OUTPUTS_GENERATOR_H */
