/**
 * @file     ThermDetailsListener.cpp
 * @details  Is an implementation of ThermDetailsListener interface.
 *
 * @author   Franco Riberi
 * @email    fgriberi AT gmail.com
 *
 * Contents: Source file for remo providing ThermDetailsListener implementation.
 *
 * System:   remo: RNAemo - RNA research project
 * Language: C++
 *
 * @date     March 26, 2013
 *
 * This file is part of R-emo.
 *
 * Copyright (C) 2013 - Franco Riberi, FuDePAN.
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

#include "remo/ThermDetailsListener.h"

namespace remo
{

void ThermDetailsListener::setTolerances(const Tolerance tb, const Tolerance ti)
{
    _toleranceBulge = tb;
    _toleranceInterior = ti;
}

void ThermDetailsListener::addStack(const StackSize stackSize)
{
    const Stacks::const_iterator it = _currentData.find(stackSize);
    if (it != _currentData.end())
    {
        _currentData[stackSize]++;
    }
    else
    {
        _currentData[stackSize] = 1;
    }
}

void ThermDetailsListener::getData(Stacks& data) const
{
    data = _currentData;
}

void ThermDetailsListener::process(const Motif& motif, const Tolerance tolerance)
{
    if (motif.attribute >= tolerance) //broken stacks
    {
        addStack(_oldStackSize);
        _oldStackSize = motif.amountStacks;
    }
    else
    {
        _oldStackSize += motif.amountStacks;
    }
}

/** @brief Represent the matif names
*
*/
static const std::string INTERIOR_ASYMMETRIC = "Interior Asymmetric";
static const std::string INTERIOR_SYMMETRIC  = "Interior Symmetric";
static const std::string HAIRPIN_LOOP        = "Hairpin loop";
static const std::string MULTI_LOOP          = "Multi-loop";
static const std::string BULGE_LOOP          = "Bulge loop";
static const std::string EXTERNAL_LOOP       = "External loop";

void ThermDetailsListener::processMotif(const Motif& motif)
{
    if (motif.nameMotif == EXTERNAL_LOOP)
    {
        _oldStackSize = motif.amountStacks;
    }
    else if ((motif.nameMotif == MULTI_LOOP) || (motif.nameMotif == HAIRPIN_LOOP))
    {
        addStack(_oldStackSize);
        _oldStackSize = motif.amountStacks;
    }
    else if (motif.nameMotif == BULGE_LOOP)
    {
        process(motif, _toleranceBulge);
    }
    else if ((motif.nameMotif == INTERIOR_ASYMMETRIC) || (motif.nameMotif == INTERIOR_SYMMETRIC))
    {
        process(motif, _toleranceInterior);
    }
}

void ThermDetailsListener::start()
{}

void ThermDetailsListener::cleanContainerData()
{
    _currentData.clear();
}

void ThermDetailsListener::finalize()
{
    if (_oldStackSize != 0)
    {
        addStack(_oldStackSize);
    }
}

} //namespace remo