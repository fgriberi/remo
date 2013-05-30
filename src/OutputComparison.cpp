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
    : currentMaxStack(0)
{
    generate(name);
}

void OutputComparison::generate(const File& fileName)
{
    if (comparisonFile.is_open())
    {
        comparisonFile.close();
    }
    comparisonFile.open(fileName.c_str());
    if (!comparisonFile)
    {
        throw FileNotCreate();
    }
}

static const size_t INIT_FILE = 0;

//ver si esta bien el tema de las comas
void OutputComparison::generateHeader()
{
    comparisonFile.seekp(INIT_FILE);
    const size_t amountNecessaryCommas = currentMaxStack / 2;
    const bool isPairCurrentMaxStack = (currentMaxStack % 2) == 0;
    //first row
    comparisonFile << "RNAm," ;
    completeWithComma(amountNecessaryCommas);
    comparisonFile << "Original";
    if (isPairCurrentMaxStack)
    {
        completeWithComma(amountNecessaryCommas - 1);
    }
    else
    {
        completeWithComma(amountNecessaryCommas);
    }
    completeWithComma(amountNecessaryCommas);
    comparisonFile << "Humanized";
    if (isPairCurrentMaxStack)
    {
        completeWithComma(amountNecessaryCommas - 1);
    }
    else
    {
        completeWithComma(amountNecessaryCommas);
    }
    comparisonFile << std::endl;
}

void OutputComparison::completeWithComma(const size_t amount)
{
    for (size_t i = 0; i < amount; ++i)
    {
        comparisonFile << ", ";
    }
}

void OutputComparison::generateSubHeader(const size_t limit)
{
    //comparisonFile.seekp(INIT_FILE);
    comparisonFile << ", " ;
    fillColumnSubHeader(limit);
    comparisonFile << ", " ;
    fillColumnSubHeader(limit);
    comparisonFile << std::endl;
}


void OutputComparison::fillColumnSubHeader(const size_t limit)
{
    for (size_t i = 0; i < limit; ++i)
    {
        comparisonFile << i + 1;
        if (i + 1 != limit)
        {
            comparisonFile << ", ";
        }
    }
}

size_t OutputComparison::maximumStack(const Stacks& origStacks, const Stacks& humStacks) const
{
    size_t ret;
    const size_t firstTerm = origStacks.rbegin()->first;
    const size_t secondTerm = humStacks.rbegin()->first;
    if (firstTerm >= secondTerm)
    {
        ret = firstTerm;
    }
    else
    {
        ret = secondTerm;
    }
    return ret;
}

void OutputComparison::updateSubHeader(const size_t limit)
{
    if (currentMaxStack < limit)
    {
        generateSubHeader(limit);
        currentMaxStack = limit;
    }
}

void OutputComparison::fillColumWithData(Stacks& stacks)
{
    Stacks::iterator it = stacks.begin();
    for (size_t i = 1; i <= currentMaxStack; ++i)
    {
        if (i != it->first)
        {
            comparisonFile << 0;
        }
        else
        {
            comparisonFile << it->second;
            ++it;
        }
        if (i != currentMaxStack)
        {
            comparisonFile << ", ";
        }
    }
}

void OutputComparison::fillRow(Stacks& origStacks, Stacks& humStacks)
{
    comparisonFile << ", ";
    fillColumWithData(origStacks);
    comparisonFile << ", ";
    fillColumWithData(humStacks);
    comparisonFile << std::endl;
}

//void fillWithCero()
//{
//recorrer todo el archivo y agregar 0 dnd corresponda
//}

//Funcion que completa el archivo con un mapa
void OutputComparison::save(Stacks& origStacks, Stacks& humStacks)
{
    const size_t limit = maximumStack(origStacks, humStacks);
    //const size_t currentPos = comparisonFile.tellp();
    updateSubHeader(limit);
    //comparisonFile.seekp(currentPos);
    fillRow(origStacks, humStacks);


    //fseek(0) generar el encabezado posta
}

} // namespace remo