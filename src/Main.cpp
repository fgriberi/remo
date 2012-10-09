/**
 *  @file:      Main.cpp
 *  @details    Main file.\n
 *              System: R-emo \n
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

#include "getoptpp/getopt_pp.h"
#include "remo/MOP.h"
#include "remo/IHumanizer.h"
#include "remo/Definitions.h"
#include "remo/Exceptions.h"
#include "remo/OutputsGenerator.h"
#include "remo/TablesGenerator.h"
#include "remo/StatisticalControl.h"
#include "remo/OutputFile.h"

using namespace GetOpt;
using namespace std;

/**
* Muestra opciones de uso.
*/
static void showHelp();

int main(int argc, char* argv[])
{
    GetOpt_pp args(argc, argv);
    int ret = EXIT_FAILURE;
        
    std::string fileNameRNAm;
    std::string fileNameMicroRNA;
    bool isCirc;
    std::string humanizer;
    std::string humanizerPath;
    std::string help;

    if (args >> Option('H', "help", help) >> Option('h', "help", help))
        showHelp();
    args.exceptions_all();
    try
    {
        args
             >> Option('S', "rnam", fileNameRNAm) 
             >> Option('s', "rnam", fileNameRNAm)
             >> Option('M', "mirna", fileNameMicroRNA) 
             >> Option('m', "mirna", fileNameMicroRNA)
             >> OptionPresent('c', "false", isCirc); 
             ;

        if (args >> Option('H', "humanizer", humanizer) >> Option('h', "humanizer", humanizer))
        {
            if (args >> Option('A', "arg", humanizer) >> Option('a', "arg", humanizer))
            {
                MOP system(fileNameRNAm, fileNameMicroRNA, isCirc, humanizerPath);
            }
            else
            {
                MOP system(fileNameRNAm, fileNameMicroRNA, isCirc);
            }
//            system.startSystem();
            ret = EXIT_SUCCESS;
        }
        args.end_of_options(); 
        return ret;        
    }
    catch(TooManyOptionsEx)
    {
       std::cerr << "You specified more options than necessary\n";
    }
    catch(GetOptEx)
    {
       cerr << "Invalid options. Try again\n";
    }
}

void showHelp()
{
    cout << "Usage: ./main -S <rna_m> -M <mi_rna> -C -H <humanizer> [optional] \n";    
    cout << "[optional] \n";
    cout << "-arg PATH \n";    
}

