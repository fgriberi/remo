/**
 * @file     comparisonGeneratorTest.cpp
 * @brief    Defines the test for comparisonGenerator class.
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
#include <gtest/gtest.h>
#include "remo/ComparisonGenerator.h"
#include "remo/IMotifObserverRemo.h"
#include "remo/ThermDetailsListener.h"

using namespace remo;

/// Temporal functions
int linkFictitious();

/** @brief Init map with specific value
*
* @param mapStack: map to fill
* @return void
*/
void initStacks(Stacks& mapStacks)
{
    mapStacks[6] = 2;
    mapStacks[1] = 1;
    mapStacks[3] = 3;
    mapStacks[2] = 4;
}

TEST(ComparisonGeneratorTestSuite, addStackMethod)
{
    linkFictitious();
    const size_t stackSize1 = 2;
    const size_t stackSize2 = 3;
    const size_t stackSize3 = 7;

    Stacks mapStacks; //<sizeStacks, amount>
    initStacks(mapStacks);
    const size_t initSizeMap = mapStacks.size();

    ComparisonGenerator cg;

    //add an element that exists in the map
    cg.addStack(stackSize1, mapStacks);
    cg.addStack(stackSize2, mapStacks);
    EXPECT_TRUE(mapStacks.size() == initSizeMap);
    EXPECT_TRUE(mapStacks[stackSize1] == 5);
    EXPECT_TRUE(mapStacks[stackSize2] == 4);

    //add an element that does not exist in the map
    cg.addStack(stackSize3, mapStacks);
    EXPECT_TRUE(mapStacks.size() == initSizeMap + 1);
    EXPECT_TRUE(mapStacks[stackSize3] == 1);
}

void setMotif(IMotifObserverRemo::Motif& motif, const std::string& name, const size_t att, size_t const stacks)
{
    motif.nameMotif = name;
    motif.attribute = att;
    motif.amountStacks = stacks;
}

TEST(ComparisonGeneratorTestSuite, calculateSpecificMotifStacksMethod)
{
    //stacks does not break
    IMotifObserverRemo::Motif bulge;
    setMotif(bulge, "Bulge loop", 1, 4);

    const size_t tolerance = 3;
    size_t previous = 2;
    size_t oldPrevious = previous;
    Stacks mapStacks;
    initStacks(mapStacks);

    ComparisonGenerator cg;
    cg.calculateSpecificMotifStacks(bulge, tolerance, previous, mapStacks);
    EXPECT_TRUE(previous == oldPrevious + bulge.amountStacks);
    oldPrevious = previous;

    //broken stacks
    IMotifObserverRemo::Motif interior;
    setMotif(interior, "Interior loop", 5, 2);

    cg.calculateSpecificMotifStacks(interior, tolerance, previous, mapStacks);

    EXPECT_TRUE(mapStacks[oldPrevious] == 3); //added stack with size previous (6)
    EXPECT_TRUE(previous == interior.amountStacks);
}

TEST(ComparisonGeneratorTestSuite, calculateStacksMethod)
{
    //build MotifsData
    IMotifObserverRemo::MotifsData motifs;

    IMotifObserverRemo::Motif external;
    setMotif(external, "External loop", 16, 3);
    motifs.push_back(external);

    IMotifObserverRemo::Motif bulge1;
    setMotif(bulge1, "Bulge loop", 4, 4);
    motifs.push_back(bulge1);

    IMotifObserverRemo::Motif multi1;
    setMotif(multi1, "Multi-loop", 9, 5);
    motifs.push_back(multi1);

    IMotifObserverRemo::Motif interior;
    setMotif(interior, "Interior Asymmetric", 2, 4);
    motifs.push_back(interior);

    IMotifObserverRemo::Motif bulge2;
    setMotif(bulge2, "Bulge loop", 8, 8);
    motifs.push_back(bulge2);

    IMotifObserverRemo::Motif multi2;
    setMotif(multi2, "Multi-loop", 14, 4);
    motifs.push_back(multi2);

    IMotifObserverRemo::Motif bulge3;
    setMotif(bulge3, "Bulge loop", 3, 4);
    motifs.push_back(bulge3);

    const size_t tBulge = 4;
    const size_t tInterior = 3;
    Stacks currentStacks;

    ComparisonGenerator cg;
    cg.calculateStacks(motifs, tBulge, tInterior, currentStacks);

    EXPECT_TRUE(currentStacks.size() == 4);
    Stacks::iterator it = currentStacks.begin();

    //first value of map
    EXPECT_TRUE(it->first == 3);
    EXPECT_TRUE(it->second == 1);
    ASSERT_TRUE(++it != currentStacks.end());

    //second value of map
    EXPECT_TRUE(it->first == 4);
    EXPECT_TRUE(it->second == 1);
    ASSERT_TRUE(++it != currentStacks.end());

    //third value of map
    EXPECT_TRUE(it->first == 8);
    EXPECT_TRUE(it->second == 2);
    ASSERT_TRUE(++it != currentStacks.end());

    //fourth value of map
    EXPECT_TRUE(it->first == 9);
    EXPECT_TRUE(it->second == 1);
    ASSERT_TRUE(++it == currentStacks.end());
}