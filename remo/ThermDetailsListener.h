/**
 * @file     ThermDetailsListener.h
 * @details  ThermDetailsListener provides the interface to implement IMotifObserverRemo
 *
 * @author   Franco Riberi
 * @email    fgriberi AT gmail.com
 *
 * Contents: Source file for remo providing ThermDetailsListener interface.
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

#ifndef THERM_DETAILS_LISTENER_H
#define THERM_DETAILS_LISTENER_H

#include "remo/IMotifObserverRemo.h"

namespace remo
{

/** @brief ThermDetailsListener provides the interface to implement IMotifObserverRemo.
 *
 */
class ThermDetailsListener : public IMotifObserverRemo
{
private:

    /** @brief Start observer
     *
     * @return void
     */
    virtual void start();

    /** @brief Process current motif
     *
     * @param motif: motif to analyze
     * return void
     */
    virtual void processMotif(const Motif& motif);

    /** @brief Finalize observer
     *
     * @return void
     */
    virtual void finalize();

    /** @brief Get data about stacks
     *
     * @param data: to fill
     * @param void
     */
    virtual void getData(Stacks& data) const;

    /** @brief Set the tolerances
     *
     * @param tb: bulge tolerance value
     * @param ti: interior tolerance value
     * @return void
     */
    virtual void setTolerances(const Tolerance tb, const Tolerance ti);

    /**
     * @brief Clear the observer container
     *
     * @return void
     */
    virtual void cleanContainerData();

    /** @brief Destructor of class
     *
     */
    virtual ~ThermDetailsListener() {}

    /** @brief Determine the amount stacks of a motif and if it broken
     *
     * @param motif: motif to analyze
     * @param tolerance: greater value allowed.
     */
    void process(const Motif& motif, const Tolerance tolerance);

    /** @brief Add current stack size
     *
     * @param sizeStack: to added
     * @return void
     */
    void addStack(const StackSize stackSize);

    /** @brief Represent previous stack size of a motif
     *
     */
    StackSize _oldStackSize;

    /** @brief To fill with data about stacks <stackSize, amount>
     *
     */
    Stacks _currentData;

    /** @brief Represente bulge loop tolerance
     *
     */
    Tolerance _toleranceBulge;

    /** @brief Represente interior loop tolerance
     *
     */
    Tolerance _toleranceInterior;
};

} //namespace remo
#endif /* THERM_DETAILS_LISTENER_H */