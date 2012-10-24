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
    virtual void humanize(const NucSequence& sequence, NucSequence& sequenceHumanized, int numSeq) const;
    virtual void setArgument(const string& arg);
    virtual ~GeneDesign() {}
};

static const string FILE_ERROR = "error.txt";
static const string SEQUENCE = "sequence";
static const string FILE_NAME_INPUT = ".FASTA";
static const string DIRECTORY_PATH = "_gdRT";
static const string FILE_NAME_OUTPUT = "_gdRT_";

REGISTER_FACTORIZABLE_CLASS(IHumanizer, GeneDesign, string, "GeneDesign");

void GeneDesign::setArgument(const string& arg)
{
    argPath = arg;
}

void GeneDesign::humanize(const NucSequence& sequence, NucSequence& sequenceHumanized, int numSeq) const
{   
    sequenceHumanized.clear();

    //move to the directory where is the humanizer
    if (chdir(argPath.c_str()) != 0)
        throw InvalidPathChdir(argPath);

    stringstream file_name;
    file_name << SEQUENCE << numSeq << FILE_NAME_INPUT;

    //Translate to amino acid sequences, and keep on file in FASTA
    AminoSequence ac;
    sequence.translate(ac);
    {        
        FastaSaver<AminoSequence> fs(file_name.str());
        fs.saveNextSequence("temp", ac);
    }    
    stringstream ss;
    ss << "perl Reverse_Translate.pl -i ";
    ss << file_name.str();
    ss << " -o 3";
    const Command CMD = ss.str(); //Command is: perl Reverse_Translate.pl -i FILE_NAME -o 3
    runCommand(CMD);

    stringstream directory;
    directory << SEQUENCE << numSeq << DIRECTORY_PATH;
    string cmd = argPath + "/" + directory.str();

    if (chdir(cmd.c_str()) != 0)
        throw InvalidPathChdir(argPath);

    ifstream fileError;
    fileError.open(FILE_ERROR.c_str());
    if (fileError)
        throw ErrorHumanizer();
    fileError.close();

    stringstream file_output;
    file_output << SEQUENCE << numSeq << FILE_NAME_OUTPUT << 3 << FILE_NAME_INPUT;   

    FastaParser<NucSequence> fp(file_output.str());
    string name;
    if (!fp.getNextSequence(name, sequenceHumanized))
        throw EmptySequence();
    AminoSequence acTemp;
    sequenceHumanized.translate(acTemp);
    assert(ac == acTemp);
    remove_file(file_output.str());
}
