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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with R-emo. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "getoptpp/getopt_pp.h"
#include "remo/remo.h"

using namespace GetOpt;
using namespace std;
using namespace mili;

int main(int argc, char* argv[])
{
    cerr << getGPL3LicenseText("Remo", "1.1", "Franco Riberi", "2012");
    int ret = EXIT_FAILURE;
    GetOpt_pp args(argc, argv);
    try
    {
        MOP::startSystem(args);
        ret = EXIT_SUCCESS;
    }
    catch (const TooManyOptionsEx&)
    {
        cerr << "You specified more options than necessary. Add -h option. \n";
    }
    catch (const GetOptEx&)
    {
        cerr << "Remo arguments error" << endl;
        cerr << "Please execute remo -h for more information." << endl;
    }
    catch (const exception& e)
    {
        cerr << e.what() << " Try again. Add -h option." << endl;
    }
    catch (const char* msg)
    {
        cerr << msg << endl;
    }
    catch (const string& msg)
    {
        cerr << msg << endl;
    }
    return ret;
}
