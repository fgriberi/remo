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

class CodingSectionObtainer
{
public:

    CodingSectionObtainer() : repeatedSize(false), lastGoodSize(0), lastGoodStart(0), lastGoodEnd(0), aminoSeq() {}

    void getCodingSection(const biopp::NucSequence& src, biopp::AminoSequence& dest, size_t& posInit);

private:
    void maxSubSeq(size_t initSeq, size_t finSeq, biopp::AminoSequence& dest) const;

    size_t nextStop(size_t start);

    void processSubSeq(size_t start, size_t end);

    bool repeatedSize;
    size_t lastGoodSize;
    size_t lastGoodStart;
    size_t lastGoodEnd;
    biopp::AminoSequence* aminoSeq;

};
//}
#endif /* CODING_SECTION_OBTAINER_H */

