/**
 * @file     Exceptions.h
 * @brief    This header defines all Remo exceptions
 *
 * @author   Franco Riberi
 * @email    fgriberi AT gmail.com
 *
 * Contents: Header file for remo providing system exceptions definitions.
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

#ifndef REMO_EXCEPTIONS_H
#define REMO_EXCEPTIONS_H

#include <mili/mili.h>

namespace remo
{

struct RemoExceptionHierarchy {};
typedef mili::GenericException<RemoExceptionHierarchy> RemoException;

//State exception
class StateException: public RemoException
{
public:
    StateException(const std::string& description): RemoException(description) {}
};

//File exceptions
DEFINE_SPECIFIC_EXCEPTION_TEXT(FileNotFound, RemoExceptionHierarchy, "Input file not found.");

//MOP exceptions
DEFINE_SPECIFIC_EXCEPTION_TEXT(InvalidHumanizer, RemoExceptionHierarchy, "Humanizer software is not valid.");
DEFINE_SPECIFIC_EXCEPTION_TEXT(InvalidFolder, RemoExceptionHierarchy, "Folder backend is not valid.");
DEFINE_SPECIFIC_EXCEPTION_TEXT(InvalidHybridize, RemoExceptionHierarchy, "Hybridize backend is not valid.");
DEFINE_SPECIFIC_EXCEPTION_TEXT(ErrorCreateFactory, RemoExceptionHierarchy, "Error creating factory.");
DEFINE_SPECIFIC_EXCEPTION_TEXT(InvalidOrganism, RemoExceptionHierarchy, "Organism is not valid.");

//GeneDesign exceptions
DEFINE_SPECIFIC_EXCEPTION_TEXT(InvalidLengthSequence, RemoExceptionHierarchy, "RNA messenger length is not multiple of 3.");
DEFINE_SPECIFIC_EXCEPTION_TEXT(InvalidPathChdir, RemoExceptionHierarchy, "Error in chdir path.");
DEFINE_SPECIFIC_EXCEPTION_TEXT(ErrorHumanizer, RemoExceptionHierarchy, "Error in the humanization.");
DEFINE_SPECIFIC_EXCEPTION_TEXT(EmptySequence, RemoExceptionHierarchy, "Empty humanized sequence.");
DEFINE_SPECIFIC_EXCEPTION_TEXT(OrganismNotSupported, RemoExceptionHierarchy, "Organism not supported.");

//TableGenerator exceptions
DEFINE_SPECIFIC_EXCEPTION_TEXT(FileNotCreate, RemoExceptionHierarchy, "Can't create output file.");

//OutputsGenerator exceptions
DEFINE_SPECIFIC_EXCEPTION_TEXT(InvalidDescriptionMiRNA, RemoExceptionHierarchy, "Invalid description of miRNA.");
DEFINE_SPECIFIC_EXCEPTION_TEXT(ErrorCodingSection, RemoExceptionHierarchy, "Can't determinate coding section.");
DEFINE_SPECIFIC_EXCEPTION_TEXT(ErrorTypeOutput, RemoExceptionHierarchy, "Error in type of output");

} // namespace remo
#endif /* REMO_EXCEPTIONS_H */