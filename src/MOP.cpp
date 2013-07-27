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
#include <fideo/fideo.h>
#include <acuoso/acuoso.h>
#include "remo/MOP.h"
#include "remo/Exceptions.h"
#include "remo/OutputsGenerator.h"
#include "remo/ComparisonGenerator.h"

/** @brief Temporal methods to execute remo
*
*/
acuoso::ICodonUsageModifier* getDerivedHumanizerBackend(const std::string& derivedKey);

namespace remo
{

/**
* Show available folding and hybridize backends
*/
void MOP::showBackends(const Backend& sList)
{
    Backend::const_iterator pos;
    pos = sList.begin();
    while (pos != sList.end())
    {
        std::cout << " " << *pos;
        pos++;
        if (pos != sList.end())
        {
            std::cout << ",";
        }
        else
        {
            std::cout << "\n";
        }
    }
}

/**
* Show options of usage
*/
void MOP::showOptions()
{
    std::cout << "\n RNAemo - RNA research project\n\n";
    std::cout << "  The aim of the study is to determine if this bias could be the result of evolutionary \n";
    std::cout << "  pressure exerted by the miRNA. To achieve this goal massive comparisons should be made \n";
    std::cout << "  (in the order of 10e7) between  the recognition of the virus natural genome and  the\n";
    std::cout << "  ''humanized'' genome. The latter may be obtained by replacing codons in the viral \n";
    std::cout << "  genome, achieving a codon usage ratio similar to the host. Also allows comparison \n";
    std::cout << "  between secondary structures\n\n";
    std::cout << "Usage examples:\n";
    std::cout << "- Ad hoc method (folding): \n";
    std::cout << "     ./remo -m <method> -s <rna_m.FASTA> -r <mi_rna.FASTA> -f <folder> -u <humanizer> -o <organism> -v <versionOutput>\n\n";
    std::cout << "- More formal (hybridize): \n";
    std::cout << "     ./remo -m <method> -s <rna_m.FASTA> -r <mi_rna.FASTA> -y <hybridize> -u <humanizer> -o <organism> -v <versionOutput>\n\n";
    std::cout << "- Compariso strucutre: \n";
    std::cout << "     ./remo -s <rna_m.FASTA> -u <humanizer> -o <organism> -v <versionOutput> -b <toleranceOfBulge> -i <toleranceOfInterior>\n\n";
    std::cout << "Required arguments:\n";
    std::cout << "   -m,   --method        : method to use: OldTablesGenerator (folding) \n";
    std::cout << "                                              NewTablesGenerator (hybridize) \n";
    std::cout << "   -s,   --rnam           : rnaM sequence in FASTA format. \n";
    std::cout << "   -r,   --mirna          : miRNA sequence in FASTA format. \n";
    std::cout << "   -f,   --folder         : folder backends: ";
    Backend foldingList;
    fideo::IFold* fold;
    fold->getAvailableBackends(foldingList);
    showBackends(foldingList);

    std::cout << "   -y,   --hybridize      : hybridize backends: ";
    Backend hybridizeList;
    fideo::IHybridize* hybridize;
    hybridize->getAvailableBackends(hybridizeList);
    showBackends(hybridizeList);

    std::cout << "   -u,   --humanizer      : humanizer software: ";
    Backend humanizerBackends;
    acuoso::ICodonUsageModifier* codonUsage;
    codonUsage->getAvailableBackends(humanizerBackends);
    showBackends(humanizerBackends);

    std::cout << "   -o,   --organism      : number of organism: 1 = S.cerevisiae,  2 = E.coli, 3 = H.sapiens, \n";
    std::cout << "                                               4 = C.elegans, 5 = D.melanogaster, 6 = B.subtilis\n";
    std::cout << "   -v,   --versionOutput : type of output: analysis, comparison \n";
    std::cout << "Optional arguments\n";
    std::cout << "   -c,                   : rnaM is circular. By default false. \n";
    std::cout << "   -b,   --tBulge        : tolerance of Bulge Loop. By default 0. \n";
    std::cout << "   -i,   --tInterior     : tolerance of Interior Loop. By default 0. \n";
    std::cout << "   -h,   --help          : Display this message." << std::endl;
}

/** @brief Represents options to remo
*
*/
static const std::string ANALYSIS = "analysis";
static const std::string COMPARISON = "comparison";

void MOP::parseArguments(GetOpt::GetOpt_pp& args, RemoArguments& remoArgs)
{
    args >> GetOpt::OptionPresent('h', "help", remoArgs.help);
    args.exceptions_all();
    if (!remoArgs.help)
    {
        args
                >> GetOpt::Option('s', "rnam", remoArgs.fileNameRNAm)
                >> GetOpt::Option('r', "mirna", remoArgs.fileNameMicroRNA, "")
                >> GetOpt::OptionPresent('c', "circular", remoArgs.isCirc)
                >> GetOpt::Option('u', "humanizer", remoArgs.humanizer)
                >> GetOpt::Option('o', "organism", remoArgs.organism)
                >> GetOpt::Option('m', "method", remoArgs.method, "OldTablesGenerator")
                >> GetOpt::Option('b', "tBulge", remoArgs.toleranceOfBulge, size_t(0))
                >> GetOpt::Option('i', "tInterior", remoArgs.toleranceOfInterior, size_t(0))
                >> GetOpt::Option('v', "versionOutput", remoArgs.typeOutput)
                ;
        //check correct typeOutput
        if ((remoArgs.typeOutput != ANALYSIS) && (remoArgs.typeOutput != COMPARISON))
        {
            throw InvalidOutput();
        }
    }
    else
    {
        showOptions();
    }
}

void MOP::startSystem(GetOpt::GetOpt_pp& args)
{
    RemoArguments remoArgs;
    parseArguments(args, remoArgs);
    bioppFiler::FastaParser<biopp::NucSequence> fileMsg(remoArgs.fileNameRNAm);

    //humanizer
    std::auto_ptr<acuoso::ICodonUsageModifier> humanizerImpl(getDerivedHumanizerBackend(remoArgs.humanizer));
    
    //set organism
    if (remoArgs.organism < acuoso::ICodonUsageModifier::numberOfOrganisms && remoArgs.organism >= acuoso::ICodonUsageModifier::minimumValue)
    {
        humanizerImpl->setOrganism(acuoso::ICodonUsageModifier::Organism(remoArgs.organism));
    }
    else
    {
        throw InvalidOrganism();
    }

    //set type operation
    if (remoArgs.typeOutput == ANALYSIS)
    {
        //Analysis RNAm vs. miRNA
        bioppFiler::FastaParser<biopp::NucSequence> fileMicro(remoArgs.fileNameMicroRNA);
        std::auto_ptr<TablesGenerator> tabGen(mili::FactoryRegistry<TablesGenerator, string>::new_class(remoArgs.method));
        if (tabGen.get() == NULL)
        {
            throw ErrorCreateFactory();
        }

        tabGen->initialize(args); //create concrete instance to 'folding' or 'hybridize'
        args.end_of_options();
        OutputsGenerator::generateOutput(fileMsg, remoArgs.isCirc, fileMicro, humanizerImpl.get(), tabGen.get());
    }
    else
    {
        //Comparison structures
        args.end_of_options();
        ComparisonGenerator comparison;
        comparison.generateComparison(fileMsg, remoArgs.isCirc, humanizerImpl.get(), remoArgs.toleranceOfBulge, remoArgs.toleranceOfInterior);
    }
}
} // namespace remo
