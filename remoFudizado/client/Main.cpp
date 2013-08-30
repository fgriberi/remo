/**
 * @file     Main.cpp
 * @brief    Implementation file containing the main application for remo client
 *
 * @author   Franco Riberi
 * @email    fgriberi AT gmail.com
 *
 * Contents: Source file for remo providing the main appication for remo client.
 *
 * System:   remo: RNAemo - RNA research project
 * Language: C++
 *
 * @date     August 2013
 *
 * This file is part of Remo.
 *
 * Copyright (C) 2013 - Franco Riberi, FuDePAN.
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

#include <fud/fud.h>
#include <getoptpp/getopt_pp.h>
#include "FoldProcesor.h"

using namespace fud;
using namespace GetOpt;

static const size_t PORT = 31337;
static const std::string ADDRESS = "127.0.0.1";

/* main program*/
int main(int argc, char** argv)
{
    size_t port(PORT);
    std::string address(ADDRESS.c_str());

    GetOpt_pp ops(argc, argv);
    ops >> Option('a', "address", address) 
        >> Option('p', "port", port) ;

    new FoldProcessor();

    DistributionClient* distribution_client = create_distribution_client(address, port);
    distribution_client->run();

    return 0;
}