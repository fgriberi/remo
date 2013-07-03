/**
 * @file     Main.cpp
 * @brief    Main file of remo.
 *
 * @author   Franco Riberi
 * @email    fgriberi AT gmail.com
 *
 * Contents: Source file for remo providing Main implementation.
 *
 * System:   remo: RNAemo - RNA research project
 * Language: C++
 *
 * @date     October 2012
 *
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

#include <mili/mili.h>
#include "remo/MOP.h"
#include "remo/Exceptions.h"

int main(int argc, char* argv[])
{
    std::cerr << mili::getGPL3LicenseText("Remo", "1.1", "Franco Riberi", "2012");
    int ret = EXIT_FAILURE;
    GetOpt::GetOpt_pp args(argc, argv);
    try
    {
        remo::MOP::startSystem(args);
        ret = EXIT_SUCCESS;
    }
    catch (const GetOpt::TooManyOptionsEx&)
    {
        std::cerr << "You specified more options than necessary. Add -h option. \n";
    }
    catch (const GetOpt::GetOptEx&)
    {
        std::cerr << "Remo arguments error" << std::endl;
        std::cerr << "Please execute remo -h for more information." << std::endl;
    }
    catch (...)
    {
        std::cerr << "Unknown error" << std::endl;
    }
    return ret;
}