/**
 * @file     ComparisonGenerator.h
 * @details  ComparisonGenerator provides the interface for the comparison of secondary structures
 *
 * @author   Franco Riberi
 * @email    fgriberi AT gmail.com
 *
 * Contents: Header file for ComparisonGenerator.
 *
 * System:   remo: RNAemo - RNA research project
 * Language: C++
 *
 * @date    March 26, 2013
 *
 * This file is part of R-emo.
 *
 * Copyright (C) 2013 - Franco Riberi, FuDePAN.
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

#ifndef COMPARISON_GENERATOR_H
#define COMPARISON_GENERATOR_H

#include <acuoso/acuoso.h>
#include <biopp/biopp.h>
#include <fideo/fideo.h>
#include <biopp-filer/bioppFiler.h>
#include "remo/OutputComparison.h"

namespace remo
{

/** @brief Provides the interface for the comparison of secondary structures
 *
 */
class ComparisonGenerator
{
public:

    /** @brief constructor of class
     *
     */
    ComparisonGenerator();

    /** @breif Destructor of class
     *
     */
    ~ComparisonGenerator();

    /** @brief Generate the comparison of secondary structures
     *
     * @param fileRNAm: file of RNAm sequences
     * @param circ: if the sequences are circular.
     * @param humanizer: concrete backend to humanizer sequence.
     * @param toleranceOfBulge: greater value allowed in a bulge loop.
     * @param toleranceOfInterior: greater value allowed in an interior loop.
     * @return void
     */
    void generateComparison(bioppFiler::FastaParser<biopp::NucSequence>& fileRNAm, const bool circ,
                            const acuoso::ICodonUsageModifier* humanizer, const size_t toleranceOfBulge,
                            const size_t toleranceOfInterior);

private:

    /** @brief Process current sequence
    *
    * @param sequence: RNAm sequence
    * @param structure: secondary structure of sequence
    * @param obs: remo observer
    * @param tb: greater value allowed in a bulge loop.
    * @param ti: greater value allowed in an interior loop.
    * @param currentStacks: to fill
    * @return void
    */
    void processSequence(biopp::NucSequence& sequence, const bool circ, biopp::SecStructure& structure, fideo::IMotifObserver* obs);

    /** @brief Specific backend to folder
     *
     */
    fideo::IFold* folder;

    /** @brief To fill the generated file
     *
     */
    StacksStores stacksStore;

};

} // namespace remo
#endif /* COMPARISON_GENERATOR_H */