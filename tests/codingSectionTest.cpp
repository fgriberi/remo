/**
 * @file     codingSectionTest.cpp
 * @brief    Defines the test for condingSectionObtainer class.
 *
 * @author   Franco Riberi
 * @email    fgriberi AT gmail.com
 *
 * Contents: test case
 *
 * System:   remo: RNAemo - RNA research project
 * Language: C++
 *
 * @date 2012
 *
 * Copyright (C) 2012 Franco Riberi, FuDePAN
 *
 * This file is part of the remo.
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
 * along with Remo. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#define private public

#include <string>
#include <fstream>
#include <biopp/biopp.h>
#include <acuoso/acuoso.h>
#include <mili/mili.h>
#include <gtest/gtest.h>
#include "remo/CodingSectionObtainer.h"
#include "remo/Exceptions.h"

using namespace remo;
using namespace acuoso;

/// Temporal functions
int linkFictitious();

void myTest(const std::string& originalSeq, const std::string& result)
{
    const biopp::NucSequence seq(originalSeq);
    biopp::AminoSequence dest;
    size_t init = 0;
    CodingSectionObtainer cso;
    cso.getCodingSection(seq, dest, init);

    ICodonUsageModifier* humanizer = mili::FactoryRegistry<ICodonUsageModifier, std::string>::new_class("GeneDesign");
    ASSERT_TRUE(humanizer != NULL);

    ASSERT_EQ(dest.getString(), result);
}

TEST(CodingSectionTestSuite, withoutStopCodon)
{
    linkFictitious();
    const std::string nucSeq = "GCUGUGUGUUGUGUGUGCCAUGGAUCAGUCAAACACAUUAUAGGCUUGUACAGCAGGAUG"
                               "AGUACACCAGCGCUGGUUACGUGACGUGUUGGUAUCAGACUGGUAUGAUUGUCCCACCAG"
                               "GAACCCCAAAUUC";
    // nucSeq in Aminoacid
    // AVCCVCHGSVKHIIGLYSRMSTPALVT

    const std::string res = "AVCCVCHGSVKHIIGLYSRMSTPALVT";
    myTest(nucSeq, res);
}

TEST(CodingSectionTestSuite, greaterRightCodingSection)
{
    const std::string nucSeq = "UUUAAAACAGCCUGUGGGUUGUUCCCACCCACAGGCGCCACCGGGCGUUAGCACACUGGU"
                               "AUCACGGUACCCUUGUGCGCCUGUUUUAUAACCCCACCCCGAGUAAACCUUAGAAGCAAU"
                               "GCACCUCUGGUCAAUAGUAGGUGUGACACACCAGUCACAUCGUGACCAAGCACUUCUGUC"
                               "UCCCCGGACUGAGUAUCAAUAGGCUGCUCGCGCGGCUGAAGGAGAAAGCGUUCGUUACCC"
                               "GGCCAGCUACUUCGAGAAGCCUAGUAACACCAUGAAGGUUGCAGAGUGUUUCGCUCAGCA"
                               "CUUCCCCUGUGUAGAUCAGGCCGAUGAGUCACCGCGUUCCUCACGGGCGACCGUGGCGGU"
                               "CGCUGCGCUGGUGGCCUGCCUAUGGGGCAACCCAUAGGACGCUCUAAUGCUGACAUGGUG"
                               "CGAAGAGUCUAUUGAGCUAGCUGGUAGUCCUCCGGCCCCUGAAUGCGGCUAAUCCCAACU"
                               "GCGGAGCACGCACCCUCAAACCAGGGGGCAGCGUGUCGUAACGGGCAACUCUGCAGCGGA"
                               "ACCGACUACUUUGGGUGUCCGUGUUUCUUUUUAUUCCUAUAUUGGCUGCUUAUGGUGACA"
                               "AUUGAGAGAUUGUUACCAUAUAGCUAUUGGAUUGGCCAUCCGGUGAGCAACAGAGCUAUU"
                               "GUGUAUCUGUUUACUGGUUUCAUACCCCUUAAUUACAAAGAAGUCAAAACCCUUCACUUG"
                               "AUCUUGUUAUUCAAUACAACAAAAUGGGAGCUCAAGUGUCAACACAGAAAACUGGAGCUC";
    // nucSeq in Aminoacid
    //FKTACGLFPPTGATGR*HTGITVPLCACFITPPRVNLRSNAPLVNSRCDTPVTS*PSTSVSPD*VSIGCSRG*RRKRSLPGQLLREA*
    //*HHEGCRVFRSALPLCRSGR*VTAFLTGDRGGRCAGGLPMGQPIGRSNADMVRRVY*ASW*SSGP*MRLIPTAEHAPSNQGAACRNGQ
    //LCSGTDYFGCPCFFLFLYWLLMVTIERLLPYSYWIGHPVSNRAIVYLFTGFIPLNYKEVKTLHLILLFNTTKWELKCQHRKLEL

    const std::string res = "MRLIPTAEHAPSNQGAACRNGQLCSGTDYFGCPCFFLFLYWLLMVTIERLLPYSYWIG"
                            "HPVSNRAIVYLFTGFIPLNYKEVKTLHLILLFNTTKWELKCQHRKLEL";

    myTest(nucSeq, res);
}

TEST(CodingSectionTestSuite, greaterLeftCodingSection)
{
    const std::string nucSeq = "UGUGUGUGCCCGAGGCUGAGAUGGGAGGAGCUGUGGUUGGACAAGCAUUUUCCGCCA"
                               "CCGCGAUGGCAAAUGGUGAUAAAGCAUAUGAGUUCACUAGCGCAACCCAAAGUGAUCAGA"
                               "CAAAAGUUCAAACUGCUAUACACAAUGCAGGGAUGGGCGUAGGUGUAGGGAACCUCACUA";
    // nucSeq in Aminoacid
    // CVCPRLRWEELWLDKHFPPPRWQMVIKHMSSLAQPKVIRQKFKLLYTMQGWA*V*GTSL

    const std::string res = "CVCPRLRWEELWLDKHFPPPRWQMVIKHMSSLAQPKVIRQKFKLLYTMQGWA";

    myTest(nucSeq, res);
}

TEST(CodingSectionTestSuite, greaterCodingSectionInTheMiddle)
{
    const std::string nucSeq = "UUUUAGCCGCCCGAGCAAAACAGCCUGUGGGUUGUUCCCACCCACAGGCGCCACCGGGCGUUAGCACACUGGU"
                               "AUCACGGUACCCUUGUGCGCCUGUUUUAUAACCCCACCCCGAGUAAACCUUAGAAGCAAUAG";
    // nucSeq in Aminoacid
    // F*PPEQNSLWVVPTHRRHRALAHWYHGTLVRLFYNPTPSKP*KQ*

    const std::string res = "PPEQNSLWVVPTHRRHRALAHWYHGTLVRLFYNPTPSKP";
    myTest(nucSeq, res);
}

TEST(CodingSectionTestSuite, repeatedSubsequenceLarger)
{
    const std::string nucSeq = "UAAUGGAAAUAGCAGAAGUGGACUCGGUCGUGCCCGUGAACAAUGUCCAAGACACCACUG"
                               "ACCAAAUGGAGAUGUUCAGGAUACCAGUGACCAUAAAUGCCCCUCUACAACAACAGGUUU"
                               "UUGGCCUCAGAUUGCAACCAGGCUUAGAUAGUGUGUUUAAGCACACUCUGUUGGGAGAAA"
                               "UUCUAAACUACUAUGCGCACUGGUCAGGCAGCAUGAAGCUGACAUUUGUGUUUUGCGGGU";
    // nucSeq in Aminoacid
    // *WK*QKWTRSCP*TMSKTPLTKWRCSGYQ*P*MPLYNNRFLASDCNQA*IVCLSTLCWEKF*TTMRTGQAA*S*HLCFAG

    const biopp::NucSequence seq(nucSeq);
    biopp::AminoSequence dest;
    size_t init = 0;
    CodingSectionObtainer cso;

    EXPECT_THROW(cso.getCodingSection(seq, dest, init), RemoException);
    //Two largar subsequences with equals size
}

TEST(CodingSectionTestSuite, manyStopInHead)
{
    std::string nucSeq = "UAAUAAUAGUCUUUUCGUCGAGGUGGGGCUUAAAUGUGUUUUCGUCGA";
    
    // nucSeq in Aminoacid
    // ***SFRRGGA*MCFRR

    const std::string res = "SFRRGGA";
    myTest(nucSeq, res);
}

TEST(CodingSectionTestSuite, manyStopInTheMiddle1)
{
    std::string nucSeq = "UGUGGGUGUUUUCGUCGAUGUGGGGCUUAACGAUGUUUUUAAUGAUAAUGAAUGUGUUUU";
    
    // nucSeq in Aminoacid
    // CGCFRRCGA*RCF****MCF

    const std::string res = "CGCFRRCGA";
    myTest(nucSeq, res);
}

TEST(CodingSectionTestSuite, manyStopInTheMiddle2)
{
    std::string nucSeq = "CAUAUGAAAUAAUAGCCUCCCUCCACCGUUUAGUAAUAAUAGGACGAUUGUUGAUAAUGAUGAUAAUAGUGAUAAGCUCGUAACCUUGACUUUAUGUAA";
    
    // nucSeq in Aminoacid
    // HMK**PPSTV****DDC********ARNLDFM*

    const std::string res = "ARNLDFM";
    myTest(nucSeq, res);
}

TEST(CodingSectionTestSuite, manyStopInEnd)
{
    std::string nucSeq = "AAUAAGCCCUUGAUGUGUUUUUAGCGUAUGUGUCGAAAGCCCUCUUUUCGUUAGUAGUGA";
    
    // nucSeq in Aminoacid
    // NKPLMCF*RMCRKPSFR***

    const std::string res = "RMCRKPSFR";
    myTest(nucSeq, res);
}

TEST(CodingSectionTestSuite, nextStopTest)
{
    biopp::NucSequence nucSeq("UAAUGGAAAUAGCAGAAGUGGACUCGGUCGUGCCCGUGAACAAUGUCCAAGACACCACUG"
                              "ACCAAAUGGAGAUGUUCAGGAUACCAGUGACCAUAAAUGCCCCUCUACAACAACAGGUUU"
                              "UUGGCCUCAGAUUGCAACCAGGCUUAGAUAGUGUGUUUAAGCACACUCUGUUGGGAGAAA"
                              "UUCUAAACUACUAUGCGCACUGGUCAGGCAGCAUGAAGCUGACAUUUGUGUUUUGCGGGU");
    biopp::AminoSequence seq;
    nucSeq.translate(seq);

    CodingSectionObtainer cso;
    cso.aminoSeq = &seq;

    const std::string expectedResult = "*WK*QKWTRSCP*TMSKTPLTKWRCSGYQ*P*MPLYNNRFLASDCNQA*IVCLSTLCWEKF*TTMRTGQAA*S*HLCFAG";
    ASSERT_EQ((*(cso.aminoSeq)).getString(), expectedResult);

    size_t result;

    size_t firstStop = 0;
    result = cso.nextStop(firstStop);
    EXPECT_EQ(result, 0);

    size_t secondStop = 1;
    result = cso.nextStop(secondStop);
    EXPECT_EQ(result, 3);

    size_t thirdStop = 4;
    result = cso.nextStop(thirdStop);
    EXPECT_EQ(result, 12);

    size_t fourthStop = 13;
    result = cso.nextStop(fourthStop);
    EXPECT_EQ(result, 29);

    size_t fifthStop = 30;
    result = cso.nextStop(fifthStop);
    EXPECT_EQ(result, 31);

    size_t noStop = expectedResult.size();
    result = cso.nextStop(noStop);
    EXPECT_EQ(result, noStop);
}

TEST(CodingSectionTestSuite, maxSubSeq)
{
    biopp::NucSequence nucSeq("UGUGUGUGCCCGAGGCUGAGAUGGGAGGAGCUGUGGUUGGACAAGCAUUUUCCGCCA"
                              "CCGCGAUGGCAAAUGGUGAUAAAGCAUAUGAGUUCACUAGCGCAACCCAAAGUGAUCAGA"
                              "CAAAAGUUCAAACUGCUAUACACAAUGCAGGGAUGGGCGUAGGUGUAGGGAACCUCACUA");
    biopp::AminoSequence seq;
    biopp::AminoSequence dest;
    nucSeq.translate(seq);

    CodingSectionObtainer cso;
    cso.aminoSeq = &seq;  //aminoSeq = CVCPRLRWEELWLDKHFPPPRWQMVIKHMSSLAQPKVIRQKFKLLYTMQGWA*V*GTSL

    const std::string result = "CVCPRLRWEELWLDKHFPPPRWQMVIKHMSSLAQPKVIRQKFKLLYTMQGWA";

    cso.maxSubSeq(0, 52, dest);
    EXPECT_EQ(dest.getString(), result);
}