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
#include "remo/OutputsGenerator.h"
#include "remo/TablesGenerator.h"
#include "remo/IHumanizer.h"

using namespace biopp;
using namespace std;

//OutputsGenerator::OutputsGenerator(const std::string& file_rna_m, const std::string& file_mi_rna, bool circ) 
//    : file_msg(file_rna_m),
//    : file_micro(file_mi_rna),
//    : circular(circ)        
//{}

std::string OutputsGenerator::generateTableName(const std::string& rna_m_name, size_t n)
{
    std::stringstream out;    
    out << rna_m_name << "_" << n;
    return out.str();    
}

void OutputsGenerator::getDataToGenerateTable()
{
    try 
    {
        size_t miRnacount;
        string descripcion;
        NucSequence sequence;
        IHumanizer* humanizer = mili::FactoryRegistry<IHumanizer, std::string>::new_class("GeneDesign");
        IFold* folder = mili::FactoryRegistry<IFold, std::string>::new_class("UNAFold");
        while(file_msg.getNextSequence(descripcion,sequence))      
        {
            //humanizo la secuencia
            NucSequence sequenceHumanized;            
            humanizer->humanize(sequence,sequenceHumanized);

            //foldeo el mensajero y el humanizado
            SecStructure structRNAm;
            SecStructure structHumanized;
            folder->fold(sequence, structRNAm, circular);
            folder->fold(sequenceHumanized, structHumanized, circular);

            //miRNA.restart()
            miRnacount = 0;
            string microDescripcion;
            NucSequence microSequence;
            TablesGenerator tablesGenerator;
            while(file_micro.getNextSequence(microDescripcion, microSequence))
            {
                string tabName = generateTableName(descripcion,miRnacount);                  
                tablesGenerator.setOneTableData(tabName, sequence, sequenceHumanized, microSequence, circular, structRNAm, structHumanized);
            }
        }
    }   
    catch(const MethodNotImplemented& e)
    {   
    }
}
