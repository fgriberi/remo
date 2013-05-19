/**
 * @file     MOP.h
 * @brief    MOP interface.
 *
 * @author   Franco Riberi
 * @email    fgriberi AT gmail.com
 *
 * Contents: Header file for remo providing class MOP.
 *
 * System:   remo: RNAemo - RNA research project
 * Language: C++
 *
 * @date 2012
 *
 * Copyright (C) 2012 Franco Riberi, FuDePAN
 *
 * This file is part of the remo.
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

#ifndef MOP_H
#define MOP_H

#include <getoptpp/getopt_pp.h>

namespace remo
{

/** @brief Mediator class
*
*/
class MOP
{
public:

    /** @brief Start program
     *
     * @param args: object containing the input parameters needed
     * @param void
     */
    static void startSystem(GetOpt::GetOpt_pp& args);

private:
    typedef std::list<std::string> Backend;

    /** @brief Structure that represents all the data needed to remo
    *
    */
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

    /** @brief Show all remo options of usage
     *
     *  @return void
     */
    static void showOptions();

    /** @brief Displays all registered backends
     *
     * @param to fill with specific backends registered
     * @return void
     */
    static void showBackends(const Backend& sList);

    /** @brief Parser input arguments
     *
     *  @param args: object to parser
     *  @param remoArgs: to fill with parser
     * @return void
     */
    static void parseArguments(GetOpt::GetOpt_pp& args, RemoArguments& remoArgs);
};

} // namespace remo
#endif /* MOP_H */