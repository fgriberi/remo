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

void MOP::optionToPrefold(bioppFiler::FastaParser<biopp::NucSequence>& fileMsg, const bool circ, const acuoso::ICodonUsageModifier* humanizer)
{
    PreFold folding;
    folding.prefold(fileMsg, circ, humanizer);
}

void MOP::optionToAnalysis(GetOpt::GetOpt_pp& args, const OptionUsage& method, bioppFiler::FastaParser<biopp::NucSequence>& fileMsg, const bool  circ, const OptionUsage& fileMiRna,
                           const acuoso::ICodonUsageModifier* humanizer, const bool dontFold)
{
    bioppFiler::FastaParser<biopp::NucSequence> fileMicro(fileMiRna);
    std::auto_ptr<TablesGenerator> tabGen(mili::FactoryRegistry<TablesGenerator, string>::new_class(method));
    mili::assert_throw<ErrorCreateFactory>(tabGen.get() != NULL);
    tabGen->initialize(args); //create concrete instance to 'folding' or 'hybridize'
    OutputsGenerator::generateOutput(fileMsg, circ, fileMicro, humanizer, dontFold, tabGen.get());
}

void MOP::optionToComparison(bioppFiler::FastaParser<biopp::NucSequence>& fileMsg, const bool circ, const acuoso::ICodonUsageModifier* humanizer,
                             const bool dontFold, const size_t toleranceOfBulge, const size_t toleranceOfInterior)
{
    ComparisonGenerator comparison;
    comparison.generateComparison(fileMsg, circ, humanizer, dontFold, toleranceOfBulge, toleranceOfInterior);
}

void MOP::startSystem(GetOpt::GetOpt_pp& args, const RemoArguments& remoArgs)
{
    bioppFiler::FastaParser<biopp::NucSequence> fileMsg(remoArgs.fileNameRNAm);

    //humanizer
    std::auto_ptr<acuoso::ICodonUsageModifier> humanizerImpl(getDerivedHumanizerBackend(remoArgs.humanizer));

    //set organism
    mili::assert_throw<InvalidOrganism>(isValidOrganism(remoArgs.organism));
    humanizerImpl->setOrganism(acuoso::ICodonUsageModifier::Organism(remoArgs.organism));

    //process options
    if (remoArgs.prefold)
    {
        optionToPrefold(fileMsg, remoArgs.isCirc, humanizerImpl.get());
    }
    if (remoArgs.analysisOption)
    {
        optionToAnalysis(args, remoArgs.method, fileMsg, remoArgs.isCirc, remoArgs.fileNameMicroRNA, humanizerImpl.get(), remoArgs.dontFold);
    }
    if (remoArgs.comparisonOption)
    {
        optionToComparison(fileMsg, remoArgs.isCirc, humanizerImpl.get(), remoArgs.dontFold, remoArgs.toleranceOfBulge, remoArgs.toleranceOfInterior);
    }
}

} // namespace remo