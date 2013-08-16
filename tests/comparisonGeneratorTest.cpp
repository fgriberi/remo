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
    const size_t stackSize1 = 2;
    const size_t stackSize2 = 3;
    const size_t stackSize3 = 7;

    ThermDetailsListener *listener = new ThermDetailsListener();    
    initStacks(listener->_currentData);
    const size_t initSizeMap = listener->_currentData.size();

    //add an element that exists in the map
    listener->addStack(stackSize1);
    listener->addStack(stackSize2);    

    EXPECT_TRUE(listener->_currentData.size() == initSizeMap);
    EXPECT_TRUE(listener->_currentData[stackSize1] == 5);
    EXPECT_TRUE(listener->_currentData[stackSize2] == 4);

    //add an element that does not exist in the map
    listener->addStack(stackSize3);
    EXPECT_TRUE(listener->_currentData.size() == initSizeMap + 1);
    EXPECT_TRUE(listener->_currentData[stackSize3] == 1);
}

void setMotif(const std::string& name, const size_t att, size_t const stacks, IMotifObserverRemo::Motif& motif)
{
    motif.nameMotif = name;
    motif.attribute = att;
    motif.amountStacks = stacks;
}

typedef std::list<fideo::IMotifObserver::Motif> Motifs;

TEST(ComparisonGeneratorTestSuite, processMotif)
{
    //build motif list
    Motifs motifs;

    fideo::IMotifObserver::Motif external;
    setMotif("External loop", 16, 3, external);
    motifs.push_back(external);

    fideo::IMotifObserver::Motif bulge1;
    setMotif("Bulge loop", 4, 4, bulge1);
    motifs.push_back(bulge1);

    fideo::IMotifObserver::Motif multi1;
    setMotif("Multi-loop", 9, 5, multi1);
    motifs.push_back(multi1);

    fideo::IMotifObserver::Motif interior;
    setMotif("Interior Asymmetric", 2, 4, interior);
    motifs.push_back(interior);

    fideo::IMotifObserver::Motif bulge2;
    setMotif("Bulge loop", 8, 8, bulge2);
    motifs.push_back(bulge2);

    fideo::IMotifObserver::Motif multi2;
    setMotif("Multi-loop", 14, 4, multi2);
    motifs.push_back(multi2);

    fideo::IMotifObserver::Motif bulge3;
    setMotif("Bulge loop", 3, 4, bulge3);
    motifs.push_back(bulge3);

    const size_t tBulge = 4;
    const size_t tInterior = 3;
    
    ThermDetailsListener *listener = new ThermDetailsListener();
    listener->setTolerances(tBulge, tInterior);

    Motifs::const_iterator pos;

    listener->start();
    for (pos = motifs.begin(); pos != motifs.end(); ++pos)
    {
        listener->processMotif(*pos);
    }
    listener->finalize();
    //expected map = <3,1>,<4,1>,<8,2>,<9,1>
    EXPECT_TRUE(listener->_currentData.size() == 4);
    
    Stacks::iterator it = listener->_currentData.begin();

    //first value of map    
    EXPECT_TRUE(it->first == 3);
    EXPECT_TRUE(it->second == 1);
    ++it;
    
    //second value of map
    EXPECT_TRUE(it->first == 4);
    EXPECT_TRUE(it->second == 1); 
    ++it;

    //third value of map
    EXPECT_TRUE(it->first == 8); 
    EXPECT_TRUE(it->second == 2);
    ++it;

    //fourth value of map
    EXPECT_TRUE(it->first == 9);
    EXPECT_TRUE(it->second == 1);
    ASSERT_TRUE(++it == listener->_currentData.end());
}












