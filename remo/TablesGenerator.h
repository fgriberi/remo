/**
 *  @file:      TablesGenerator.h
 *  @details    System: R-emo \n
 *              Language: C++\n
 *  @author     Franco Riberi
 *
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with R-emo. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef TABLES_GENERATOR_H
#define TABLES_GENERATOR_H

#include <string>
#include <fstream>
#include "biopp/biopp.h"
#include "biopp-filer/bioppFiler.h"
#include "fideo/fideo.h"
#include "getoptpp/getopt_pp.h"
#include "remo/ICodonUsageModifier.h"

using namespace GetOpt;

struct TablesGenerator
{
public:

    /*
     * Destructor of class
     */
    virtual ~TablesGenerator() {}

    /*
     * Builder
     */
    virtual void initialize(GetOpt_pp& args) = 0;

    /*
     * Create file
     */
    virtual void generate(const std::string& tableName, const biopp::NucSequence& rnaMsg, const biopp::NucSequence& rnaMHumanized, bool circ) = 0;
    
    /**
     * Method that append one sequence of miRNA in table
     */
    virtual void appendMicro(const biopp::NucSequence& miRna, const std::string& nameMicro) = 0;
};
#endif /* TABLES_GENERATOR_H */
