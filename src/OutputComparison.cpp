/**
 * @file:     OutputComparison.cpp
 * @brief     This is the implementation of OutputComparison interface.
 *
 * author     Franco Riberi
 * @email     fgriberi AT gmail.com
 *
 * Contents:  Source file for remo providing OutputComparison implementation.
 *
 * System:    remo: RNAemo - RNA research project
 * Language:  C++
 *
 * @date      May 2013
 *
 * This file is part of Remo.
 *
 * Copyright (C) 2013 - Franco Riberi, FuDePAN.
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

#include <algorithm>
#include <vector>
#include "remo/OutputComparison.h"
#include "remo/Exceptions.h"

namespace remo
{

OutputComparison::OutputComparison(const File& name)
{
    generate(name);
}

void OutputComparison::generate(const File& fileName)
{
    if (_comparisonFile)
    {
        _comparisonFile.close();
    }
    _comparisonFile.open(fileName.c_str());
    mili::assert_throw<FileNotCreated>(_comparisonFile);
}

void OutputComparison::generateHeader(const size_t limitElement)
{
    const size_t amountNecessaryCommas = limitElement / 2;
    const bool isPairLimitElement = (limitElement % 2) == 0;

    _comparisonFile << "RNAm, ";
    completeWithComma(amountNecessaryCommas);
    _comparisonFile << "Original";
    completeColumHeader(isPairLimitElement, amountNecessaryCommas);
    completeWithComma(amountNecessaryCommas);
    _comparisonFile << "Humanized";
    completeColumHeader(isPairLimitElement, amountNecessaryCommas + 1);
    _comparisonFile << std::endl;
}

void OutputComparison::completeColumHeader(const bool isPair, const size_t amount)
{
    if (isPair)
    {
        completeWithComma(amount - 1);
    }
    else
    {
        completeWithComma(amount);
    }
}

void OutputComparison::completeWithComma(const size_t amount)
{
    for (size_t i = 0; i < amount; ++i)
    {
        _comparisonFile << ", ";
    }
}

void OutputComparison::generateSubHeader(const size_t limit)
{
    _comparisonFile << "stackSize, " ;
    fillColumnSubHeader(limit);
    _comparisonFile << ", " ;
    fillColumnSubHeader(limit);
    _comparisonFile << std::endl;
}

void OutputComparison::fillColumnSubHeader(const size_t limit)
{
    for (size_t i = 0; i < limit; ++i)
    {
        _comparisonFile << i + 1;
        if (i + 1 != limit)
        {
            _comparisonFile << ", ";
        }
    }
}

size_t OutputComparison::maximumStack(const StacksStores& stacks) const
{
    size_t ret = 0;
    StacksStores::const_iterator it;
    for (it  = stacks.begin(); it != stacks.end(); ++it)
    {
        const size_t firstTerm = it->orig.rbegin()->first;
        const size_t secondTerm = it->hum.rbegin()->first;
        if ((firstTerm >= secondTerm) && (firstTerm >= ret))
        {
            ret = firstTerm;
        }
        else if ((secondTerm >= firstTerm) && (secondTerm >= ret))
        {
            ret = secondTerm;
        }
    }
    return ret;
}

void OutputComparison::fillRow(const StacksStores& row, const size_t limit)
{
    StacksStores::const_iterator it;
    for (it = row.begin(); it != row.end(); ++it)
    {
        _comparisonFile << it->nameSequence << ", ";
        fillColumWithData(it->orig, limit);
        _comparisonFile << ", ";
        fillColumWithData(it->hum, limit);
        _comparisonFile << std::endl;
    }
}

void OutputComparison::fillColumWithData(const Stacks& stacks, const size_t limit)
{
    Stacks::const_iterator it = stacks.begin();
    for (size_t i = 1; i <= limit; ++i)
    {
        if (i != it->first)
        {
            _comparisonFile << 0;
        }
        else
        {
            _comparisonFile << it->second;
            ++it;
        }
        if (i != limit)
        {
            _comparisonFile << ", ";
        }
    }
}

void OutputComparison::save(const StacksStores& origHumStacks)
{
    const size_t limit = maximumStack(origHumStacks);
    generateHeader(limit);
    generateSubHeader(limit);
    fillRow(origHumStacks, limit);
}

/***********************************************
//Output file format
RNAm, , , Original, , , , , Humanized, ,
size, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5
seq1, amout1, amout2, ....
***********************************************/

} // namespace remo