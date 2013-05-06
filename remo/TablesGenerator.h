/**
 * @file     TablesGenerator.h
 * @brief    TablesGenerator provides the interface to select the output of remo (oldVersion-NewVersion)
 
 * @author   Franco Riberi
 * @email    fgriberi AT gmail.com
 *
 * Contents: Header file for TablesGenerator.
 *
 * System:   remo: RNAemo - RNA research project
 * Language: C++
 *
 * @date     October 2012
 *
 * This file is part of Remo.
 *
 * Copyright (C) 2012 - Franco Riberi, FuDePAN.
 *
 * Remo is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Remo is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Remo. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef TABLES_GENERATOR_H
#define TABLES_GENERATOR_H

#include <fideo/fideo.h>
#include <getoptpp/getopt_pp.h>
#include "remo/ICodonUsageModifier.h"

struct TablesGenerator
{
    /*
     * Destructor of class
     */
    virtual ~TablesGenerator() {}

    /*
     * Builder
     */
    virtual void initialize(GetOpt::GetOpt_pp& args) = 0;

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
    