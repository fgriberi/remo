/**
 *  @file:      CodingSectionObtainer.cpp
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
 * but WITHOUT ANY WARRANTY; w  ithout even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with R-emo. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "remo/Exceptions.h"
#include "remo/CodingSectionObtainer.h"

using namespace RemoTools;
using namespace biopp;
using namespace mili;

void CodingSectionObtainer::maxSubSeq(size_t initSeq, size_t finSeq, AminoSequence& dest) const
{
    const size_t limit = finSeq - initSeq;
    for (size_t i = 0 ; i < limit; ++i)
    {    
        insert_into(dest, (*aminoSeq)[i + initSeq]);
    }
}

size_t CodingSectionObtainer::nextStop(size_t start)
{
    size_t i = start;
    const size_t lengthAminoSeq = (*aminoSeq).size();
    while (i < lengthAminoSeq && (*aminoSeq)[i] != Aminoacid::STOP_CODON)
    {    
        ++i;
    }
    return i;
}

void CodingSectionObtainer::processSubSeq(size_t start, size_t end)
{
    if ((*aminoSeq)[start] == Aminoacid::STOP_CODON)
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

void CodingSectionObtainer::getCodingSection(const NucSequence& src, AminoSequence& dest, size_t& posInit)
{
    AminoSequence aminoSeq2;
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
        posInit = lastGoodStart * 3;
    }
}
