/**
 * @file     ComparisonGenerator.cpp
 * @details  ComparisonGenerator is the implementation of ComparisonGenerator interface
 *
 * @author   Franco Riberi
 * @email    fgriberi AT gmail.com
 *
 * Contents: Source file for remo providing ComparisonGenerator implementation.
 *
 * System:   remo: RNAemo - RNA research project
 * Language: C++
 *
 *  @date    March 26, 2013
 *
 * This file is part of R-emo.
 *
 * Copyright (C) 2013 - Franco Riberi, FuDePAN.
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

#include "remo/ComparisonGenerator.h"
#include "remo/Exceptions.h"
#include "remo/OutputsGenerator.h"
#include "remo/ThermDetailsListener.h"

/** @brief Temporal method
*
*/
fideo::IFold* getDerivedFold(const std::string& derivedKey);

namespace remo
{

static const std::string FILE_NAME = "comparisonSeconStructure.csv";
static const size_t CANT_NUC = 3;
static const std::string BACKEND = "UNAFold"; //Single backend that generate .det file

ComparisonGenerator::ComparisonGenerator()
{
    folder = getDerivedFold(BACKEND);
    if (folder == NULL)
    {
        throw InvalidFolder();
    }
}

ComparisonGenerator::~ComparisonGenerator()
{
    //delete folder;
}

void ComparisonGenerator::getDataOfSequence(const biopp::NucSequence& sequence, const bool circ, biopp::SecStructure& structure,
        fideo::IMotifObserver* observer) const
{
    folder->fold(sequence, circ, structure, observer);
}

void ComparisonGenerator::addStack(const size_t sizeStack, Stacks& currentStacks)
{
    const Stacks::const_iterator it = currentStacks.find(sizeStack);
    if (it != currentStacks.end())
    {
        currentStacks[sizeStack]++;
    }
    else
    {
        currentStacks[sizeStack] = 1;
    }
}

/** @brief Represent the matif names
*
*/
static const std::string INTERIOR_ASYMMETRIC = "Interior Asymmetric";
static const std::string INTERIOR_SYMMETRIC  = "Interior Symmetric";
static const std::string HAIRPIN_LOOP        = "Hairpin loop";
static const std::string MULTI_LOOP          = "Multi-loop";
static const std::string BULGE_LOOP          = "Bulge loop";

void ComparisonGenerator::calculateSpecificMotifStacks(const IMotifObserverRemo::Motif motif, const size_t tolerance, size_t& previous, Stacks& currentStacks)
{
    if (motif.attribute >= tolerance) //broken stacks
    {
        addStack(previous, currentStacks);
        previous = motif.amountStacks;
    }
    else
    {
        previous += motif.amountStacks;
    }
}

void ComparisonGenerator::calculateStacks(const IMotifObserverRemo::MotifsData motifs, const size_t toleranceOfBulge, const size_t toleranceOfInterior, Stacks& currentStacks)
{
    IMotifObserverRemo::MotifsData::const_iterator current = motifs.begin();
    size_t previousStacks = current->amountStacks;
    ++current;
    size_t tolerance;
    while (current != motifs.end())
    {
        const bool brokenStack = ((current->nameMotif == MULTI_LOOP)
                                  || (current->nameMotif == HAIRPIN_LOOP));
        if (brokenStack)
        {
            addStack(previousStacks, currentStacks);
            previousStacks = current->amountStacks;
        }
        else
        {
            if (current->nameMotif == BULGE_LOOP)
            {
                tolerance = toleranceOfBulge;
            }
            else if ((current->nameMotif == INTERIOR_ASYMMETRIC) || (current->nameMotif == INTERIOR_SYMMETRIC))
            {
                tolerance = toleranceOfInterior;
            }
            calculateSpecificMotifStacks(*current, tolerance, previousStacks, currentStacks);
        }
        ++current;
    }
    if (previousStacks != 0)
    {
        addStack(previousStacks, currentStacks);
    }
}

void ComparisonGenerator::processSequence(biopp::NucSequence& sequence, const bool circ, biopp::SecStructure& structure,
        IMotifObserverRemo* obs, const size_t tb, const size_t ti, Stacks& currentStacks)
{
    IMotifObserverRemo::MotifsData motifs;
    motifs.clear();
    getDataOfSequence(sequence, circ, structure, obs);
    obs->getMotifs(motifs);
    calculateStacks(motifs, tb, ti, currentStacks);
}

void ComparisonGenerator::generateComparison(bioppFiler::FastaParser<biopp::NucSequence>& fileRNAm, const bool circ,
        const acuoso::ICodonUsageModifier* humanizer, const size_t toleranceOfBulge,
        const size_t toleranceOfInterior)
{
    StacksSave data;
    biopp::NucSequence origRNAm;
    biopp::NucSequence humanizedRNAm;
    biopp::SecStructure structureOrig;
    biopp::SecStructure structureHumanized;
    std::string description;
    OutputComparison comparison(FILE_NAME.c_str());
    IMotifObserverRemo* observer = new ThermDetailsListener();
    while (fileRNAm.getNextSequence(description, origRNAm))
    {
        if (OutputsGenerator::validateSizeOfSequece(origRNAm, description))
        {
            processSequence(origRNAm, circ, structureOrig, observer, toleranceOfBulge, toleranceOfInterior, stacksOrig);
            OutputsGenerator::getHumanizedSequence(origRNAm, humanizer, humanizedRNAm);
            processSequence(humanizedRNAm, circ, structureHumanized, observer, toleranceOfBulge, toleranceOfInterior, stacksHum);
            OutputsGenerator::parseFileName(description, data.nameSequence);
            data.orig = stacksOrig;
            data.hum = stacksHum;
            stacksStore.push_back(data);
        }
    }
    comparison.save(stacksStore);
}

} // namespace remo
