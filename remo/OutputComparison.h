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

#include <list>
#include <fstream>
#include "remo/IMotifObserverRemo.h"

namespace remo
{

struct StacksSave
{
    std::string nameSequence;
    Stacks orig;
    Stacks hum;
};

/** @brief Represent original and humanized stacks
 *
 */
typedef struct StacksSave StacksSave;

/** @brief To store original and humanized stacks
 *
 */
typedef std::list<StacksSave> StacksStores;

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

    /** @brief Fill the file generated
    *
    * @param origHumStacks: to fill file
    * @return void
    */
    void save(const StacksStores& origHumStacks);

private:

    /** @brief Generate a file
     *
     * @param fileName: file name
     * @return void
     */
    void generate(const File& fileName);

    /** @brief Fill header file
     *
     * @param limitElemet: determines the number of elements in each row
     * @return void
     */
    void generateHeader(const size_t limitElement);

    /** @brief Fill header with commas determines whether the number of commas is pair
    *
    * @param isPair: determines whether the number of commas is pair
    * @param amount: to fill with commas
    * @return void
    */
    void completeColumHeader(const bool isPair, const size_t amount);

    /** @brief Fill header with commas
    *
    * @param amount: limit of commas to added
    * @return void
    */
    void completeWithComma(const size_t amount);

    /** @brief Fill sub-header file
    *
    * @param limit: Maximum element of subheader
    * @return void
    */
    void generateSubHeader(const size_t limit);

    /** @brief Fill a column sub-header
    *
    * @param limit: Maximum element of subheader
    * @return void
    */
    void fillColumnSubHeader(const size_t limit);

    /** @brief Gets the maximum stack size
     *
     * @param stacks: to analize
     * @return maximum stack size
     */
    size_t maximumStack(const StacksStores& stacks) const;

    /** @brief Fill one line with data of stacks
     *
     * @param row: to fill file geneted generated
     * @param limit: limit of colums
     * @return void
     */
    void fillRow(const StacksStores& row, const size_t limit);

    /** @brief Fill column whith data (Orignal or Humanized colums)
     *
     * @param stacks: to get data
     * @param limit: limit of colums
     * @return void
     */
    void fillColumWithData(const Stacks& stacks, const size_t limit);

    /** @brief Represent a file output
     *
     */
    typedef std::ofstream FileOutput;

    /** @breif File to generate
     *
     */
    FileOutput comparisonFile;
};

} // namespace remo
#endif /* OUTPUT_COMPARISON_H */
