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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with R-emo. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <memory>
#include "biopp/biopp.h"
#include "fideo/fideo.h"
#include "biopp-filer/bioppFiler.h"
#include "remo/MOP.h"
#include "remo/OutputsGenerator.h"
#include "remo/Exceptions.h"
#include "remo/Definitions.h"

using namespace RemoTools;
using namespace std;
using namespace mili;
using namespace biopp;
using namespace bioppFiler;
using namespace GetOpt;

/**
* Show available folding and hybridize backends
*/
void MOP::showBackends(const list<string> & sList)
{
	StringList::const_iterator pos;
	pos = sList.begin();
	while(pos != sList.end())
	{
		cout << "                        " << *pos << endl;
		pos++;
	}
}

/**
* Show options of usage
*/
void MOP::showOptions()
{
    cout << "\n RNAemo - RNA research project\n\n";
    cout << "  The aim of the study is to determine if this bias could be the result of evolutionary \n";
    cout << "  pressure exerted by the miRNA. To achieve this goal massive comparisons should be made \n";
    cout << "  (in the order of 10e7) between  the recognition of the virus natural genome and  the\n";
    cout << "  ''humanized'' genome. The latter may be obtained by replacing codons in the viral \n";
    cout << "  genome, achieving a codon usage ratio similar to the host. \n\n";
    cout << "Usage examples:\n";
    cout << "To folding: \n";
    cout << "            ./remo -s <rna_m.FASTA> -m <mi_rna.FASTA> -f <folder> -u <humanizer> -o <organism> -v <typeOutput>\n\n";
    cout << "To hybridize: \n";
    cout << "            ./remo -s <rna_m.FASTA> -m <mi_rna.FASTA> -y <hybridize> -u <humanizer> -o <organism> -v <typeOutput>\n\n";
    cout << "Required arguments:\n";
    cout << "   -s,   -rnam       : rnaM sequence in FASTA format. \n";
    cout << "   -m,   -mirna      : miRNA sequence in FASTA format. \n";
    cout << "   -f,   -folder     : folder backends: \n";

	StringList foldingList;
	IFold *fold;
	fold->getAvailableBackends(foldingList);
	showBackends(foldingList);

    cout << "   -y,   -hybridize  : hybridize backends:\n";

	StringList hybridizeList;
	IHybridize *hybridize;
	hybridize->getAvailableBackends(hybridizeList);
	showBackends(hybridizeList);

    cout << "   -u,   -humanizer  : humanizer software (geneDesign). \n";
    cout << "   -v,   --versionOutput : type of output.\n";
    cout << "                      OldTablesGenerator (folding),  NewTablesGenerator (hybridize) \n\n";
    cout << "   -o,   --organism : number of organism. \n";
    cout << "                      1 = S.cerevisiae,  2 = E.coli, 3 = H.sapiens, \n";
    cout << "                      4 = C.elegans, 5 = D.melanogaster, 6 = B.subtilis\n";
    cout << "Optional arguments\n";
    cout << "   -c,               : rnaM is circular. By default false. \n";
    cout << "   -h,   --help      : Display this message.\n";
}

void MOP::parseArguments(GetOpt_pp& args, RemoArguments& remoArgs)
{
    args >> OptionPresent('h', "help", remoArgs.help);
    args.exceptions_all();
    if (!remoArgs.help)
    {
        args
                >> Option('s', "rnam", remoArgs.fileNameRNAm)
                >> Option('m', "mirna", remoArgs.fileNameMicroRNA)
                >> OptionPresent('c', "circular", remoArgs.isCirc)
                >> Option('u', "humanizer", remoArgs.humanizer)
                >> Option('o', "organism", remoArgs.organism)
                >> Option('v', "versionOutput", remoArgs.typeOutput)
                ;
    }
    else
        showOptions();
}

void MOP::startSystem(GetOpt_pp& args)
{
    RemoArguments remoArgs;
    parseArguments(args, remoArgs);
    FastaParser<NucSequence> fileMsg(remoArgs.fileNameRNAm);
    FastaParser<NucSequence> fileMicro(remoArgs.fileNameMicroRNA);

    //humanizer
    auto_ptr<ICodonUsageModifier> humanizerImpl(FactoryRegistry<ICodonUsageModifier, string>::new_class(remoArgs.humanizer));
    if (humanizerImpl.get() == NULL)
        throw InvalidHumanizer();

    if (remoArgs.organism < ICodonUsageModifier::number_of_organisms and remoArgs.organism >= ICodonUsageModifier::_minimumValue)
        humanizerImpl->setOrganism(ICodonUsageModifier::Organism(remoArgs.organism));
    else
        throw InvalidOrganism();

    auto_ptr<TablesGenerator> tabGen(FactoryRegistry<TablesGenerator, string>::new_class(remoArgs.typeOutput));
    if (tabGen.get() == NULL)
        throw ErrorCreateFactory();

    tabGen->initialize(args); //create factory to 'folding' or 'hybridize'
    args.end_of_options();
    OutputsGenerator::generateOutput(fileMsg, fileMicro, humanizerImpl.get(), tabGen.get(), remoArgs.isCirc);
}
