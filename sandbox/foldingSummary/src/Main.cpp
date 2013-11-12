/**
 * @file     Main.cpp
 * @brief    Main file of Remo.
 *
 * @author   Franco Riberi
 * @email    fgriberi AT gmail.com
 *
 * Contents: Source file for remo providing folding summary implementation.
 *
 * System:   remo: RNAemo - RNA research project
 * Language: C++
 *
 * @date     October 2012
 *2
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

#include <acuoso/acuoso.h>
#include <getoptpp/getopt_pp.h>
#include "foldingSummary/Analyse.h"

 /**
 * @brief Parse input parameters
 *
 * @param args input object that contain input options
 * @param remoArgs to fill with input options
 * @return void
 */
static void parseArguments(GetOpt::GetOpt_pp& args, NSAnalyse::Arguments& remoArgs)
{    
    args >> GetOpt::Option('s', "rnam", remoArgs.fileNameRNAm);
    args >> GetOpt::Option('p', "path", remoArgs.pathFiles);
    args.end_of_options();
}

/** 
 * @brief The main program
 */
int main(int argc, char* argv[])
{    
    int ret = EXIT_FAILURE;
    GetOpt::GetOpt_pp args(argc, argv);
    NSAnalyse::Arguments argument;
    try
    {
        parseArguments(args, argument);
        NSAnalyse::Analyse analyse;
        analyse.startAnalysis(argument);
        ret = EXIT_SUCCESS;
    }
    catch (...)
    {
        std::cerr << "Unknown error" << std::endl;   
    }
    return ret;
}