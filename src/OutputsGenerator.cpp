/**
 *  @file:      OutputsGenerator.cpp
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
 * but WITHOUT ANY WARRANTY; w  ithout even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with R-emo. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <sstream>
#include <fideo/fideo.h>
#include "remo/OutputsGenerator.h"
#include "remo/ICodonUsageModifier.h"
#include "remo/Exceptions.h"
#include "remo/CodingSectionObtainer.h"

using namespace RemoTools;
using namespace biopp;
using namespace bioppFiler;
using namespace std;
using namespace mili;

string OutputsGenerator::parseFileName(const string& fileName)
{
    stringstream ss(fileName);
    vector<string> result;
    ss >> mili::Separator(result, '|');
    string ret;
    if (result.size() > 3)
    {
        ret = result[3];
    }
    else
    {
        ret = fileName;
    }
    return ret;
}

string OutputsGenerator::parseNameMicro(const string& microDescription)
{
    stringstream ss(microDescription);
    vector<string> result;
    ss >> result;
    if (result.size() != 2)
    {
        throw InvalidDescriptionMiRNA();
    }
    else
    {
        return result[1];
    }
}

void OutputsGenerator::replaceHumanizedSection(const NucSequence& originalSeq, const NucSequence& humanizedSeq, NucSequence& toFoldSeq, size_t initNucIndex)
{
    toFoldSeq = originalSeq;
    for (size_t i = 0; i < humanizedSeq.length(); i++)
    {
        toFoldSeq[i + initNucIndex] = humanizedSeq[i];
    }
}

void OutputsGenerator::generateOutput(FastaParser<NucSequence>& fileRNAm, FastaParser<NucSequence>& fileMiRNA, ICodonUsageModifier* humanizer, TablesGenerator* tGen, bool circ)
{
    NucSequence origRNAm;
    NucSequence humRnaM;
    NucSequence newHumanizedSeq;
    string tableName;
    NucSequence microRNA;
    string nameMicro;
    string description;
    size_t initIndex;
    CodingSectionObtainer helper;
    while (fileRNAm.getNextSequence(description, origRNAm))
    {
        if ((origRNAm.length() % 3) != 0)
        {
            cout << "\n Invalid size in sequence: " << description << endl;
        }
        else
        {
            AminoSequence aminoSequeRNAm;

            //Obtengo la mayor seccion codificante
            helper.getCodingSection(origRNAm, aminoSequeRNAm, initIndex);

            //humanized correct sequence sequence
            humanizer->changeCodonUsage(aminoSequeRNAm, humRnaM);

            //rearmo cadena
            replaceHumanizedSection(origRNAm, humRnaM, newHumanizedSeq, initIndex);

            string microDescription;
            tableName = parseFileName(description) + "csv"; //.csv
            tGen->generate(tableName, origRNAm, newHumanizedSeq, circ);
            while (fileMiRNA.getNextSequence(microDescription, microRNA))
            {
                nameMicro = parseNameMicro(microDescription);
                tGen->appendMicro(microRNA, nameMicro);
            }
            fileMiRNA.reset();
        }
    }
}