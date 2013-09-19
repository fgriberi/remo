/*
 * @file     Application.h
 * @brief    Provide the interface to Application window.
 *
 * @author   Franco Riberi
 * @email    fgriberi AT gmail.com
 *
 * Contents: Source file for r-emo providing Application interface.
 *
 * Language: C++
 *
 * @date      September 2013
 *
 * This file is part of r-emo.
 *
 * Copyright (C) 2013 - Franco Riberi, FuDePAN.
 *
 * r-emo is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * r-emo is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with r-emo. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include "MainWindow.h"

class Application : QApplication
{
    Q_OBJECT

public:
    Application(int argc, char** argv)
        : QApplication(argc, argv)
    {}
    int run();

private:
    MainWindow window;
};

#endif
