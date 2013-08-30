/**
 * @file     Main.cpp
 * @brief    Implementation file containing the main application for remo server.
 *
 * @author   Franco Riberi
 * @email    fgriberi AT gmail.com
 *
 * Contents: Source file for remo providing the main appication for remo server.
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

#include <fud/fud.h>
#include <acuoso/acuoso.h>
#include <getoptpp/getopt_pp.h>
#include "OriginalJobDistributable.h"
#include "HumanizedJobDistributable.h"
#include "Exceptions.h"

using namespace fud;
using namespace GetOpt;

static const size_t PORT = 31337;
static const std:: string GENE_DESIGN = "GeneDesign";
static const size_t ORGANISM = 3; //human

acuoso::ICodonUsageModifier* getDerivedHumanizerBackend(const std::string& derivedKey);

static bool isValidOrganism(const size_t organism)
{
    return (organism < acuoso::ICodonUsageModifier::numberOfOrganisms) && (organism >= acuoso::ICodonUsageModifier::minimumValue);
}

int main(int argc, char** argv)
{    
    size_t port(PORT);
    std::string humanizer(GENE_DESIGN.c_str());
    size_t organism(ORGANISM);
    std::string file;

    GetOpt_pp ops(argc, argv);
    ops >> Option('p', "port", port)
        >> GetOpt::Option('u', "humanizer", humanizer)
        >> GetOpt::Option('o', "organism", organism)
        >> GetOpt::Option('s', "rnam", file);

    //humanizer initialize
    std::auto_ptr<acuoso::ICodonUsageModifier> humanizerImpl(getDerivedHumanizerBackend(humanizer));
    
    //set organism
    mili::assert_throw<InvalidOrganism>(isValidOrganism(organism));
    humanizerImpl->setOrganism(acuoso::ICodonUsageModifier::Organism(organism));

    OriginalJobDistributable* originalSeqJob = new OriginalJobDistributable(file); 
    HumanizedJobDistributable* humanizedSeqJob = new HumanizedJobDistributable(file, humanizerImpl.get()); 
    originalSeqJob->run();
    humanizedSeqJob->run();    
    originalSeqJob->wait_completion();
    humanizedSeqJob->wait_completion();

    fud::finish();
    delete originalSeqJob;
    delete humanizedSeqJob;
}