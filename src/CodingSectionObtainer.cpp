/**
 * @file     CodingSectionObtainer.cpp
 * @brief    This is the implementation of CodingSectionObtainer interface
 *
 * @author   Franco Riberi
 * @email    fgriberi AT gmail.com
 *
 * Contents: Source file for remo providing class CodingSectionObtainer implementation.
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
 * but WITHOUT ANY WARRANTY; w  ithout even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Remo. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "remo/Exceptions.h"
#include "remo/CodingSectionObtainer.h"

namespace remo
{

CodingSectionObtainer::CodingSectionObtainer() :
    repeatedSize(false), lastGoodSize(0), lastGoodStart(0), lastGoodEnd(0), aminoSeq() {}

void CodingSectionObtainer::maxSubSeq(const IndexSequence initSeq, const IndexSequence finSeq, biopp::AminoSequence& dest) const
{
    const size_t limit = finSeq - initSeq;
    for (size_t i = 0 ; i < limit; ++i)
    {
        mili::insert_into(dest, aminoSeq[i + initSeq]);
    }
}

IndexSequence CodingSectionObtainer::nextStop(const IndexSequence start) const
{
    IndexSequence i = start;
    while ((i < aminoSeq.size()) && (aminoSeq[i] != biopp::Aminoacid::STOP_CODON))
    {
        ++i;
    }
    return i;
}

void CodingSectionObtainer::processSubSeq(const IndexSequence start, const IndexSequence end)
{
    assert(start < end);
    IndexSequence tempStart = start;
    if (aminoSeq[tempStart] == biopp::Aminoacid::STOP_CODON)
    {
        ++tempStart;
    }
    const size_t newSize = (end - tempStart) + 1;
    if (newSize > lastGoodSize)
    {
        lastGoodSize = newSize;
        lastGoodStart = tempStart;
        lastGoodEnd = end;
        repeatedSize = false;
    }
    else if (newSize == lastGoodSize)
    {
        repeatedSize = true;
    }
}

void CodingSectionObtainer::getCodingSection(const biopp::NucSequence& src, biopp::AminoSequence& dest, size_t& posInit)
{
    src.translate(dest);
    aminoSeq = dest;

    const size_t length = aminoSeq.size();
    IndexSequence last = 0;
    IndexSequence next = 0;
    do
    {
        next = nextStop(last + 1);
        processSubSeq(last, next);
        last = next;
    }
    while (last <= length);
    if (repeatedSize)
    {
        throw ErrorCodingSection();
    }
    dest.clear();
    maxSubSeq(lastGoodStart, lastGoodEnd, dest);
    posInit = lastGoodStart * 3; // remember that the original sequence is in nucleotides
}

}  // namespace remo