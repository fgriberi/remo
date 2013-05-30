/**
 * @file     ThermDetailsListener.h
 * @details  ThermDetailsListener provides the interface to IMotifObserverRemo.
 *
 * @author   Franco Riberi
 * @email    fgriberi AT gmail.com
 *
 * Contents: Header file for ThermDetailsListener interface.
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


#ifndef THERM_DETAILS_LISTENER_h
#define THERM_DETAILS_LISTENER_h

#include "remo/IMotifObserverRemo.h"

namespace remo
{

/** Represent result <stackSize, amount>
 *
 */
typedef std::map<size_t, size_t> Stacks;

/** @brief Class that provides the interface to IMotifObserverRemo
 *
 */
class ThermDetailsListener : public IMotifObserverRemo
{
private:

    /** @brief Get all motifs
     *
     * @param allMotifs: to fill with all motifs
     * retunr void
     */
    virtual void getMotifs(MotifsData& allMotifs) const;

    /** @brief Process current motif
     *
     * @param motif: motif to analyze
     * return void
     */
    virtual void processMotif(const Motif& motif);

    /** @brief Destructor of class
     *
     */
    virtual ~ThermDetailsListener();
};

} // namespace remo
#endif /* THERM_DETAILS_LISTENER_h */