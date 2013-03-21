/**
 *  @file:      CodingSectionObtainer.h
 *  @details    System: R-emo \n
 *              Language: C++\n
 *
 *  @author     Franco Riberi
 *  @email      fgriberi AT gmail.com
 *
 *  @date       October 2012
 *  @version    1.0
 *
 * This file is part of R-emo.
 *
 * Copyright (C) 2012 - Franco Riberi, FuDePAN.
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

#ifndef CODING_SECTION_OBTAINER_H
#define CODING_SECTION_OBTAINER_H

#include "biopp/biopp.h"

class CodingSectionObtainer
{
    bool repeatedSize;
    size_t lastGoodSize;
    size_t lastGoodStart;
    size_t lastGoodEnd;
    biopp::AminoSequence* aminoSeq;

    void maxSubSeq(size_t initSeq, size_t finSeq, biopp::AminoSequence& dest) const;

    size_t nextStop(size_t start);

    void processSubSeq(size_t start, size_t end);

public:

    CodingSectionObtainer() : repeatedSize(false), lastGoodSize(0), lastGoodStart(0), lastGoodEnd(0), aminoSeq() {}

    void getCodingSection(const biopp::NucSequence& src, biopp::AminoSequence& dest, size_t& posInit);
};

#endif /* CODING_SECTION_OBTAINER_H */
