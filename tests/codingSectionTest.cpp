/*
    Copyright (C) 2012 Franco Riberi, FuDePAN

    This file is part of the remo.

    Remo is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Remo is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Remo. If not, see <http://www.gnu.org/licenses/>.

    This is a test file.
*/

#include <string>
#include <fstream>
#include <fideo/fideo.h>
#include <biopp/biopp.h>
#include <mili/mili.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "remo/remo.h"


TEST(CodingSectionTestSuite, ManyStopCodon)
{
    string p = "UUUAAAACAGCCUGUGGGUUGUUCCCACCCACAGGCGCCACCGGGCGUUAGCACACUGGU";    
    p += "AUCACGGUACCCUUGUGCGCCUGUUUUAUAACCCCACCCCGAGUAAACCUUAGAAGCAAU";
    p += "GCACCUCUGGUCAAUAGUAGGUGUGACACACCAGUCACAUCGUGACCAAGCACUUCUGUC";
    p += "UCCCCGGACUGAGUAUCAAUAGGCUGCUCGCGCGGCUGAAGGAGAAAGCGUUCGUUACCC";
    p += "GGCCAGCUACUUCGAGAAGCCUAGUAACACCAUGAAGGUUGCAGAGUGUUUCGCUCAGCA";
    p += "CUUCCCCUGUGUAGAUCAGGCCGAUGAGUCACCGCGUUCCUCACGGGCGACCGUGGCGGU";
    p += "CGCUGCGCUGGUGGCCUGCCUAUGGGGCAACCCAUAGGACGCUCUAAUGCUGACAUGGUG";
    p += "CGAAGAGUCUAUUGAGCUAGCUGGUAGUCCUCCGGCCCCUGAAUGCGGCUAAUCCCAACU";
    p += "GCGGAGCACGCACCCUCAAACCAGGGGGCAGCGUGUCGUAACGGGCAACUCUGCAGCGGA";
    p += "ACCGACUACUUUGGGUGUCCGUGUUUCUUUUUAUUCCUAUAUUGGCUGCUUAUGGUGACA";
    p += "AUUGAGAGAUUGUUACCAUAUAGCUAUUGGAUUGGCCAUCCGGUGAGCAACAGAGCUAUU";
    p += "GUGUAUCUGUUUACUGGUUUCAUACCCCUUAAUUACAAAGAAGUCAAAACCCUUCACUUG";
    p += "AUCUUGUUAUUCAAUACAACAAAAUGGGAGCUCAAGUGUCAACACAGAAAACUGGAGCUC";
  
    const biopp::NucSequence seq(p);
    biopp::AminoSequence dest;
    size_t init;
    CodingSectionObtainer::getCodingSection(seq, dest, init);

    std::string res =
 "MRLIPTAEHAPSNQGAACRNGQLCSGTDYFGCPCFFLFLYWLLMVTIERLLPYSYWIGHPVSNRAIVYLFTGFIPLNYKEVKTLHLILLFNTTKWELKCQHRKLE";

    ASSERT_EQ(init, 154);
    ASSERT_EQ(dest.getString(), res);
}

//TEST(CodingSectionTestSuite, HeadStopCodon)
//{
//    /* *AAAAAAAAGGGGGGGGCCCCCCCCTTTTTTTT*/
//} 

//TEST(CodingSectionTestSuite, EndStopCodon)
//{
//    /* AAAAAAAAGGGGGGGGCCCCCCCCTTTTTTTT* */
//}

//TEST(CodingSectionTestSuite, OneStopCodonRigth)
//{
//    /* AAAAAAAAGGGGGGGGCCCCC*CCCTTTTTTTT* */
//}

//TEST(CodingSectionTestSuite, OneStopCodonLeft)
//{
//    /* AAAAAAAAGG*sGGGGGGCCCCCCCCTTTTTTTT* */
//}
