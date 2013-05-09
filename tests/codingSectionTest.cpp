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

#define private public

#include <string>
#include <fstream>
#include <biopp/biopp.h>
#include <mili/mili.h>
#include <gtest/gtest.h>
#include <remo/remo.h>

using namespace remo;

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