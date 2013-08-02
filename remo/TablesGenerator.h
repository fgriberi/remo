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

#include <acuoso/acuoso.h>
#include <getoptpp/getopt_pp.h>

namespace remo
{

/** @brief Interface to select the output of remo
*
*/
struct TablesGenerator
{
    /** @brief Destructor of class
     *
     */
    virtual ~TablesGenerator() {}

    /** @brief Create a concrete instance depending on the selected service
     *
     * @param args: input object
     * @return void
     */
    virtual void initialize(GetOpt::GetOpt_pp& args) = 0;

    /** @brief Create output file
     *
     * @param tableName: file name
     * @param rnaMsg: sequence of messenger RNA
     * @param rnaMHumanized: sequence humanized
     * @param circ: sequence is circular
     * @return void
     */
    virtual void generate(const std::string& tableName, const biopp::NucSequence& rnaMsg,
                          const biopp::NucSequence& rnaMHumanized, const bool circ) = 0;

    /** @brief Method that append one sequence of miRNA in table
    *
    * @param miRna: sequence of miRNA
    * @param nameMicro: name of miRNA
    * @return void
    */
    virtual void appendMicro(const biopp::NucSequence& miRna, const std::string& nameMicro) = 0;

    /** @brief 
    *
    */
    bool dontFold;    
};

} // namespace remo
#endif /* TABLES_GENERATOR_H */
