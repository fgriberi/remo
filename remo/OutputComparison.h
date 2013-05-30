/**
 * @file     OutputComparison.h
 * @brief    OutputComparison provides the interface to get the output file
 *           corresponding to the comparison between secondary structures
 *
 * @author   Franco Riberi
 * @email    fgriberi AT gmail.com
 *
 * Contents: Header file for OutputComparison.
 *
 * System:    remo: RNAemo - RNA research project
 * Language:  C++
 *
 * @date      May 2012
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

#ifndef OUTPUT_COMPARISON_H
#define OUTPUT_COMPARISON_H

#include <fstream>
#include "remo/ThermDetailsListener.h"

namespace remo
{

/** @briel Class that provides the interface to get the output file
 *         corresponding to the comparison between secondary structures
 *
 */
class OutputComparison
{
public:

    /** @brief Represent a file name
     *
     */
    typedef std::string File;

    /** @brief Constructor of class
    *
    */
    OutputComparison(const File& name);

    /** @brief Generate a file
     *
     * @param fileName: file name
     * @return void
     */
    void generate(const File& fileName);

    /** @brief Fill file with the stacks
    *
    * @param origStacks: stacks corresponding to the original sequence
    * @param humStacks: stacks corresponding to the humanized sequence
    * @return void
    */
    void save(Stacks& origStacks, Stacks& humStacks);

private:

    /** @brief Fill header file
     *
     * @return void
     */
    void generateHeader();

    /** @brief Fill header with commas
    *
    * @param amount: limit of commas to added
    * @return void
    */
    void completeWithComma(const size_t amount);

    /** @brief Update sub-header file
    *
    * @param limit: Maximum element of subheader
    * @return void
    */
    void updateSubHeader(const size_t limit);

    /** @brief Fill sub-header file
    *
    * @param limit: Maximum element of subheader
    * @return void
    */
    void generateSubHeader(const size_t limit);

    /** @brief Fill a column sub-header
    *
    * @param limit: Maximum element of subheader of a column
    * @return void
    */
    void fillColumnSubHeader(const size_t limit);

    /** @brief Gets the maximum size between two stacks
     *
     * @param origStacks: stacks corresponding to the original sequence
     * @param humStacks: stacks corresponding to the humanized sequence
     * @return maximum stack size
     */
    size_t maximumStack(const Stacks& origStacks, const Stacks& humStacks) const;

    /** @brief Fill one line with data of stacks
     *
     * @param origStacks: stacks corresponding to the original sequence
     * @param humStacks: stacks corresponding to the humanized sequence
     * @return void
     */
    void fillRow(Stacks& origStacks, Stacks& humStacks);

    /** @brief Fill complete column whith data (Orignal or Humanized colums)
     *
     * @param stacks: to get data
     * @return void
     */
    void fillColumWithData(Stacks& stacks);

    /** @brief Represent a file output
     *
     */
    typedef std::ofstream FileOutput;

    /** @breif File to generate
     *
     */
    FileOutput comparisonFile;

    /** @breif To store the partial maximum stack size
    *
    */
    size_t currentMaxStack;
};

} // namespace remo
#endif /* OUTPUT_COMPARISON_H */