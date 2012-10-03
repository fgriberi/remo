/**
 *  @file:      IHumanized.h
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with R-emo .  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef I_HUMANIZED_H
#define I_HUMANIZED_H

#include <biopp/biopp.h>
//#include <biopp-filer/bioppFiler.h>

/**
 * Interface for sequence's humanized services.
 */
class IHumanized
{
public:
    /**
     * Humanized an messenger ARN sequence
     * @param file the messenger ARN to humanized.
     * @return
     */
//    virtual void humanized(const bioppFiler::FastaParser<biopp::NucSequence>& rna_m_file) const = 0;

    virtual ~IHumanized() {}
};

#endif /* I_HUMANIZED_H */
