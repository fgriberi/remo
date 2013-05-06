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

#include <getoptpp/getopt_pp.h>
#include "remo/Definitions.h"

using namespace std;

class MOP
{
public:
    /**
     * Program started
     * @param object to parser
     */
    static void startSystem(GetOpt::GetOpt_pp& args);

private:  
    typedef std::list<std::string> Backend;

    struct RemoArguments
    {
        std::string fileNameRNAm;
        std::string fileNameMicroRNA;
        bool isCirc;
        bool help;
        std::string humanizer;
        std::string folder;
        std::string hybridize;
        std::string humanizerArg;
        size_t organism;
        std::string typeOutput;
    };

    static void showOptions();

    static void showBackends(const Backend& sList); 

    static void parseArguments(GetOpt::GetOpt_pp& args, RemoArguments& remoArgs);
};
#endif /* MOP_H */
