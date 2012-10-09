/**
 *  @file:      StatisticalControl.h
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

#ifndef STATISTICAL_CONTROL_H
#define STATISTICAL_CONTROL_H

#include <string>
#include <list>

class StatisticalControl
{
public:
    StatisticalControl();

    /**
    * Validar las secuencias de ese archivos respecto a calculos estadisticos
    */
    bool validateSequence(std::string& file_name);
    void generateSequenceRandom(biopp::NucSequence& sequence, std::list<biopp::NucSequence>& list);

    ~StatisticalControl();
};
#endif /* STATISTICAL_CONTROL_H */