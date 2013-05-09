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
    
void CodingSectionObtainer::maxSubSeq(const size_t initSeq, const size_t finSeq, biopp::AminoSequence& dest) const
{
    const size_t limit = finSeq - initSeq;
    for (size_t i = 0 ; i < limit; ++i)
    {
        mili::insert_into(dest, (*aminoSeq)[i + initSeq]);
    }
}

size_t CodingSectionObtainer::nextStop(size_t start) const
{
    size_t i = start;
    const size_t lengthAminoSeq = (*aminoSeq).size();
    while (i < lengthAminoSeq && (*aminoSeq)[i] != biopp::Aminoacid::STOP_CODON)
    {
        ++i;
    }    
    return i;
}

void CodingSectionObtainer::processSubSeq(size_t start, size_t end)
{
    if ((*aminoSeq)[start] == biopp::Aminoacid::STOP_CODON)
    {
        ++start;
    }
    const size_t newSize = (end - start) + 1;
    if (newSize > lastGoodSize)
    {
        lastGoodSize = newSize;
        lastGoodStart = start;
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
    biopp::AminoSequence aminoSeq2;
    src.translate(aminoSeq2);
    aminoSeq = &aminoSeq2;

    const size_t length = (*aminoSeq).size();
    size_t last = 0;
    size_t next = 0;
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
    else
    {
        maxSubSeq(lastGoodStart, lastGoodEnd, dest);
        posInit = lastGoodStart * 3; // remember that the original sequence is in nucleotides
    }
}

}  // namespace remo