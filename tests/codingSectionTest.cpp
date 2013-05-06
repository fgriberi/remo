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
#include <remo/remo.h>

TEST(CodingSectionTestSuite, withoutStopCodon)
{
    const std::string nucSeq = "GCUGUGUGUUGUGUGUGCCAUGGAUCAGUCAAACACAUUAUAGGCUUGUACAGCAGGAUG"
                               "AGUACACCAGCGCUGGUUACGUGACGUGUUGGUAUCAGACUGGUAUGAUUGUCCCACCAG"
                               "GAACCCCAAAUUC";
    // nucSeq in Aminoacid
    // AVCCVCHGSVKHIIGLYSRMSTPALVT

    const biopp::NucSequence seq(nucSeq);
    biopp::AminoSequence dest;
    size_t init = 0;
    CodingSectionObtainer cso;
    cso.getCodingSection(seq, dest, init);

    const std::string res = "AVCCVCHGSVKHIIGLYSRMSTPALVT";

    ASSERT_EQ(dest.getString(), res);
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

    const biopp::NucSequence seq(nucSeq);
    biopp::AminoSequence dest;
    size_t init = 0;
    CodingSectionObtainer cso;
    cso.getCodingSection(seq, dest, init);

    const std::string res = "MRLIPTAEHAPSNQGAACRNGQLCSGTDYFGCPCFFLFLYWLLMVTIERLLPYSYWIG"
                            "HPVSNRAIVYLFTGFIPLNYKEVKTLHLILLFNTTKWELKCQHRKLEL";

    ASSERT_EQ(dest.getString(), res);
}

TEST(CodingSectionTestSuite, greaterLeftCodingSection)
{
    const std::string nucSeq = "UGUGUGUGCCCGAGGCUGAGAUGGGAGGAGCUGUGGUUGGACAAGCAUUUUCCGCCA"
                               "CCGCGAUGGCAAAUGGUGAUAAAGCAUAUGAGUUCACUAGCGCAACCCAAAGUGAUCAGA"
                               "CAAAAGUUCAAACUGCUAUACACAAUGCAGGGAUGGGCGUAGGUGUAGGGAACCUCACUA";
    // nucSeq in Aminoacid
    // CVCPRLRWEELWLDKHFPPPRWQMVIKHMSSLAQPKVIRQKFKLLYTMQGWA*V*GTSL

    const biopp::NucSequence seq(nucSeq);
    biopp::AminoSequence dest;
    size_t init = 0;
    CodingSectionObtainer cso;
    cso.getCodingSection(seq, dest, init);

    const std::string res = "CVCPRLRWEELWLDKHFPPPRWQMVIKHMSSLAQPKVIRQKFKLLYTMQGWA";

    ASSERT_EQ(dest.getString(), res);
}

TEST(CodingSectionTestSuite, greaterCodingSectionInTheMiddle)
{
    const std::string nucSeq = "UUUUAGCCGCCCGAGCAAAACAGCCUGUGGGUUGUUCCCACCCACAGGCGCCACCGGGCGUUAGCACACUGGU"
                               "AUCACGGUACCCUUGUGCGCCUGUUUUAUAACCCCACCCCGAGUAAACCUUAGAAGCAAUAG";
    // nucSeq in Aminoacid
    // F*PPEQNSLWVVPTHRRHRALAHWYHGTLVRLFYNPTPSKP*KQ*

    const biopp::NucSequence seq(nucSeq);
    biopp::AminoSequence dest;
    size_t init = 0;
    CodingSectionObtainer cso;
    cso.getCodingSection(seq, dest, init);

    const std::string res = "PPEQNSLWVVPTHRRHRALAHWYHGTLVRLFYNPTPSKP";

    ASSERT_EQ(dest.getString(), res);
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
    EXPECT_THROW(cso.getCodingSection(seq, dest, init), RemoTools::RemoException);
    //Two largar subsequences with equals size
}