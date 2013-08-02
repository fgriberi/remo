/**
 * @file      MOP.cpp
 * @brief     MOP implements of remo.
 *
 * @author    Franco Riberi
 * @email     fgriberi AT gmail.com
 *
 * Contents:  Source file for remo providing MOP implementation.
 *
 * System:    remo: RNAemo - RNA research project
 * Language:  C++
 *
 * @date      October 2012
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

#include <memory>
#include "remo/MOP.h"
#include "remo/Exceptions.h"
#include "remo/OutputsGenerator.h"
#include "remo/ComparisonGenerator.h"
#include "remo/PreFold.h"

/** @brief Temporal methods to execute remo
*
*/
acuoso::ICodonUsageModifier* getDerivedHumanizerBackend(const std::string& derivedKey);

namespace remo
{

bool MOP::isValidOrganism(const size_t organism)
{
    return (organism < acuoso::ICodonUsageModifier::numberOfOrganisms) && (organism >= acuoso::ICodonUsageModifier::minimumValue);
}

void MOP::startSystem(GetOpt::GetOpt_pp& args, const RemoArguments& remoArgs)
{
    bioppFiler::FastaParser<biopp::NucSequence> fileMsg(remoArgs.fileNameRNAm);

    //humanizer
    std::auto_ptr<acuoso::ICodonUsageModifier> humanizerImpl(getDerivedHumanizerBackend(remoArgs.humanizer));
    
    //set organism
    if (!isValidOrganism(remoArgs.organism))
    {
        throw InvalidOrganism();
    }
    humanizerImpl->setOrganism(acuoso::ICodonUsageModifier::Organism(remoArgs.organism));   
        
    if (remoArgs.prefold)
    {
        PreFold folding;
        folding.prefold(fileMsg, remoArgs.isCirc, humanizerImpl.get());
    }    
    if (remoArgs.analysisOption)
    {
        bioppFiler::FastaParser<biopp::NucSequence> fileMicro(remoArgs.fileNameMicroRNA);
        std::auto_ptr<TablesGenerator> tabGen(mili::FactoryRegistry<TablesGenerator, string>::new_class(remoArgs.method));
        if (tabGen.get() == NULL)
        {
            throw ErrorCreateFactory();
        }

        tabGen->initialize(args); //create concrete instance to 'folding' or 'hybridize'        
        OutputsGenerator::generateOutput(fileMsg, remoArgs.isCirc, fileMicro, humanizerImpl.get(), remoArgs.dontFold, tabGen.get());
    }
    if (remoArgs.comparisonOption)
    {
        ComparisonGenerator comparison;
        comparison.generateComparison(fileMsg, remoArgs.isCirc, humanizerImpl.get(), remoArgs.dontFold, remoArgs.toleranceOfBulge, remoArgs.toleranceOfInterior);
    }
}

} // namespace remo