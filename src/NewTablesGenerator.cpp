/**
 *  @file     NewTablesGenerator.cpp
 *  @brief    NewTablesGenerator is the implementation of TableGenerator interface
 *
 *
 *  @author   Franco Riberi
 *  @email    fgriberi AT gmail.com
 *
 * Contents:  Source file for remo providing NewTablesGenerator implementation.
 *
 * System:    remo: RNAemo - RNA research project
 * Language:  C++
 *
 * @date      October 2012
 *
 * This file is part of Remo.
 *
 * Copyright (C) 2012 - Franco Riberi, FuDePAN.
 *
 * Remo is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Remo is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Remo. If not, see <http:www.gnu.org/licenses/>.
 *
 */

#include <memory>
#include <fideo/fideo.h>
#include "remo/Exceptions.h"
#include "remo/TablesGenerator.h"

/** @brief Temporal methods to execute remo
 *
 */
fideo::IHybridize* getDerivedHybridize(const std::string& derivedKey);

namespace remo
{

/** @brief NewTablesGenerator is a implementation of TableGenerator interface
 *
 */
class NewTablesGenerator : public TablesGenerator
{
public:

    /** @brief Destructor of concrete class
     *
     */
    virtual ~NewTablesGenerator();

    /** @brief Create concrete instance
     *
     * @param args: to get specific instance
     * @return void
     */
    virtual void initialize(GetOpt::GetOpt_pp& args);

    /** @brief Method that prints the header files
     *
     * @return void
     */
    void generateHeader();

    /** @brief Method that populates a file by rows
     *
     * @param tableName: name of table
     * @param rnaMsg: rnam sequence
     * @param rnaMHumanized: rnam humanized sequence
     * @param circ: if rnam sequence is circ
     * @return void
     */
    virtual void generate(const std::string& tableName, const biopp::NucSequence& rnaMsg, const biopp::NucSequence& rnaMHumanized, const bool circ);

    /** @brief Method that append one miRNA in table.
     *
     * @param miRna: micro rna sequence
     * @param nameMicro: name of micro rna sequence
     * @return void
     */
    virtual void appendMicro(const biopp::NucSequence& miRna, const std::string& nameMicro);

    /**
     * File to generate
     */
    std::ofstream _oFile;

private:

    fideo::IHybridize* _hybridImpl;
    bool _isCirc;
    biopp::NucSequence _rnaM;
    biopp::NucSequence _rnaMHum;
};

REGISTER_FACTORIZABLE_CLASS(TablesGenerator, NewTablesGenerator, std::string, "NewTablesGenerator");

NewTablesGenerator::~NewTablesGenerator()
{
    delete _hybridImpl;
}

void NewTablesGenerator::initialize(GetOpt::GetOpt_pp& args)
{
    std::string hybrid;
    args >> GetOpt::Option('y', "hybridize", hybrid);
    _hybridImpl = getDerivedHybridize(hybrid);
}

void NewTablesGenerator::generateHeader()
{
    _oFile << "miRNA ," ;
    _oFile << "ScoreHybOrig ," ;
    _oFile << "ScoreHybHum"  << std::endl;
    //_oFile << "ScoreHybRaton" << std::endl;
}

void NewTablesGenerator::generate(const std::string& tableName, const biopp::NucSequence& rnaMsg,
                                  const biopp::NucSequence& rnaMHumanized, const bool circ)
{
    _rnaM = rnaMsg;
    _rnaMHum = rnaMHumanized;
    _isCirc = circ;
    if (_oFile)
    {
        _oFile.close();
    }
    _oFile.open(("/tmp/" + tableName).c_str());
    mili::assert_throw<FileNotCreated>(_oFile);
    generateHeader();
}

void NewTablesGenerator::appendMicro(const biopp::NucSequence& miRna, const std::string& nameMicro)
{
    assert(_rnaM.length() == _rnaMHum.length());

    //'hybridize' original sequence and humanized sequence
    _oFile << nameMicro;
    _oFile << ",";
    _oFile << _hybridImpl->hybridize(_rnaM, _isCirc, miRna);
    _oFile << ",";
    _oFile << _hybridImpl->hybridize(_rnaMHum, _isCirc, miRna);
    _oFile << std::endl;
}

} // namespace remo