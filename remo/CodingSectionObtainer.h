/**
 * @file     CodingSectionObtainer.h
 * @brief    CodingSectionObtainer provides the interface that allows
 *           get the coding section of sequence
 *
 * @author Franco Riberi
 * @email  fgriberi AT gmail.com
 *
 * Contents:  Header file for remo providing class CodingSectionObtainer.
 *
 * System:    remo: RNAemo - RNA research project
 * Language:  C++
 *
 * @date      October 2012
 *
 * This file is part of remo.
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

#ifndef CODING_SECTION_OBTAINER_H
#define CODING_SECTION_OBTAINER_H

#include <biopp/biopp.h>

namespace remo
{

class CodingSectionObtainer
{
public:

    /** @brief Constructor of class
     *
     */
    CodingSectionObtainer();

    /** @brief Get the coding section
     *
     * Method for obtaining the largest coding section of a given sequence.
     * @param src: original sequence
     * @param dest: larger coding section
     * @param posInit: to fill with the starting position of the largest coding section
     * @return void
     */
    void getCodingSection(const biopp::NucSequence& src, biopp::AminoSequence& dest, size_t& posInit);

private:

    /** @brief Copy the longest subsequence in other aminoSequence
    *
    * @param initSeq: initial position of the longest subsequence
    * @param finSeq: end position of the longest subsequence
    * @param dest: to fill with the larger subsequence
    * @retun void
    */
    void maxSubSeq(const size_t initSeq, const size_t finSeq, biopp::AminoSequence& dest) const;

    /** @brief Get position of next stop codon
     *
     * @param start: position where the search begins
     * @retun position in aminoacid sequence of next stop codon
     */
    size_t nextStop(size_t start) const;

    /** @brief Processes the subsequence determined by the input parameters
     *
     * @param start: subsequence start
     * @param end: subsequence end
     * @retun void
     */
    void processSubSeq(size_t start, size_t end);

    bool repeatedSize;              ///flag to determine if repeated the size of larger subsequence
    size_t lastGoodSize;            ///stores the size of the maximum subsequence temporarily
    size_t lastGoodStart;           ///initial position of the longest subsequence temporarily
    size_t lastGoodEnd;             ///end position of the longest subsequence temporarily
    biopp::AminoSequence* aminoSeq; ///aminoacid sequence to be processed
};

} // namespace remo
#endif /* CODING_SECTION_OBTAINER_H */

