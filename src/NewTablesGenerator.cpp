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

#include <memory>
#include <mili/mili.h>
#include "fideo/fideo.h"
#include "remo/Definitions.h"
#include "remo/Exceptions.h"
#include "remo/TablesGenerator.h"

using namespace RemoTools;
using namespace std;
using namespace mili;
using namespace biopp;

class NewTablesGenerator : public TablesGenerator
{

    IHybridize* hybridImpl;      
    bool isCirc;
    biopp::NucSequence originalRNAm;
    biopp::NucSequence humanizedRNAm;
public:

    std::ofstream oFile;

    ~NewTablesGenerator();

    virtual void initialize(GetOpt_pp& args);

    /*
     * 'foldear' or 'hybridize' whichever is applicable
     */
    virtual void setRnaM(const biopp::NucSequence& rnaM, const biopp::NucSequence& humRnaM, bool circ);

    /**
     * Method that prints the header files
     */
    virtual void generateHeader();

    /**
     * Method that populates a file by rows
     */
    virtual void generate(const string& tableName);

    /**
      * Method that append one miRNA in table.
      */
   virtual void appendMicro(const biopp::NucSequence& miRna, const std::string& nameMicro, const biopp::NucSequence& rnaM, const biopp::NucSequence& rnaMHum, const std::string& tableName);  
};

REGISTER_FACTORIZABLE_CLASS(TablesGenerator, NewTablesGenerator, std::string, "NewTablesGenerator");

NewTablesGenerator::~NewTablesGenerator()
{
    delete hybridImpl;
}

void NewTablesGenerator::initialize(GetOpt_pp& args){
    string hybrid;
    args >> Option('y', "hybridize", hybrid);
    hybridImpl = (FactoryRegistry<IHybridize, string>::new_class(hybrid));
    if (hybridImpl == NULL)
        throw InvalidHybridize();
}
       
void NewTablesGenerator::setRnaM(const NucSequence& rnaM, const NucSequence& humRnaM, bool circ){   
    isCirc = circ;
    originalRNAm = rnaM;
    humanizedRNAm = humRnaM;
}

void NewTablesGenerator::generateHeader()
{
    oFile << "miRNA ," ;
    oFile << "ScoreHybOrig ," ;
    oFile << "ScoreHybHum ," ;
    oFile << "ScoreHybRaton" << endl;
}

void NewTablesGenerator::generate(const string& tableName)
{
    oFile.open(tableName.c_str());
    if (!oFile)
        throw FileNotCreate();
    generateHeader();
    oFile.close();
}

void NewTablesGenerator::appendMicro(const NucSequence& miRna, const string& nameMicro, const NucSequence& rnaM, const NucSequence& rnaMHum, const string& tableName)
{
    assert(rnaM.length() == rnaMHum.length());

    //'hybridize' original sequence and humanized sequence
    oFile.open(tableName.c_str(), ios::app);
    if (!oFile)
        throw FileNotCreate();
    oFile << nameMicro;
    oFile << ",";
    oFile << hybridImpl->hybridize(rnaM, miRna, isCirc);
    oFile << ",";
    oFile << hybridImpl->hybridize(rnaMHum, miRna, isCirc);
//    oFile << ",";
//    oFile << td.scoreHybRaton;
    oFile << endl;
    oFile.close();
}
