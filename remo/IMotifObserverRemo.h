/**
 * @file     IMotifObserverRemo.h
 * @details  IMotifObserverRemo provides the interface to extend fideo::IMotifObserver
 *
 * @author   Franco Riberi
 * @email    fgriberi AT gmail.com
 *
 * Contents: Header file for IMotifObserverRemo interface.
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

#ifndef IMOTIF_OBSERVER_REMO_H
#define IMOTIF_OBSERVER_REMO_H

#include <fideo/fideo.h>

namespace remo
{

/** @brief Represent amount of stacks
 *
 */
typedef size_t AmountStack;

/** @brief Represent a stack size
 *
 */
typedef size_t StackSize;

/** @brief Represent a tolerance of a specific motif
*
*/
typedef size_t Tolerance;

/** Represent result <stackSize, amount>
 *
 */
typedef std::map<StackSize, AmountStack> Stacks;

/** @brief Struct that provides the interface to extend fideo::IMotifObserver
 *
 */
struct IMotifObserverRemo : public fideo::IMotifObserver
{

    /** @brief Rename type motif
     *
     */
    typedef fideo::IMotifObserver::Motif Motif;

    /** @brief Start observer
    *
    * @return void
    */
    virtual void start() = 0;

    /** @brief Process current motif
     *
     * @param motif: motif to analyze
     * return void
     */
    virtual void processMotif(const Motif& motif) = 0;

    /** @brief Finalize observer
    *
    * @return void
    */
    virtual void finalize() = 0;

    /** @brief Get data about stacks
     *
     * @param data: to fill
     * @param void
     */
    virtual void getData(Stacks& data) const = 0;

    /** @brief Set the tolerances
     *
     * @param tb: bulge tolerance value
     * @param ti: interior tolerance value
     * @return void
     */
    virtual void setTolerances(const Tolerance tb, const Tolerance ti) = 0;

    /** @brief Destructor of class
     *
     */
    virtual ~IMotifObserverRemo() {}
};

} //namespace remo
#endif /* IMOTIF_OBSERVER_REMO_H */