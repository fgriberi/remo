/**
 * @file     outputsGeneratorTest.cpp
 * @brief    Defines the test for outputsGenerator class.
 *
 * @author   Franco Riberi
 * @email    fgriberi AT gmail.com
 *
 * Contents: test case
 *
 * System:   remo: RNAemo - RNA research project
 * Language: C++
 *
 * @date May 9, 2013
 *
 * Copyright (C) 2013 Franco Riberi, FuDePAN
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
#include "remo/OutputsGenerator.h"
#include "remo/CodingSectionObtainer.h"
#include "remo/Exceptions.h"

using namespace remo;
using namespace acuoso;

TEST(OutputsGeneratorTestSuite, replaceHumanizedSection)
{
    const biopp::NucSequence originalSeq("GGAAGCUGGAAAUGUUCACUUAUCUUAGGUUUGAUAUGGAGGUAACUUUU"
                                         "GUGAUCACAAGUCGACAAGACCCCGGAACAACCCUAGCUCAGGACAUGCC"
                                         "CGUGUUGACGCGCCAAAUCAUAUGUAUGUGCCACCUGGCGGUCCGAUUCC"
                                         "AGCAAAAGUUGAUGAUUAUGCCUGGCAGACGUCUACAAACCCCAGCAUUU"
                                         "UCUGGACGGAAGGAAACGCACCAGCGCGCAUGUCCAUCCCAUUUAUCAGC"
                                         "UUUAUAUAUAUAGGAAAUGCAUACAGCAAUUUUUAUGACGGGUGGUCAAA"
                                         "UUUUGAUCAGAGGGGCUCAUACGGGUACAAUACCCUGAAUAACUUAGGUC"
                                         "ACAUAUAUGUGAGACACGUGAGUGCGAAAGAAGUAGUCCUCACCCAAUCA"
                                         "CGAGCACUAUUAGAGUGUAUUUCAAGCCAAAACAUACGGCAGAGCUUGGG"
                                         "UGCCGCGCCCUCCAAGGCUAUGCCAAUACAAGAAGGCAUUUAGCGUGGAU"
                                         "UUCACGCCAACUCCCAUUACAGACACCAGGAAAGACAUCAACACUGUAAC"
                                         "CACCGUGGCGCAAAGUCGGCGUCGGGGUGACAUGUCCACCCUUAACACGC"
                                         "AUGGUGCCUUCGGACAAC");

    biopp::AminoSequence aminoSeq;
    biopp::NucSequence humanizedSeq;

    ICodonUsageModifier* humanizer = mili::FactoryRegistry<ICodonUsageModifier, std::string>::new_class("GeneDesign");
    ASSERT_TRUE(humanizer != NULL);

    humanizer->setOrganism(ICodonUsageModifier::Organism(3)); //human organism
    size_t initIndex = 0;
    CodingSectionObtainer cso;
    cso.getCodingSection(originalSeq, aminoSeq, initIndex);

    EXPECT_NO_THROW(humanizer->changeCodonUsage(aminoSeq, humanizedSeq));
    delete humanizer;

    size_t initNucIndex = 342;
    biopp::NucSequence toFoldSeq;

    OutputsGenerator::replaceHumanizedSection(originalSeq, humanizedSeq, initNucIndex, toFoldSeq);

    const std::string expectedResult = "GGAAGCUGGAAAUGUUCACUUAUCUUAGGUUUGAUAUGGAGGUAACUUUU"
                                       "GUGAUCACAAGUCGACAAGACCCCGGAACAACCCUAGCUCAGGACAUGCC"
                                       "CGUGUUGACGCGCCAAAUCAUAUGUAUGUGCCACCUGGCGGUCCGAUUCC"
                                       "AGCAAAAGUUGAUGAUUAUGCCUGGCAGACGUCUACAAACCCCAGCAUUU"
                                       "UCUGGACGGAAGGAAACGCACCAGCGCGCAUGUCCAUCCCAUUUAUCAGC"
                                       "UUUAUAUAUAUAGGAAAUGCAUACAGCAAUUUUUAUGACGGGUGGUCAAA"
                                       "UUUUGAUCAGAGGGGCUCAUACGGGUACAAUACCCUGAAUAACUGCGCAG"
                                       "CCACAUCUGCGAGACCCGCGAGUGCGAGCGCAGCAGCCCCCACCCCAUCA"
                                       "CCAGCACCAUCCGCGUGUACUUCAAGCCCAAGCACACCGCCGAGCUGGGC"
                                       "UGCCGCGCCCUGCAGGGCUACGCCAACACCCGCCGCCACCUGGCCUGGAU"
                                       "CAGCCGCCAGCUGCCCCUGCAGACCCCCGGCAAGACCAGCACCCUGUAAC"
                                       "CACCGUGGCGCAAAGUCGGCGUCGGGGUGACAUGUCCACCCUUAACACGC"
                                       "AUGGUGCCUUCGGACAAC";

    EXPECT_EQ(toFoldSeq.getString(), expectedResult);
    EXPECT_NE(originalSeq.getString(), toFoldSeq.getString());
}

TEST(OutputsGeneratorTestSuite, parseFileName)
{
    const std::string desc1   = "gi|221214|dbj|D00627.1|CXA9CG Human coxsackievirus A9 genomic RNA, complete genome, strain: Griggs2";
    const std::string desc2   = "gi|5524735|gb|AF119795.2| Enterovirus 71 strain TW/2272/98 polyprotein gene, complete cds";
    const std::string desc3   = "gi|22131|p";

    const std::string result1 = "D00627.1";
    const std::string result2 = "AF119795.2";
    const std::string result3 = "gi|22131|p";

    std::string name1;
    std::string name2;
    std::string name3;
    OutputsGenerator og;
    og.parseFileName(desc1, name1);
    og.parseFileName(desc2, name2);
    og.parseFileName(desc3, name3);

    EXPECT_EQ(name1, result1);
    EXPECT_EQ(name2, result2);
    EXPECT_EQ(name3, result3);
}

TEST(OutputsGeneratorTestSuite, parseNameMicro)
{
    const std::string micro1 = "hsa-miR-576-3p MIMAT0004796";
    const std::string micro2 = "hsa-miR-140-5p MIMAT0000431";
    const std::string micro3 = "hsa-2682-5p MIMAT0013517 MIADSS112";
    const std::string micro4 = "hsa-miR";

    const std::string result1 = "MIMAT0004796";
    const std::string result2 = "MIMAT0000431";
    std::string name1;
    std::string name2;
    OutputsGenerator og;
    og.parseNameMicro(micro1, name1);
    og.parseNameMicro(micro2, name2);

    EXPECT_EQ(name1, result1);
    EXPECT_EQ(name2, result2);

    EXPECT_THROW(og.parseNameMicro(micro3, name1), RemoException);
    EXPECT_THROW(og.parseNameMicro(micro4, name2), RemoException);
}