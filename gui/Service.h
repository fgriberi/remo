/*
 * @file     Service.h
 * @brief    Provide the interface to Service window.
 *
 * @author   Franco Riberi
 * @email    fgriberi AT gmail.com
 *
 * Contents: Source file for r-emo providing Service interface.
 *
 * Language: C++
 *
 * @date      September 2013
 *
 * This file is part of r-emo.
 *
 * Copyright (C) 2013 - Franco Riberi, FuDePAN.
 *
 * r-emo is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * r-emo is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with r-emo. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef SERVICE_H
#define SERVICE_H

#include <string>
#include <list>

class Service
{

public:
    static void startRemo(const std::string& cmd);
    static void getFoldingBackend(std::list<std::string>& backends);
    static void getHybridizeBackend(std::list<std::string>& backends);
    static void getHumanizerBackend(std::list<std::string>& backends);
    
    static void generateArgumentToAnalysis(const std::string& rnam, const std::string& mirna,
                                           const std::string& method, const std::string& humanizer,
                                           const std::string& backend, const bool circ, const size_t org,
                                           std::string& cmd, const bool prefold, const bool dontFold);

    static void generateArgumentToComparison(const std::string& rnam, const std::string& humanizer,
                                             const bool circ, const size_t org, const std::string& tBulge,
                                             const std::string& tInterior, std::string& cmd, const bool prefold, const bool dontFold);
};

#endif
