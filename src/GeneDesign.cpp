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
#include <mili/mili.h>
//#include <biopp-filer/bioppFiler.h>
#include <fideo/fideo.h>
#include "remo/IHumanize.h"

//GeneDesign software
class GeneDesign : public IHumanize
{
    virtual void humanize(const biopp::NucSequence& rnam_sequence, biopp::NucSequence& rnam_sequence_humanized) const;
};

static const std::string FILE_NAME_INPUT = "sequence.FASTA";
static const std::string FILE_NAME_OUTPUT = "sequence_gdRT_3.FASTA";

REGISTER_FACTORIZABLE_CLASS(IHumanize, GeneDesign, std::string, "GeneDesign");

void GeneDesign::humanize(const biopp::NucSequence& rnam_sequence, biopp::NucSequence& rnam_sequence_humanized) const
{
    //biopp::translate(rnam_sequence)
    FileLine sseq;
    for (int i = 0; i < rnam_sequence.length(); ++i)
        sseq += rnam_sequence[i].as_char();
    write(FILE_NAME_INPUT, sseq);  //crearlo desde aca
    std::stringstream ss;
    ss << "perl Reverse_Translate.pl -i ";
    ss << FILE_NAME_INPUT;
    ss << " -o 3";
    std::cout << ss;
    const Command CMD = ss.str();
    const Command CD = "cd home/gringusi/Escritorio/geneDesign/GeneDesign/bin/";
    runCommand(CD);
    runCommand(CMD);   // perl Reverse_Translate.pl -i FILE_NAME -o 3

    //cd home/gringusi/Escritorio/geneDesign/GeneDesign/bin/sequence_gdRT
    //bioppFiler::FastaParser<biopp::NucSequence> fp(FILE_NAME_OUTPUT);
    //leer la sequencia y la deja en rnam_sequence_humanized
    //borrar el archivo de salida
    //borrar el dir sequence_gdRT
    //remove_file(FILE_NAME_OUTPUT);
}
