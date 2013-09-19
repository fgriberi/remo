/**
 * @file     Service.cpp
 * @brief    Is a implementation of Service interface.
 *
 * @author   Franco Riberi
 * @email    fgriberi AT gmail.com
 *
 * Contents: Source file for r-emo providing Service implementation.
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

#include <iostream>
#include <memory>
#include <sstream>
#include <acuoso/acuoso.h>
#include <fideo/fideo.h>
#include <etilico/etilico.h>
#include "Service.h"

fideo::IFold* getDerivedFold(const std::string& derivedKey);

void Service::startRemo(const std::string& cmd)
{
    etilico::Command command = cmd;
    etilico::runCommand(command);
}

void Service::getFoldingBackend(std::list<std::string>& backends)
{
    std::auto_ptr<fideo::IFold> tmpFold(getDerivedFold("UNAFold"));
    tmpFold->getAvailableBackends(backends);    
}

void Service::getHybridizeBackend(std::list<std::string>& backends)
{
    fideo::IHybridize::getAvailableBackends(backends);
}

void Service::getHumanizerBackend(std::list<std::string>& backends)
{
    acuoso::ICodonUsageModifier::getAvailableBackends(backends);    
}

void Service::generateArgumentToAnalysis(const std::string& rnam, const std::string& mirna,
        const std::string& method, const std::string& humanizer,
        const std::string& backend, const bool circ, const size_t org,
        std::string& cmd, const bool prefold, const bool dontFold)
{  
    std::string command;
    command = "./install/bin/remo -s ";
    command += rnam;
    command += " -m ";
    command += mirna;
    std::string version;
    if (method == "Ad hoc")
    {
        command += " -f ";
        command += backend;
        version = "OldTablesGenerator";
    }
    else
    {
        command += " -y ";
        command += backend;
        version = "NewTablesGenerator";
    }
    command += " -u ";
    command += humanizer;
    command += " -o ";
    std::ostringstream convert;
    convert << org;
    command += convert.str();    
    circ ? command += " -c " : command += "";
    command += " -v ";
    command += version;
    prefold ? command += " -p" : command += "";
    dontFold ? command += " -d" : command += "";
    cmd = command;
}

void Service::generateArgumentToComparison(const std::string& rnam, const std::string& humanizer,
        const bool circ, const size_t org, const std::string& tBulge, const std::string& tInterior,
        std::string& cmd, const bool prefold, const bool dontFold)
{
    std::string command;
    command = "./install/bin/remo -s ";
    command += rnam;
    command += " -u ";
    command += humanizer;
    command += " -o ";
    std::ostringstream convert;
    convert << org;
    command += convert.str();
    circ ? command += " -c " : command += "";
    command += " -tb ";
    command += tBulge;
    command += " -ti ";
    command += tInterior;
    prefold ? command += " -p" : command += "";
    dontFold ? command += " -d" : command += "";
    cmd = command;
}
