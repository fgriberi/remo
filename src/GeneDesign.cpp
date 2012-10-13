/**
 *  @file:      GeneDesign.h
 *  @details    External software \n
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

#include <sstream>
#include <fstream>
#include <unistd.h>
#include "mili/mili.h"
#include "fideo/fideo.h"
#include "biopp-filer/bioppFiler.h"
#include "remo/IHumanizer.h"
#include "remo/Exceptions.h"

using namespace RemoTools;
using namespace std;
using namespace biopp;
using namespace bioppFiler;

class GeneDesign : public IHumanizer
{
    string argPath;
    virtual void humanize(const NucSequence& sequence, NucSequence& sequenceHumanized) const;
    virtual void setArgument(const string& arg);
    virtual ~GeneDesign() {}
};

static const string FILE_NAME_INPUT = "sequence.FASTA";
static const string DIRECTORY_PATH = "sequence_gdRT";
static const string FILE_NAME_OUTPUT = "sequence_gdRT_3.FASTA";
static const string FILE_ERROR = "error.txt";

REGISTER_FACTORIZABLE_CLASS(IHumanizer, GeneDesign, string, "GeneDesign");

void GeneDesign::setArgument(const string& arg)
{
    argPath = arg;
}

void GeneDesign::humanize(const NucSequence& sequence, NucSequence& sequenceHumanized) const
{
    if ((sequence.length() % 3) != 0)
        throw InvalidLengthSequence();
    sequenceHumanized.clear();

    //move to the directory where is the humanizer
    if (chdir(argPath.c_str()) != 0)
        throw InvalidPathChdir(argPath);

    //Translate to amino acid sequences, and keep on file in FASTA
    AminoSequence ac;
    sequence.translate(ac);
    {
        FastaSaver<AminoSequence> fs(FILE_NAME_INPUT);
        fs.saveNextSequence("temp", ac);
    }
    stringstream ss;
    ss << "perl Reverse_Translate.pl -i ";
    ss << FILE_NAME_INPUT;
    ss << " -o 3";
    const Command CMD = ss.str(); //Command is: perl Reverse_Translate.pl -i FILE_NAME -o 3
    runCommand(CMD);

    string cmd = argPath + "/" + DIRECTORY_PATH;

    if (chdir(cmd.c_str()) != 0)
        throw InvalidPathChdir(argPath);

    ifstream fileError;
    fileError.open(FILE_ERROR.c_str());
    if (fileError)
        throw ErrorHumanizer();
    fileError.close();

    FastaParser<NucSequence> fp(FILE_NAME_OUTPUT);
    string name;
    if (!fp.getNextSequence(name, sequenceHumanized))
        throw EmptySequence();
    remove_file(FILE_NAME_OUTPUT);
}
