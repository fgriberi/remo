/**
 * @file      PreFold.h
 * @brief     Provide the interface to pre-fold sequences.
 *
 * @author    Franco Riberi
 * @email     fgriberi AT gmail.com
 *
 * Contents:  Source file for remo providing PreFold interface.
 *
 * System:    remo: RNAemo - RNA research project
 * Language:  C++
 *
 * @date      October 2012
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

#include <fideo/fideo.h>
#include <acuoso/acuoso.h>
#include <biopp/biopp.h>
#include <biopp-filer/bioppFiler.h>

namespace remo
{

/** Provide the implementation to pre-fold sequences.
*
*/
class PreFold
{
public:

    /** @brief Constructor of class
    *
    */
    PreFold();

    /** @brief Destructor of class
    *
    */
    ~PreFold();

    /** @brief Prefolding of sequence.
     *
     * @param fileRNAm: file of RNAm sequences
     * @param circ: if the sequences are circular.
     * @param humanizer: concrete backend to humanizer sequence.
     * @return void
     */
    void prefold(bioppFiler::FastaParser<biopp::NucSequence>& fileRNAm, const bool circ,
                 const acuoso::ICodonUsageModifier* humanizer);

private:

    /** @brief Prefold specific sequece
     *
     * @param sequence: specific sequence to fold
     * @param isCirc: if the sequences are circular.
     * @param nameOutputFile: name of output file
     * @param structure: secondary structure
     * @return void
     */
    void preFoldSpecificSequence(biopp::NucSequence& sequence, const bool isCirc, const std::string& nameOutputFile, biopp::SecStructure& structure);

    /** @brief specific backend usage to fold
     *
     */
    fideo::IFold* folderImpl;

    /** @brief To store the current path
     *
     */
    std::string currentPath;


};

} // namespace remo
