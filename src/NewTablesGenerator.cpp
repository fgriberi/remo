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
#include <fideo/fideo.h>
#include "remo/Definitions.h"
#include "remo/Exceptions.h"
#include "remo/TablesGenerator.h"

class NewTablesGenerator : public TablesGenerator
{   
public:   

    ~NewTablesGenerator();

    virtual void initialize(GetOpt::GetOpt_pp& args);

    /**
     * Method that prints the header files
     */
    void generateHeader();

    /**
     * Method that populates a file by rows
     */
    virtual void generate(const std::string& tableName, const biopp::NucSequence& rnaMsg, const biopp::NucSequence& rnaMHumanized, bool circ);

    /**
      * Method that append one miRNA in table.
      */
    virtual void appendMicro(const biopp::NucSequence& miRna, const std::string& nameMicro);

    std::ofstream oFile;
    
private:

    fideo::IHybridize* hybridImpl;
    bool isCirc;
    biopp::NucSequence rnaM;
    biopp::NucSequence rnaMHum;
};

REGISTER_FACTORIZABLE_CLASS(TablesGenerator, NewTablesGenerator, std::string, "NewTablesGenerator");

NewTablesGenerator::~NewTablesGenerator()
{
    delete hybridImpl;
}

void NewTablesGenerator::initialize(GetOpt::GetOpt_pp& args)
{
    std::string hybrid;
    args >> GetOpt::Option('y', "hybridize", hybrid);
    hybridImpl = (mili::FactoryRegistry<fideo::IHybridize, std::string>::new_class(hybrid));
    if (hybridImpl == NULL)
    {
        throw RemoTools::InvalidHybridize();
    }
}

void NewTablesGenerator::generateHeader()
{
    oFile << "miRNA ," ;
    oFile << "ScoreHybOrig ," ;
    oFile << "ScoreHybHum ," ;
    oFile << "ScoreHybRaton" << std::endl;
}

void NewTablesGenerator::generate(const std::string& tableName, const biopp::NucSequence& rnaMsg, const biopp::NucSequence& rnaMHumanized, bool circ)
{
    rnaM = rnaMsg;
    rnaMHum = rnaMHumanized;
    isCirc = circ;
    if (oFile.is_open())
    {
        oFile.close();
    }
    oFile.open(tableName.c_str());
    if (!oFile)
    {
        throw RemoTools::FileNotCreate();
    }
    generateHeader();
}

void NewTablesGenerator::appendMicro(const biopp::NucSequence& miRna, const std::string& nameMicro)
{
    assert(rnaM.length() == rnaMHum.length());

    //'hybridize' original sequence and humanized sequence
    oFile << nameMicro;
    oFile << ",";
    oFile << hybridImpl->hybridize(rnaM, isCirc, miRna);
    oFile << ",";
    oFile << hybridImpl->hybridize(rnaMHum, isCirc, miRna);
//    oFile << ",";
//    oFile << td.scoreHybRaton;
    oFile << std::endl;
}
