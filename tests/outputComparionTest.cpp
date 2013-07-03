/**
 * @file     outputComparionTest.cpp
 * @brief    Defines the test for outputComparion class.
 *
 * @author   Franco Riberi
 * @email    fgriberi AT gmail.com
 *
 * Contents: test case
 *
 * System:   remo: RNAemo - RNA research project
 * Language: C++
 *
 * @date May 29, 2013
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
#include <etilico/etilico.h>
#include <mili/mili.h>
#include <gtest/gtest.h>
#include "remo/OutputComparison.h"
#include "remo/Exceptions.h"

using namespace remo;

/** @brief Check if the file exists
*
* @param file: file input
* @return true if file exists, otherwise false
*/
bool existFile(const std::ofstream& file)
{
    bool ret;
    if (file)
    {
        ret = true;
    }
    else
    {
        ret = false;
    }
    return ret;
}

static const std::string nameFile = "file.txt";

/** @brief Remove nameFile
*
* @return nameFile
*/
void unlinkFile()
{
    std::string filePath;
    etilico::getCurrentPath(filePath);
    filePath += ("/" + nameFile);
    mili::assert_throw<ExceptionUnlink>(unlink(filePath.c_str()) == 0);
}

TEST(OutputComparisonTestSuite, constructorOfClass)
{
    OutputComparison oc(nameFile);

    EXPECT_TRUE(existFile(oc.comparisonFile));
    unlinkFile();
}

void setStacksList(Stacks& original1, Stacks& humanized1, Stacks& original2, Stacks& humanized2, StacksStores& stacks)
{
    original1[6] = 2;
    original1[1] = 1;
    original1[7] = 7;
    original1[2] = 4;

    humanized1[2] = 2;
    humanized1[3] = 11;
    humanized1[7] = 1;
    humanized1[9] = 5;

    original2[2] = 4;
    original2[7] = 5;

    humanized2[11] = 1;
    humanized2[3] = 5;
    humanized2[1] = 8;
    humanized2[3] = 5;

    StacksSave elem1;
    elem1.nameSequence = "Seq1";
    elem1.orig = original1;
    elem1.hum = humanized1;

    StacksSave elem2;
    elem2.nameSequence = "Seq2";
    elem2.orig = original2;
    elem2.hum = humanized2;

    stacks.push_back(elem1);
    stacks.push_back(elem2);
}

TEST(OutputComparisonTestSuite, maximumStackMethod)
{
    //build list
    Stacks original1;
    Stacks humanized1;
    Stacks original2;
    Stacks humanized2;
    StacksStores stacks;
    setStacksList(original1, humanized1, original2, humanized2, stacks);

    OutputComparison oc(nameFile);
    const size_t max = oc.maximumStack(stacks);
    EXPECT_TRUE(max == 11);
    unlinkFile();
}

TEST(OutputComparisonTestSuite, generateHeaderMethod)
{
    size_t limit = 6;
    OutputComparison oc(nameFile);
    oc.generateHeader(limit);
    const std::string expectedResult1 = "RNAm, , , , Original, , , , , Humanized, , , ";
    limit = 5;
    oc.generateHeader(limit);
    const std::string expectedResult2 = "RNAm, , , Original, , , , Humanized, , , ";

    std:: ifstream file(nameFile.c_str());
    std::string subHeaderLine;
    std::getline(file, subHeaderLine);
    EXPECT_EQ(expectedResult1, subHeaderLine);
    std::getline(file, subHeaderLine);
    EXPECT_EQ(expectedResult2, subHeaderLine);
    unlinkFile();
}

TEST(OutputComparisonTestSuite, generateSubHeaderMethod)
{
    const size_t limit = 4;
    OutputComparison oc(nameFile);
    oc.generateSubHeader(limit);
    const std::string expectedResult = ", 1, 2, 3, 4, 1, 2, 3, 4";

    std:: ifstream file(nameFile.c_str());
    std::string subHeaderLine;
    std::getline(file, subHeaderLine);
    EXPECT_EQ(expectedResult, subHeaderLine);
    unlinkFile();
}

