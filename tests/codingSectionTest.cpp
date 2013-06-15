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

    ASSERT_EQ(dest.getString(), result);
}

TEST(CodingSectionTestSuite, withoutStopCodon)
{
    linkFictitious();
    const std::string nucSeq = "UCUUUUCGUCGAGGUGGGGCU";
    // nucSeq in Aminoacid
    // SFRRGGA

    const std::string res = "SFRRGGA";
    myTest(nucSeq, res);
}

TEST(CodingSectionTestSuite, oneStopInHead)
{
    const std::string nucSeq = "UAGUCUUUUCGUCGAGGUGGGGCU";

    // nucSeq in Aminoacid
    // *SFRRGGA

    const std::string res = "SFRRGGA";
    myTest(nucSeq, res);
}

TEST(CodingSectionTestSuite, manyStopInHead)
{
    const std::string nucSeq = "UAAUAAUAGUCUUUUCGUCGAGGUGGGGCU";

    // nucSeq in Aminoacid
    // ***SFRRGGA

    const std::string res = "SFRRGGA";
    myTest(nucSeq, res);
}

TEST(CodingSectionTestSuite, manyStopInTheMiddle1)
{
    const std::string nucSeq = "GCUGUGUGUUGUGUGUGCCAUGGAUCAGUCAAACACAUUAUAGGCUUGUACAGCAGGAUG"
                               "AGUACACCAGCGCUGGUUACGUGACGUGUUGGUAUCAGACUGGUAUGAUUGUCCCACCAG"
                               "GAACCCCAAAUUC";
    // nucSeq in Aminoacid
    // AVCCVCHGSVKHIIGLYSRMSTPALVT*RVGIRLV*LSHQEPQI

    const std::string res = "AVCCVCHGSVKHIIGLYSRMSTPALVT";
    myTest(nucSeq, res);
}

TEST(CodingSectionTestSuite, manyStopInTheMiddle2)
{
    const std::string nucSeq = "UGUGGGUGUUUUCGUCGAUGUGGGGCUUAACGAUGUUUUUAAUGAUAAUGAAUGUGUUUU";

    // nucSeq in Aminoacid
    // CGCFRRCGA*RCF****MCF

    const std::string res = "CGCFRRCGA";
    myTest(nucSeq, res);
}

TEST(CodingSectionTestSuite, manyStopInTheMiddle3)
{
    const std::string nucSeq = "CAUAUGAAAUAAUAGCCUCCCUCCACCGUUUAGUAAUAAUAGGACGAUUGUUGAUAAUGAUGAUAAUAGUGAUAAGCUCGUAACCUUGACUUUAUGUAA";

    // nucSeq in Aminoacid
    // HMK**PPSTV****DDC********ARNLDFM*

    const std::string res = "ARNLDFM";
    myTest(nucSeq, res);
}

TEST(CodingSectionTestSuite, manyStopInTheMiddle4)
{
    std::string nucSeq = "AAUAAGCCCUUGAUGUGUUUUUAGCGUAUGUGUCGAAAGCCCUCUUUUCGUUAGUAGUGA"
                         "AAUAAGCCCUUGAUGUGUUUUUAGCGUAUGUGUCGAAAGCCCUCUUAGUAG";

    // nucSeq in Aminoacid
    // NKPLMCF*RMCRKPSFR***NKPLMCF*RMCRKPS**

    const std::string res = "RMCRKPSFR";
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

TEST(CodingSectionTestSuite, nextStopTest)
{
    biopp::NucSequence nucSeq("UAAUGGAAAUAGCAGAAGUGGACUCGGUCGUGCCCGUGAACAAUGUCCAAGACACCACUG"
                              "ACCAAAUGGAGAUGUUCAGGAUACCAGUGACCAUAAAUGCCCCUCUACAACAACAGGUUU"
                              "UUGGCCUCAGAUUGCAACCAGGCUUAGAUAGUGUGUUUAAGCACACUCUGUUGGGAGAAA"
                              "UUCUAAACUACUAUGCGCACUGGUCAGGCAGCAUGAAGCUGACAUUUGUGUUUUGCGGGU");
    biopp::AminoSequence seq;
    nucSeq.translate(seq);

    CodingSectionObtainer cso;

    const std::string expectedResult = "*WK*QKWTRSCP*TMSKTPLTKWRCSGYQ*P*MPLYNNRFLASDCNQA*IVCLSTLCWEKF*TTMRTGQAA*S*HLCFAG";
    ASSERT_EQ(seq.getString(), expectedResult);

    size_t result;
    const size_t first = 0;
    result = cso.getSubSeqBegining(first, seq);
    EXPECT_EQ(result, 1);

    const size_t second = 12;
    result = cso.getSubSeqBegining(second, seq);
    EXPECT_EQ(result, 13);

    const size_t third = 29;
    result = cso.getSubSeqBegining(third, seq);
    EXPECT_EQ(result, 30);

    const size_t fourth = 4;
    result = cso.getSubSeqEnding(fourth, seq);
    EXPECT_EQ(result, 11);

    const size_t fifth = 32;
    result = cso.getSubSeqEnding(fifth, seq);
    EXPECT_EQ(result, 47);

    const size_t sixth = 74;
    result = cso.getSubSeqEnding(sixth, seq);
    EXPECT_EQ(result, 79);
}


TEST(CodingSectionTestSuite, getMaxSubSequence)
{
    biopp::NucSequence nucSeq("UGUGUGUGCCCGAGGCUGAGAUGGGAGGAGCUGUGGUUGGACAAGCAUUUUCCGCCA"
                              "CCGCGAUGGCAAAUGGUGAUAAAGCAUAUGAGUUCACUAGCGCAACCCAAAGUGAUCAGA"
                              "CAAAAGUUCAAACUGCUAUACACAAUGCAGGGAUGGGCGUAGGUGUAGGGAACCUCACUA");
    biopp::AminoSequence seq;
    biopp::AminoSequence dest;
    nucSeq.translate(seq);
    //seq = aminoSeq = CVCPRLRWEELWLDKHFPPPRWQMVIKHMSSLAQPKVIRQKFKLLYTMQGWA*V*GTSL

    const std::string result = "CVCPRLRWEELWLDKHFPPPRWQMVIKHMSSLAQPKVIRQKFKLLYTMQGWA";
    CodingSectionObtainer::SubSequenceDescriptor subSeq(0, 51);
    CodingSectionObtainer cso;
    cso.getMaxSubSequence(subSeq, seq, dest);

    EXPECT_EQ(dest.getString(), result);
}