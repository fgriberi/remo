///**
// *  @file:      TablesGenerator.h
// *  @details    System: R-emo \n
// *              Language: C++\n
// *  @author     Franco Riberi
// *
// *  @email      fgriberi AT gmail.com
// *
// *  @date       October 2012
// *  @version    1.0
// *
// * This file is part of R-emo.
// *
// * Copyright (C) 2012 - Franco Riberi, FuDePAN.
// *
// * R-emo is free software: you can redistribute it and/or modify
// * it under the terms of the GNU General Public License as published by
// * the Free Software Foundation, either version 3 of the License, or
// * (at your option) any later version.
// *
// * R-emo is distributed in the hope that it will be useful,
// * but WITHOUT ANY WARRANTY; without even the implied warranty of
// * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// * GNU General Public License for more details.
// *
// * You should have received a copy of the GNU General Public License
// * along with R-emo. If not, see <http://www.gnu.org/licenses/>.
// *
// */

#ifndef TABLES_GENERATOR_H
#define TABLES_GENERATOR_H

#include <string>
#include <fstream>
#include "biopp/biopp.h"
#include "biopp-filer/bioppFiler.h"
#include "remo/ICodonUsageModifier.h"

class TablesGenerator
{
public:
    /**
    * Structure containing all data necessary for the generation of tables
    */
    struct TableData
    {
        std::string tableName;
        biopp::NucSequence rnaM;
        biopp::NucSequence rnaMHumanized;
        biopp::NucSequence miRna;
        std::string nameMicro;
        bool circ;
        biopp::SecStructure structRNAm;
        biopp::SecStructure structHumanized;
        DeltaG scoreHybOrig;
        DeltaG scoreHybHum;
        DeltaG scoreHybRaton;
    };

    /*
     * Output file
     */
    std::ofstream oFile;

    /**
     * Method that prints the header files
     */
    virtual void generateHeader() = 0;

    /**
     * Method that populates a file by rows
     */
    virtual void generate(const TableData& td) = 0;

    /**
     * Method that append one sequence of miRNA in table
     */
    virtual void appendMicro(const TableData& td) = 0;

};
#endif /* TABLES_GENERATOR_H */
