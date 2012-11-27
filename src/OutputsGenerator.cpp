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
#include "biopp/biopp.h"
#include "fideo/fideo.h"
#include "mili/mili.h"
#include "remo/OutputsGenerator.h"
#include "remo/ICodonUsageModifier.h"
#include "remo/Exceptions.h"

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
        ret = result[3];
    else
        ret = fileName;
    return ret;
}

string OutputsGenerator::parseNameMicro(const string& microDescription)
{
    stringstream ss(microDescription);
    vector<string> result;
    ss >> result;
    if (result.size() != 2)
        throw InvalidDescriptionMiRNA();
    else
        return result[1];
}

void OutputsGenerator::getCodingSection(const NucSequence& src, AminoSequence& dest, size_t& i, size_t& j)
{
    AminoSequence ac;
    src.translate(ac);
    AminoSequence tempMaxSubSeq;
    AminoSequence currentSeq;
    size_t length = ac.size();
    size_t initCurrent = 0;
    size_t finalCurrent = 0;
    size_t tempMaxInit = 0;
    size_t tempMaxFinal = 0;

    bool hayAst = false;
    for (size_t index = 0; index < length; ++index)
    {
        if (ac[index] == Aminoacid::STOP_CODON)
            hayAst = true;
    }
    if (!hayAst)
        tempMaxFinal = length - 1;
    else
    {
        for (size_t index = 0; index < length; ++index)
        {
            if ((ac[index] == Aminoacid::STOP_CODON) || (index == ac.size() - 1))
            {
                if ((index == ac.size() - 1) && (ac[index] == Aminoacid::STOP_CODON))
                {
                    finalCurrent = index - 1;
                }
                else
                {
                    if (ac[index] == Aminoacid::STOP_CODON)
                        finalCurrent = index - 1;
                    else
                        finalCurrent = index;
                }
                if (currentSeq.size() > tempMaxSubSeq.size())
                {
                    tempMaxSubSeq = currentSeq;
                    tempMaxFinal = finalCurrent;
                    tempMaxInit = initCurrent;
                }
                currentSeq.clear();
                initCurrent = finalCurrent + 2;
            }
            else
            {
                currentSeq.push_back(ac[index]);
            }
        }
    }
    dest = tempMaxSubSeq;
    i = tempMaxInit;
    j = tempMaxFinal;
}

void OutputsGenerator::reemplazeSectionHumanized(const NucSequence& originalSeq, const NucSequence& humanizedSeq, NucSequence& toFoldSeq, size_t initIndex, size_t finalIndex)
{
    NucSequence tempSeq = originalSeq;
    AminoSequence temp;
    humanizedSeq.translate(temp);
    assert(temp.size() == (finalIndex - initIndex) + 1); //see

    size_t i = 0;
    for (size_t index = initIndex; index < finalIndex; ++index)
    {
        tempSeq[index] = humanizedSeq[i];
        ++i;
    }
    toFoldSeq = tempSeq;
}

void OutputsGenerator::generateOutput(FastaParser<NucSequence>& fileRNAm, FastaParser<NucSequence>& fileMiRNA, ICodonUsageModifier* humanizer, TablesGenerator* tGen, bool circ)
{ 
    NucSequence origRNAm;
    NucSequence humRnaM;
    string tableName;
    NucSequence microRNA;
    string nameMicro;
    string description;    
    size_t initIndex, finalIndex;
    while (fileRNAm.getNextSequence(description, origRNAm))
    {
        if ((origRNAm.length() % 3) != 0)
        {
            cout << "\n Invalid size in sequence: " << description << endl;
        }
        else
        {
            AminoSequence aminoSequeRNAm;
            getCodingSection(origRNAm, aminoSequeRNAm, initIndex, finalIndex);

            //humanized sequence 
            humanizer->changeCodonUsage(aminoSequeRNAm, humRnaM);
            reemplazeSectionHumanized(origRNAm, humRnaM, humRnaM, initIndex, finalIndex);

            string microDescription;            
            tableName = parseFileName(description) + "csv"; //.csv
            tGen->generate(tableName, origRNAm, humRnaM, circ);
            while (fileMiRNA.getNextSequence(microDescription, microRNA))
            {
                nameMicro = parseNameMicro(microDescription);
                tGen->appendMicro(microRNA, nameMicro);
            }            
            fileMiRNA.reset();
        }
    }
}
