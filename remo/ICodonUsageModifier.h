/**
 * @file    ICodonUsageModifier.h
 * @brief   ICodonUsageModifier provides the interface to humanizer service.
 *
 * @author  Franco Riberi
 * @email   fgriberi AT gmail.com
 *
 * Contents: Header file for remo providing struct ICodonUsageModifier.
 *
 * System:   remo: RNAemo - RNA research project
 * Language: C++
 *
 * @date    October 2012
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
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Remo. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef I_CODON_USAGE_MODIFIER_H
#define I_CODON_USAGE_MODIFIER_H

#include <biopp/biopp.h>
#include "remo/Definitions.h"

namespace remo
{

///Interface for sequence's humanized services.
struct ICodonUsageModifier
{
    ///Enum that representing all organisms supported
    enum Organism
    {
        minimumValue = 1,
        SCerevisiae = minimumValue,
        EColi,
        HSapiens, //human
        CElegans,
        DMelanogaster,
        BSubtilis,
        numberOfOrganisms
    };

    /** @brief Humanized an messenger ARN sequence.
     *
     * @param src: sequence the messenger RNA to humanized.
     * @param dest: sequence the messenger RNA as result.
     * @return void
     */
    virtual void changeCodonUsage(const biopp::AminoSequence& src, biopp::NucSequence& dest) const = 0;

    /** @brief Set organism to humanizer.
     *
     * @param org: organism to set
     * @return void
     */
    virtual void setOrganism(const Organism org) = 0;

    /** @brief Destructor of class
     *
     */
    virtual ~ICodonUsageModifier() {}
};

} // namespace remo
#endif /* I_CODON_USAGE_MODIFIER_H */
