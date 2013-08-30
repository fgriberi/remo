/**
 * @file     Exceptions.h
 * @brief    This header defines all remo client exceptions
 *
 * @author   Franco Riberi
 * @email    fgriberi AT gmail.com
 *
 * Contents: Header file for remo client providing exception definitions.
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

#ifndef REMO_CLIENT_EXCEPTIONS_H
#define REMO_CLIENT_EXCEPTIONS_H

#include <mili/mili.h>

struct RemoClientExceptionHierarchy {};
typedef mili::GenericException<RemoClientExceptionHierarchy> RemoClientException;

//State exception
class StateException: public RemoClientException
{
public:
    StateException(const std::string& description): RemoClientException(description) {}
};

DEFINE_SPECIFIC_EXCEPTION_TEXT(FileNotFound, RemoClientExceptionHierarchy, "Input file not found.");
DEFINE_SPECIFIC_EXCEPTION_TEXT(InvalidSizeInput, RemoClientExceptionHierarchy, "Invalid input size.");
DEFINE_SPECIFIC_EXCEPTION_TEXT(UnlinkException, RemoClientExceptionHierarchy, "File not found.");

#endif /* REMO_CLIENT_EXCEPTIONS_H */