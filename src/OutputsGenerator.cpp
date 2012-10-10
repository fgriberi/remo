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
#include "biopp/biopp.h"
#include "fideo/fideo.h"
#include "mili/mili.h"
#include "remo/OutputsGenerator.h"
#include "remo/TablesGenerator.h"
#include "remo/IHumanizer.h"

using namespace biopp;
using namespace bioppFiler;
using namespace std;
using namespace mili;

string OutputsGenerator::generateTableName(const string& rna_m_name, size_t n)
{
    stringstream out;    
    out << rna_m_name << "_" << n;
    return out.str();    
}

//see
string OutputsGenerator::parseFileName(const string& fileName)
{
    size_t start, end, aux = 0;   
    for (size_t i = 0; i < fileName.length(); ++i)
    {
        if (fileName[i] == '|')
            ++aux;
        if (aux == 3)
            start = aux; //+1  
        if (aux == 4)
        {
            end = aux;
            break;
        }
    }
    return substr(fileName, Pos_(start), Pos_(end));
}

void OutputsGenerator::generateOutput(FastaParser<NucSequence>& file_rna_m, FastaParser<NucSequence>& file_mi_rna, bool circ, 
                                      IHumanizer* humanizer, IFold* folder)
{
    size_t miRnacount;
    string description;
    TablesGenerator tGenerator;                
    TablesGenerator::TableData td;
    while(file_rna_m.getNextSequence(description,td.rnaM))      
    {       
        //humanizo la secuencia
        humanizer->humanize(td.rnaM, td.rnaMHumanized);

        //foldeo el mensajero y el humanizado
        td.structRNAm.clear();
        folder->fold(td.rnaM, td.structRNAm, circ);
        folder->fold(td.rnaMHumanized, td.structHumanized, circ);

        //miRNA.restart()
        miRnacount = 0;
        string microDescription;
        NucSequence microSequence;        
        while(file_mi_rna.getNextSequence(microDescription, microSequence))
        {                                    
            td.tableName = generateTableName(parseFileName(description), miRnacount);
            td.miRna = microSequence;
            tGenerator.generate(td);
        }
    }
}
