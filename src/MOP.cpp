/**
 *  @file:      MOP.cpp
 *  @details    System: R-emo \n
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

#include <memory>
#include "biopp/biopp.h"
#include "fideo/fideo.h"
#include "biopp-filer/bioppFiler.h"
#include "remo/MOP.h"
#include "remo/OutputsGenerator.h"

using namespace std;
using namespace biopp;
using namespace bioppFiler;

void MOP::startSystem(const string& fileRNAm, const string& fileMicroRNA, const bool isCirc, const string& folder, const string& humanizer, const string& humanizerArg)
{
    FastaParser<NucSequence> file_msg(fileRNAm);
    FastaParser<NucSequence> file_micro(fileMicroRNA);

    auto_ptr<IHumanizer> humanizerImpl (mili::FactoryRegistry<IHumanizer, std::string>::new_class(humanizer));
    if (humanizerImpl.get() == NULL)        
        throw "Humanizer not valid"; 
    humanizerImpl->setArgument(humanizerArg);
    
    auto_ptr<IFold> folderImpl (mili::FactoryRegistry<IFold, std::string>::new_class(folder));
    if (folderImpl.get() == NULL)        
        throw "Folder not valid"; 

    OutputsGenerator::generateOutput(file_msg, file_micro, isCirc, humanizerImpl.get(), folderImpl.get());    
}
