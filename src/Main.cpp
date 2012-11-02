/**
 *  @file:      Main.cpp
 *  @details    Main file.\n
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with R-emo. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "getoptpp/getopt_pp.h"
#include "remo/MOP.h"
#include "remo/ICodonUsageModifier.h"
#include "remo/Definitions.h"
#include "remo/Exceptions.h"
#include "remo/OutputsGenerator.h"
#include "remo/TablesGenerator.h"
#include "remo/StatisticalControl.h"

using namespace GetOpt;
using namespace std;
using namespace mili;

struct RemoArguments
{
    string fileNameRNAm;
    string fileNameMicroRNA;
    bool isCirc;
    bool help;
    string humanizer;
    string folder;
    string humanizerArg;
    unsigned int organism;
};

/**
* Show options of usage
*/
void showOptions()
{
    cout << "\n RNAemo - RNA research project\n\n";
    cout << "  The aim of the study is to determine if this bias could be the result of evolutionary \n";
    cout << "  pressure exerted by the miRNA. To achieve this goal massive comparisons should be made \n";
    cout << "  (in the order of 10e7) between  the recognition of the virus natural genome and  the\n";
    cout << "  ''humanized'' genome. The latter may be obtained by replacing codons in the viral \n";
    cout << "  genome, achieving a codon usage ratio similar to the host. \n\n";
    cout << "Usage examples: ./remo -s <rna_m.FASTA> -m <mi_rna.FASTA> -f <folder> -u <humanizer> -a <path> -o <organism>\n\n";
    cout << "Required arguments:\n";
    cout << "   -s,   -rnam      : rnaM sequence in FASTA format. \n";
    cout << "   -m,   -mirna     : miRNA sequence in FASTA format. \n";
    cout << "   -c,              : rnaM is circular. By default false. \n";
    cout << "   -f,   -folder    : folder backends. \n";
    cout << "   -u,   -humanizer : humanizer software. \n\n";
    cout << "Optional arguments\n";
    cout << "   -h,   --help          : Display this message.\n";
    cout << "   -a,   --humanizer-arg : path of geneDesign execute.\n";
    cout << "   -o,   --organism : number of organism. \n";
    cout << "                      1 = S.cerevisiae,  2 = E.coli, 3 = H.sapiens, \n";
    cout << "                      4 = C.elegans, 5 = D.melanogaster, 6 = B.subtilis\n\n";
}

static void parseArguments(GetOpt_pp& args, RemoArguments& remoArgs)
{
    args.exceptions_all();
    args >> OptionPresent('h', "help", remoArgs.help);
    if (!remoArgs.help)
    {
        args
                >> Option('s', "rnam", remoArgs.fileNameRNAm)
                >> Option('m', "mirna", remoArgs.fileNameMicroRNA)
                >> OptionPresent('c', "false", remoArgs.isCirc)
                >> Option('f', "folder", remoArgs.folder)
                >> Option('u', "humanizer", remoArgs.humanizer)
                >> Option('a', "humanizer-arg", remoArgs.humanizerArg, "")
                >> Option('o', "organism", remoArgs.organism)
                ;
    }
}

int main(int argc, char* argv[])
{
    int ret = EXIT_FAILURE;
    GetOpt_pp args(argc, argv);
    RemoArguments remoArgs;

    cerr << getGPL3LicenseText("Remo", "1.0", "Franco Riberi", "2012");

    try
    {
        parseArguments(args, remoArgs);
        if (remoArgs.help)
            showOptions();
        else
        {
            args.end_of_options();
            MOP::startSystem(remoArgs.fileNameRNAm, remoArgs.fileNameMicroRNA, remoArgs.isCirc, remoArgs.folder, remoArgs.humanizer, remoArgs.humanizerArg, remoArgs.organism);
            ret = EXIT_SUCCESS;
        }
    }
    catch (const TooManyOptionsEx&)
    {
        cerr << "You specified more options than necessary. Add -h option. \n";
    }
    catch (const GetOptEx&)
    {
        cerr << "Remo arguments error" << endl;
        cerr << "Please execute remo -h for more information." << endl;
    }
    catch (const exception& e)
    {
        cerr << e.what() << " Try again. Add -h option." << endl;
    }
    catch (const char* msg)
    {
        cerr << msg << endl;
    }
    catch (const string& msg)
    {
        cerr << msg << endl;
    }
    return ret;
}
