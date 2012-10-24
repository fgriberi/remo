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
#include "remo/TablesGenerator.h"
#include "remo/IHumanizer.h"

using namespace biopp;
using namespace bioppFiler;
using namespace std;
using namespace mili;

string OutputsGenerator::generateTableName(const string& RNAmName, size_t n)
{
    stringstream out;
    out << RNAmName << "_" << n << ".csv";
    return out.str();
}

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

void OutputsGenerator::generateOutput(FastaParser<NucSequence>& fileRNAm, FastaParser<NucSequence>& fileMiRNA, bool circ,
                                      IHumanizer* humanizer, IFold* folder)
{
    size_t miRnacount;
    string description;
    TablesGenerator tGenerator;
    TablesGenerator::TableData td;
    td.circ = circ;
    int numSeq = 0;
    while (fileRNAm.getNextSequence(description, td.rnaM))
    {                
        if ((td.rnaM.length() % 3) != 0){
            cout << "\n Invalid size in sequence: " << description << endl;
        }
        else{
            ++numSeq;
            //humanized sequence
            humanizer->humanize(td.rnaM, td.rnaMHumanized, numSeq);        

            //'foldear' original sequence and humanized sequence       
            folder->fold(td.rnaM, td.structRNAm, circ);
            folder->fold(td.rnaMHumanized, td.structHumanized, circ);

            miRnacount = 1;
            string microDescription;
            NucSequence microSequence;            
            while (fileMiRNA.getNextSequence(microDescription, microSequence))
            {
                td.tableName = generateTableName(parseFileName(description), miRnacount);
                td.miRna = microSequence;
                tGenerator.generate(td);
                ++miRnacount;
            }
            fileMiRNA.reset();       
        }
    }
}
