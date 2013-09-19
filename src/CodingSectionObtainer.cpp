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

CodingSectionObtainer::SubSequenceDescriptor::SubSequenceDescriptor() :
    _start(0), _end(0) {}

CodingSectionObtainer::SubSequenceDescriptor::SubSequenceDescriptor(IndexSequence subSeqStart, IndexSequence subSeqEnd)
{
    _start = subSeqStart;
    _end = subSeqEnd;
}

size_t CodingSectionObtainer::SubSequenceDescriptor::getSize() const
{
    return _end - _start;
}

void CodingSectionObtainer::getMaxSubSequence(const SubSequenceDescriptor& subSeq, const biopp::AminoSequence& aminoSeq, biopp::AminoSequence& dest) const
{
    dest.clear();
    for (size_t i = 0 ; i <= subSeq.getSize(); ++i)
    {
        mili::insert_into(dest, aminoSeq[i + subSeq._start]);
    }
}

IndexSequence CodingSectionObtainer::getSubSeqBegining(const IndexSequence end, const biopp::AminoSequence& aminoSeq) const
{
    IndexSequence i = end;
    while (i < aminoSeq.size() && aminoSeq[i] == biopp::Aminoacid::STOP_CODON)
    {
        i++;
    }
    return i;
}

IndexSequence CodingSectionObtainer::getSubSeqEnding(const IndexSequence start, const biopp::AminoSequence& aminoSeq) const
{
    IndexSequence i = start;
    do
    {
        i++;
    }
    while (i < aminoSeq.size() && aminoSeq[i] != biopp::Aminoacid::STOP_CODON);
    return i - 1;
}

void CodingSectionObtainer::getCodingSection(const biopp::NucSequence& src, biopp::AminoSequence& dest, size_t& posInit)
{
    src.translate(dest);
    bool repeatedSize(false);
    IndexSequence currentStart = 0;
    IndexSequence currentEnd = -1;
    SubSequenceDescriptor maxSubSeq;

    while (currentStart < dest.size())
    {
        SubSequenceDescriptor currentSubSeq;
        currentSubSeq._start = getSubSeqBegining(currentEnd + 1, dest);
        currentStart = currentSubSeq._start;
        currentSubSeq._end = getSubSeqEnding(currentStart, dest);
        currentEnd = currentSubSeq._end;

        if (currentSubSeq.getSize() > maxSubSeq.getSize())
        {
            maxSubSeq._start = currentStart;
            maxSubSeq._end = currentEnd;
            repeatedSize = false;
        }
        else if (currentSubSeq.getSize() == maxSubSeq.getSize())
        {
            repeatedSize = true;
        }
        currentStart = currentEnd;
    }
    mili::assert_throw<ErrorCodingSection>(!repeatedSize);
    biopp::AminoSequence aminoSeq = dest;
    getMaxSubSequence(maxSubSeq, aminoSeq, dest);
    posInit = maxSubSeq._start * 3; // remember that the original sequence is in nucleotides
}

}  // namespace remo