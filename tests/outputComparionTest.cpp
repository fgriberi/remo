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

/// Temporal functions
int linkFictitious();

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
    linkFictitious();    
    OutputComparison oc(nameFile);

    EXPECT_TRUE(oc.currentMaxStack == 0);
    EXPECT_TRUE(existFile(oc.comparisonFile));
    unlinkFile();
}


TEST(OutputComparisonTestSuite, maximumStackMethod)
{
    Stacks original;    
    original[6] = 2;
    original[1] = 1;
    original[7] = 7;
    original[2] = 4;

    Stacks humanized;
    humanized[2] = 2;
    humanized[3] = 11;
    humanized[7] = 1;
    humanized[9] = 5;

    OutputComparison oc(nameFile);
    const size_t max = oc.maximumStack(original, humanized);
    EXPECT_TRUE(max == 9);
    unlinkFile();
}

TEST(OutputComparisonTestSuite, updateSubHeader)
{
    size_t limit = 4;
    OutputComparison oc(nameFile);
    oc.updateSubHeader(limit);
    EXPECT_TRUE(oc.currentMaxStack == limit);
    const std::string expectedResult1 = ", 1, 2, 3, 4, 1, 2, 3, 4";

    std:: ifstream file(nameFile.c_str());
    std::string subHeaderLine;        
    std::getline(file, subHeaderLine);
    EXPECT_EQ(expectedResult1, subHeaderLine);

    limit = 6;
    const size_t oldLimit = limit;
    oc.updateSubHeader(limit);
    EXPECT_TRUE(oc.currentMaxStack == limit);
    const std::string expectedResult2 = ", 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6";    

    file.seekg(0);
    std::getline(file, subHeaderLine);
    EXPECT_EQ(expectedResult2, subHeaderLine);    

    limit = 3;
    oc.updateSubHeader(limit);
    EXPECT_TRUE(oc.currentMaxStack == oldLimit);
    file.seekg(0);
    std::getline(file, subHeaderLine);
    EXPECT_EQ(expectedResult2, subHeaderLine);        
    unlinkFile();
}

TEST(OutputComparisonTestSuite, fillRowMethod)
{
    Stacks original;    
    original[3] = 2;
    original[2] = 8;
    original[1] = 2;
    original[5] = 4;

    Stacks humanized;
    humanized[4] = 2;
    humanized[2] = 6;
    humanized[1] = 1;
    humanized[6] = 2;

    OutputComparison oc(nameFile);
    const size_t limit = oc.maximumStack(original, humanized);
    oc.updateSubHeader(limit);
    oc.fillRow(original, humanized);

    const std::string expectedResult = ", 2, 8, 2, 0, 4, 0, 1, 6, 0, 2, 0, 2";
    std:: ifstream file(nameFile.c_str());
    std::string dataLine;        
    std::getline(file, dataLine); //subHeader
    std::getline(file, dataLine);
    EXPECT_EQ(expectedResult, dataLine);
    unlinkFile();
}
