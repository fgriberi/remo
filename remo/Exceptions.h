/**
 *  @file:      Exceptions.h
 *  @details    This header defines all R-emo exceptions
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

#ifndef REMO_EXCEPTIONS_H
#define REMO_EXCEPTIONS_H

#include <mili/mili.h>

namespace RemoTools
{

struct RemoExceptionHierarchy {};
typedef mili::GenericException<RemoExceptionHierarchy> RemoException;

//File exceptions
DEFINE_SPECIFIC_EXCEPTION_TEXT(FileNotFound, RemoExceptionHierarchy, "Input file not found");
//use: throw FileNotFound();
}

#endif /* REMO_EXCEPTIONS_H */