TEST(OutputComparisonTestSuite, fillRowMethod)
{
    Stacks original1;
    Stacks humanized1;
    Stacks original2;
    Stacks humanized2;
    StacksStores stacks;
    setStacksList(original1, humanized1, original2, humanized2, stacks);

    OutputComparison oc(nameFile);
    const size_t limit = oc.maximumStack(stacks);
    oc.fillRow(stacks, limit);

    const std::string firstLine = "Seq1, 1, 4, 0, 0, 0, 2, 7, 0, 0, 0, 0, 0, 2, 11, 0, 0, 0, 1, 0, 5, 0, 0";
    const std::string secondLine = "Seq2, 0, 4, 0, 0, 0, 0, 5, 0, 0, 0, 0, 8, 0, 5, 0, 0, 0, 0, 0, 0, 0, 1";

    std:: ifstream file(nameFile.c_str());
    std::string dataLine;
    std::getline(file, dataLine);
    EXPECT_EQ(firstLine, dataLine);
    std::getline(file, dataLine);
    EXPECT_EQ(secondLine, dataLine);
    unlinkFile();
}

TEST(OutputComparisonTestSuite, saveMethod)
{
    Stacks original1;
    original1[3] = 2;
    original1[2] = 8;
    original1[1] = 2;
    original1[5] = 4;

    Stacks humanized1;
    humanized1[4] = 2;
    humanized1[2] = 6;
    humanized1[1] = 1;
    humanized1[6] = 2;

    Stacks original2;
    original2[1] = 2;
    original2[3] = 6;
    original2[6] = 5;
    original2[2] = 4;

    Stacks humanized2;
    humanized2[4] = 3;
    humanized2[9] = 5;
    humanized2[2] = 8;
    humanized2[5] = 1;
    humanized2[3] = 10;
    humanized2[8] = 2;

    Stacks original3;
    original3[1] = 9;
    original3[3] = 9;
    original3[6] = 9;
    original3[2] = 9;

    Stacks humanized3;
    humanized3[4] = 9;
    humanized3[1] = 9;
    humanized3[2] = 9;
    humanized3[5] = 9;
    humanized3[3] = 9;
    humanized3[8] = 9;

    StacksSave elem1;
    elem1.nameSequence = "Seq1";
    elem1.orig = original1;
    elem1.hum = humanized1;
    StacksSave elem2;
    elem2.nameSequence = "Seq2";
    elem2.orig = original2;
    elem2.hum = humanized2;
    StacksSave elem3;
    elem3.nameSequence = "Seq3";
    elem3.orig = original3;
    elem3.hum = humanized3;
    StacksStores stacks;

    stacks.push_back(elem1);
    stacks.push_back(elem2);
    stacks.push_back(elem3);

    OutputComparison oc(nameFile);
    oc.save(stacks);

    const std::string expectedHeader = "RNAm, , , , , Original, , , , , , , , Humanized, , , , , ";
    const std::string expectedSubHeader = ", 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9";
    const std::string firstLine = "Seq1, 2, 8, 2, 0, 4, 0, 0, 0, 0, 1, 6, 0, 2, 0, 2, 0, 0, 0";
    const std::string secondLine = "Seq2, 2, 4, 6, 0, 0, 5, 0, 0, 0, 0, 8, 10, 3, 1, 0, 0, 2, 5";
    const std::string thirdLine = "Seq3, 9, 9, 9, 0, 0, 9, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 9, 0";

    std:: ifstream file(nameFile.c_str());
    std::string dataLine;
    std::getline(file, dataLine); //header
    EXPECT_EQ(expectedHeader, dataLine);

    std::getline(file, dataLine); //sub-header
    EXPECT_EQ(expectedSubHeader, dataLine);

    std::getline(file, dataLine); //sub-header
    EXPECT_EQ(firstLine, dataLine);

    std::getline(file, dataLine); //sub-header
    EXPECT_EQ(secondLine, dataLine);

    std::getline(file, dataLine); //sub-header
    EXPECT_EQ(thirdLine, dataLine);
}