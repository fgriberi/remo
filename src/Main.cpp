/**
 * @file     Main.cpp
 * @brief    Main file of remo.
 *
 * @author   Franco Riberi
 * @email    fgriberi AT gmail.com
 *
 * Contents: Source file for remo providing Main implementation.
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

#include <fideo/fideo.h>
#include <acuoso/acuoso.h>
#include <getoptpp/getopt_pp.h>
#include <mili/mili.h>
#include "remo/MOP.h"
#include "remo/Exceptions.h"

typedef std::list<std::string> Backend;

/** @brief Displays all registered backends
 *
 * @param to fill with specific backends registered
 * @return void
 */
void showBackends(const Backend& sList)
{
    Backend::const_iterator pos;
    for (pos = sList.begin(); pos != sList.end(); ++pos)
    {
        std::cout << "                        " << *pos << std::endl;
    }
}

/** @brief Show all remo options of usage
 *
 *  @return void
 */
void showHelp()
{
    std::cout << "\n RNAemo - RNA research project\n\n";
    std::cout << "  The aim of the study is to determine if this bias could be the result of evolutionary \n";
    std::cout << "  pressure exerted by the miRNA. To achieve this goal massive comparisons should be made \n";
    std::cout << "  (in the order of 10e7) between  the recognition of the virus natural genome and  the\n";
    std::cout << "  ''humanized'' genome. The latter may be obtained by replacing codons in the viral \n";
    std::cout << "  genome, achieving a codon usage ratio similar to the host. Also allows comparison \n";
    std::cout << "  between secondary structures\n\n";
    std::cout << "Usage examples:\n";
    std::cout << "- Prefold: \n";
    std::cout << "     ./install/bin/remo -s <rna_m.FASTA> -u <humanizer> -o <organism> -p\n\n";
    std::cout << "- Ad hoc method (folding): \n";
    std::cout << "     ./install/bin/remo -m <method> -s <rna_m.FASTA> -r <mi_rna.FASTA> -f <folder> -u <humanizer> -o <organism> -a\n\n";
    std::cout << "- More formal (hybridize): \n";
    std::cout << "     ./install/bin/remo -m <method> -s <rna_m.FASTA> -r <mi_rna.FASTA> -y <hybridize> -u <humanizer> -o <organism> -a\n\n";
    std::cout << "- Compariso strucutre: \n";
    std::cout << "     ./install/bin/remo -s <rna_m.FASTA> -u <humanizer> -o <organism> -c -b <toleranceOfBulge> -i <toleranceOfInterior> \n\n";

    std::cout << "Required Arguments:\n";
    std::cout << "   -a,   --analysis       : Analysis mRNA vs. miRNA \n";
    std::cout << "   -c,   --comparison     : Comparison secondary structure of mRNA \n";
    std::cout << "   -m,   --method         : method to use: OldTablesGenerator (folding) \n";
    std::cout << "                                          NewTablesGenerator (hybridize) \n";
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
    std::cout << "   -d,   --dontFold      : Using existing files. By default false. \n";
    std::cout << "   -h,   --help          : Display this message." << std::endl;
}

/** @brief Parser input arguments
 *
 * @param args: object to parser
 * @param remoArgs: to fill with parser
 * @return void
 */
void parseArguments(GetOpt::GetOpt_pp& args, remo::MOP::RemoArguments& remoArgs)
{
    args >> GetOpt::OptionPresent('h', "help", remoArgs.help)
         >> GetOpt::OptionPresent('p', "prefold", remoArgs.prefold)
         >> GetOpt::OptionPresent('c', "comparison", remoArgs.comparisonOption)
         >> GetOpt::OptionPresent('a', "analysis", remoArgs.analysisOption)
         >> GetOpt::OptionPresent('d', "dontFold", remoArgs.dontFold);
    if (remoArgs.analysisOption)
    {
        args >> GetOpt::Option('r', "mirna", remoArgs.fileNameMicroRNA)
             >> GetOpt::Option('m', "method", remoArgs.method, "OldTablesGenerator");
    }
    if (remoArgs.comparisonOption)
    {
        args >> GetOpt::Option('b', "tBulge", remoArgs.toleranceOfBulge, size_t(0))
             >> GetOpt::Option('i', "tInterior", remoArgs.toleranceOfInterior, size_t(0));
    }
    args
            >> GetOpt::Option('s', "rnam", remoArgs.fileNameRNAm)
            >> GetOpt::OptionPresent('q', "circular", remoArgs.isCirc)
            >> GetOpt::Option('u', "humanizer", remoArgs.humanizer)
            >> GetOpt::Option('o', "organism", remoArgs.organism);
    args.end_of_options();
}

/** @brief The main program
 *
 */
int main(int argc, char* argv[])
{
    int ret = EXIT_FAILURE;
    GetOpt::GetOpt_pp args(argc, argv);
    remo::MOP::RemoArguments remoArgs;

    std::cerr << mili::getGPL3LicenseText("Remo", "1.3", "Franco Riberi", "2013");
    try
    {
        parseArguments(args, remoArgs);
        const bool notOneOfThisOption = !remoArgs.prefold  && !remoArgs.comparisonOption && !remoArgs.analysisOption;
        if ((remoArgs.help) || (notOneOfThisOption))
        {
            showHelp();
        }
        else
        {
            remo::MOP::startSystem(args, remoArgs);
        }
        ret = EXIT_SUCCESS;
    }
    catch (const GetOpt::TooManyOptionsEx&)
    {
        std::cerr << "You specified more options than necessary. Add -h option. \n";
    }
    catch (const GetOpt::GetOptEx&)
    {
        std::cerr << "Remo arguments error" << std::endl;
        std::cerr << "Please execute remo -h for more information." << std::endl;
    }
    catch (...)
    {
        std::cerr << "Unknown error" << std::endl;
    }
    return ret;
}