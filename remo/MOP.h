/**
 *  @file:      MOP.h
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

#ifndef MOP_H
#define MOP_H

#include <string>
#include "remo/Definitions.h"

class MOP
{

public:
    /**
     * Program started
     * @param file name of messenger ARN
     * @param file name of micro ARN
     * @param sequence is circular (flag)
     * @param folder name
     * @param humanizer name
     * @param path name of humanizer software
     * @return
     */
    static void startSystem(const std::string& fileRNAm, const std::string& fileMicroRNA, const bool isCirc, const std::string& folder, const std::string& humanizer, const std::string& humanizerArg, const Organism org);

};
#endif /* MOP_H */
