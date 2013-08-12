
/**
 * @file     MOP.h
 * @brief    MOP interface.
 *
 * @author   Franco Riberi
 * @email    fgriberi AT gmail.com
 *
 * Contents: Header file for remo providing class MOP.
 *
 * System:   remo: RNAemo - RNA research project
 * Language: C++
 *
 * @date 2012
 *
 * Copyright (C) 2012 Franco Riberi, FuDePAN
 *
 * This file is part of the remo.
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

#ifndef MOP_H
#define MOP_H

#include <getoptpp/getopt_pp.h>
#include <biopp/biopp.h>
#include <acuoso/acuoso.h>
#include <biopp-filer/bioppFiler.h>

namespace remo
{

/** @brief Mediator class
*
*/
class MOP
{
public:

    typedef std::string OptionUsage;

    /** @brief Structure that represents all the data needed to remo
     *
     */
    struct RemoArguments
    {
        OptionUsage fileNameRNAm;
        OptionUsage fileNameMicroRNA;
        bool isCirc;
        bool help;
        OptionUsage humanizer;
        OptionUsage folder;
        OptionUsage hybridize;
        size_t organism;
        OptionUsage method;
        bool comparisonOption;
        bool analysisOption;
        bool prefold;
        bool dontFold;
        size_t toleranceOfBulge;
        size_t toleranceOfInterior;
    };

    /** @brief Start program
     *
     * @param args: object containing the input parameters needed
     * @param void
     */
    static void startSystem(GetOpt::GetOpt_pp& args, const RemoArguments& remoArgs);

private:

    /** @brief Determines whether the organism is valid
     *
     * @param organism: specific organism
     * @return true if organism is valid, otherwise return false
     */
    static bool isValidOrganism(const size_t organism);

    /** @brief
     *
     * @param fileMsg:
     * @param circ:
     * @param humanizer
     * @return void
     */
    static void optionToPrefold(bioppFiler::FastaParser<biopp::NucSequence>& fileMsg, const bool circ, const acuoso::ICodonUsageModifier* humanizer);

    /** @brief
     *
     * @param args:
     * @param fileMsg:
     * @param circ:
     * @param fileMiRna:
     * @param humanizer:
     * @param dontFold:
     * @return void
     */
    static void optionToAnalysis(GetOpt::GetOpt_pp& args, const OptionUsage& method, bioppFiler::FastaParser<biopp::NucSequence>& fileMsg, const bool  circ, const OptionUsage& fileMiRna,
                                 const acuoso::ICodonUsageModifier* humanizer, const bool dontFold);

    /** @brief
     *
     * @param fileMsg:
     * @param circ:
     * @param humanizer
     * @param dontFold:
     * @param toleranceOfBulge:
     * @param toleranceOfInterior:
     * @return void
     */
    static void optionToComparison(bioppFiler::FastaParser<biopp::NucSequence>& fileMsg, const bool circ, const acuoso::ICodonUsageModifier* humanizer,
                                   const bool dontFold, const size_t toleranceOfBulge, const size_t toleranceOfInterior);
};

} // namespace remo
#endif /* MOP_H */