/**
 * @file     Exceptions.h
 * @brief    This header defines all remo server exceptions.
 *
 * @author   Franco Riberi
 * @email    fgriberi AT gmail.com
 *
 * Contents: Header file for remo server providing exception definitions.
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

#ifndef REMO_SERVER_EXCEPTIONS_H
#define REMO_SERVER_EXCEPTIONS_H

#include <mili/mili.h>

struct RemoServerExceptionHierarchy {};
typedef mili::GenericException<RemoServerExceptionHierarchy> RemoServerException;

//State exception
class StateException: public RemoServerException
{
public:
    StateException(const std::string& description): RemoServerException(description) {}
};

DEFINE_SPECIFIC_EXCEPTION_TEXT(FileNotFound, RemoServerExceptionHierarchy, "Input file not found.");
DEFINE_SPECIFIC_EXCEPTION_TEXT(InvalidSizeInput, RemoServerExceptionHierarchy, "Invalid input size.");
DEFINE_SPECIFIC_EXCEPTION_TEXT(InvalidOrganism, RemoServerExceptionHierarchy, "Organism is not valid.");
DEFINE_SPECIFIC_EXCEPTION_TEXT(ErrorCodingSection, RemoServerExceptionHierarchy, "Can't determinate coding section.");

#endif /* REMO_SERVER_EXCEPTIONS_H */