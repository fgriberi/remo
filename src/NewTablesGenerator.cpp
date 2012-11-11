/**
 *  @file:      NewTablesGenerator.cpp
 *  @details    Generator tables.\n
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
 * along with R-emo. If not, see <http:www.gnu.org/licenses/>.
 *
 */

#include "remo/Definitions.h"
#include "remo/NewTablesGenerator.h"
#include "remo/Exceptions.h"

using namespace RemoTools;
using namespace biopp;
using namespace std;
using namespace biopp;

void NewTablesGenerator::generateHeader()
{
    oFile << "miRNA ," ;
    oFile << "ScoreHybOrig ," ;
    oFile << "ScoreHybHum ," ;
    oFile << "ScoreHybRaton" << endl;
}

void NewTablesGenerator::generate(const TableData& td)
{
    oFile.open(td.tableName.c_str());
    if (!oFile)
        throw FileNotCreate();
    generateHeader();
    oFile.close();

}

void NewTablesGenerator::appendMicro(const TableData& td)
{
    assert(td.rnaM.length() == td.rnaMHumanized.length());

    oFile.open(td.tableName.c_str(), ios::app);
    if (!oFile)
        throw FileNotCreate();
    oFile << td.nameMicro;
    oFile << ",";
    oFile << td.scoreHybOrig;
    oFile << ",";
    oFile << td.scoreHybHum;
    //oFile << ",";
    //oFile << td.scoreHybRaton;
    oFile << endl;
    oFile.close();
}
