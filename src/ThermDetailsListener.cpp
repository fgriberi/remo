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

#include <list>
#include "remo/ThermDetailsListener.h"

namespace remo
{

ThermDetailsListener::~ThermDetailsListener()
{}

void ThermDetailsListener::getMotifs(MotifsData& allMotifs) const
{
    allMotifs = motifs;
}

void ThermDetailsListener::processMotif(const Motif& motif)
{
    motifs.push_back(motif);
}

} // namespace remo