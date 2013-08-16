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
#include "remo/IMotifObserverRemo.h"
#include "remo/ThermDetailsListener.h"

/** @brief Temporal method to execute remo
 *
 */
fideo::IFold* getDerivedFold(const std::string& derivedKey);

namespace remo
{

static const std::string FILE_NAME = "/tmp/comparisonSeconStructure.csv";
static const size_t CANT_NUC = 3;
static const std::string BACKEND = "UNAFold"; //Single backend that generate .det file

ComparisonGenerator::ComparisonGenerator()
{    
    _folder = getDerivedFold(BACKEND);    
}

ComparisonGenerator::~ComparisonGenerator()
{
    delete _folder; 
}

void ComparisonGenerator::processSequence(const biopp::NucSequence& sequence, const bool circ, biopp::SecStructure& structure,
                                          const bool dontFold, fideo::FilePath& file, fideo::IMotifObserver* obs)
{
    if (dontFold)
    {                            
        std::ifstream inputFile(file.c_str());                        
        if (!inputFile)
        {                                        
            _folder->foldTo(sequence, circ, structure, file);            
        }
        _folder->foldFrom(file, structure, obs);                    
    }
    else
    {            
        _folder->fold(sequence, circ, structure, obs);
    }
}

static const std::string PREFIX_ORIG = "/tmp/orig-";
static const std::string PREFIX_HUM = "/tmp/hum-";

void ComparisonGenerator::generateComparison(bioppFiler::FastaParser<biopp::NucSequence>& fileRNAm, const bool circ,
                                             const acuoso::ICodonUsageModifier* humanizer, const bool dontFold,
                                             const Tolerance toleranceOfBulge, const Tolerance toleranceOfInterior)
{
    StacksSave currentData; //data of a sequence to save in the outputComparison file    
    biopp::NucSequence origRNAm;
    biopp::NucSequence humanizedRNAm;
    biopp::SecStructure structureOrig;
    biopp::SecStructure structureHumanized;
    std::string description;
    OutputComparison comparison(FILE_NAME.c_str());
    IMotifObserverRemo* observer = new ThermDetailsListener();
    observer->setTolerances(toleranceOfBulge, toleranceOfInterior);
    fideo::FilePath origFile;
    fideo::FilePath humFile;
    fileRNAm.reset();
    while (fileRNAm.getNextSequence(description, origRNAm))
    {
        if (OutputsGenerator::validateSizeOfSequece(origRNAm, description))
        {
            OutputsGenerator::parseFileName(description, currentData.nameSequence);
            
            //process original sequence            
            origFile = PREFIX_ORIG + currentData.nameSequence;
            processSequence(origRNAm, circ, structureOrig, dontFold, origFile, observer);
            observer->getData(currentData.orig);

            //obtain humanized sequence
            OutputsGenerator::getHumanizedSequence(origRNAm, humanizer, humanizedRNAm);                
            
            //process humanized sequence         
            humFile = PREFIX_HUM + currentData.nameSequence;
            processSequence(humanizedRNAm, circ, structureHumanized, dontFold, humFile, observer);
            observer->getData(currentData.hum);                        
            _stacksStore.push_back(currentData);

        }
    }
    comparison.save(_stacksStore);
    delete observer;
}

} // namespace remo