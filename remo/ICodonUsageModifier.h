/**
 *  @file:      ICodonUsageModifier.h
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
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with R-emo. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef I_CODON_USAGE_MODIFIER_H
#define I_CODON_USAGE_MODIFIER_H

#include <biopp/biopp.h>
#include "remo/Definitions.h"

/**
 * Interface for sequence's humanized services.
 */
struct ICodonUsageModifier
{
public:

    enum Organism
    {
        _minimumValue = 1,
        SCerevisiae = _minimumValue,
        EColi,
        HSapiens, //human
        CElegans,
        DMelanogaster,
        BSubtilis,
        number_of_organisms
    };

    /**
     * Humanized an messenger ARN sequence.
     * @param sequence the messenger ARN to humanized.
     * @param sequence the messenger ARN as result.
     * @return
     */
    virtual void changeCodonUsage(const biopp::AminoSequence& src, biopp::NucSequence& dest) const = 0;

    /**
     * Set organism to humanizer.
     * @param size_t organismo
     * @return
     */
    virtual void setOrganism(Organism org) = 0;

    /**
     * Class destroyer
     */
    virtual ~ICodonUsageModifier() {}
};

#endif /* I_CODON_USAGE_MODIFIER_H */
