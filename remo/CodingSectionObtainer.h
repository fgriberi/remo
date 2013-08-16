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

typedef size_t IndexSequence;

/** @brief CodingSectionObtainer provides the interface that allows get the coding section of sequence
 *
 */
class CodingSectionObtainer
{
public:

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

    /** @brief Class that represent a subsequence
     *
     */
    struct SubSequenceDescriptor
    {
        /** @brief Constructor of class without parameters
         *
         */
        SubSequenceDescriptor();

        /** @brief Constructor of class with parameters
         *
         * @param subSeqStart: initial position of subsequence
         * @param subSeqEnd: final position of subsequence
         */
        SubSequenceDescriptor(IndexSequence subSeqStart, IndexSequence subSeqEnd);

        /** @brief Get the size of subsequence
         *
         * @return size of sequence
         */
        size_t getSize() const;

        IndexSequence _start;
        IndexSequence _end;

    };

    /** @brief Get the next initial position of a subsequence
     *
     * @param end: final position of last subsequence
     * @param aminoSeq: complete sequence
     * @retun next initial position of a subsequence
     */
    IndexSequence getSubSeqBegining(const IndexSequence end, const biopp::AminoSequence& aminoSeq) const;

    /** @brief Get the next final position of a subsequence
     *
     * @param start: initial position of last subsequence
     * @param aminoSeq: complete subsequence
     * @retun next final position of a subsequence
     */
    IndexSequence getSubSeqEnding(const IndexSequence start, const biopp::AminoSequence& aminoSeq) const;

    /** @brief Get the longest subsequence
     *
     * @param initSeq: initial position of the longest subsequence
     * @param finSeq: end position of the longest subsequence
     * @param dest: to fill with the larger subsequence
     * @retun void
     */
    void getMaxSubSequence(const SubSequenceDescriptor& subSeq, const biopp::AminoSequence& aminoSeq, biopp::AminoSequence& dest) const;
};

} // namespace remo
#endif /* CODING_SECTION_OBTAINER_H */