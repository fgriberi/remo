/**
 *  @file:      GeneDesign.h
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with R-emo .  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <sstream>
#include "mili/mili.h"
#include "fideo/fideo.h"
#include "biopp-filer/bioppFiler.h"
#include "remo/IHumanizer.h"
#include "remo/Exceptions.h"


using namespace biopp;
using namespace bioppFiler;

//GeneDesign software
class GeneDesign : public IHumanizer
{
    std::string argPath;
    virtual void humanize(const biopp::NucSequence& sequence, biopp::NucSequence& sequenceHumanized) const;
    virtual void setArgument(const std::string& arg);        
};

static const std::string FILE_NAME_INPUT = "sequence.FASTA";
static const std::string DIRECTORY_PATH = "sequence_gdRT";
static const std::string FILE_NAME_OUTPUT = "sequence_gdRT_3.FASTA";

REGISTER_FACTORIZABLE_CLASS(IHumanizer, GeneDesign, std::string, "GeneDesign");

void GeneDesign::setArgument(const std::string& arg) 
{
    argPath = arg;
}

void GeneDesign::humanize(const biopp::NucSequence& sequence, biopp::NucSequence& sequenceHumanized) const
{
    sequenceHumanized.clear();
    std::string sseq = sequence.getString();
    write(FILE_NAME_INPUT, sseq);  //crearlo desde aca
    std::stringstream ss;
    ss << "perl Reverse_Translate.pl -i ";
    ss << FILE_NAME_INPUT;
    ss << " -o 3";
    std::cout << ss;
    const Command CMD = ss.str();
    const Command PATH_EXECUTABLE = argPath; //cd home/gringusi/Escritorio/geneDesign/GeneDesign/bin/
    runCommand(PATH_EXECUTABLE);
    runCommand(CMD);   // perl Reverse_Translate.pl -i FILE_NAME -o 3
    
    const Command PATH_SEQUENCE_HUMANIZED = argPath + DIRECTORY_PATH;
    runCommand(PATH_SEQUENCE_HUMANIZED);
 
    FastaParser<NucSequence> fp(FILE_NAME_OUTPUT);
    std::string name;  
    biopp::NucSequence seqHumanized;  
    if (fp.getNextSequence(name, seqHumanized))
        sequenceHumanized = seqHumanized;     
    
    remove_file(FILE_NAME_OUTPUT);
}
