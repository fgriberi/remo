/**
 * @file     ComparisonWindow.h
 * @brief    Provide the interface to Comparison window.
 *
 * @author   Franco Riberi
 * @email    fgriberi AT gmail.com
 *
 * Contents: Source file for r-emo providing Comparison interface.
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

#ifndef COMPARISON_WINDOW_H
#define COMPARISON_WINDOW_H

#include <QCoreApplication>
#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QString>
#include <QDir>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QFrame>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>
#include <QtGui/QComboBox>
#include <QtGui/QCheckBox>
#include <QtGui/QGroupBox>
#include <QtGui/QRadioButton>

class ComparisonWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ComparisonWindow(QWidget* parent = 0);
    ~ComparisonWindow() {};

private slots:
    void on_btnExplore_clicked();
    void on_btnAccept_clicked();
    void on_btnCancel_clicked();
    void on_exit_triggered();
    void on_about_triggered();
    void checkBoxIsCircActivated();
    void checkBoxYesCirc(int state);
    void checkBoxNoCirc(int state);
    void radioButtonActivated();
    void comboBoxHumanizerActivated();
    void comboBoxBulgeActivated();
    void comboBoxInteriorActivated();
    void btnAcceptActivated();
    void checkPrefoldAndDontFoldActivate();

private:
    // setup window
    void setupUi(QMainWindow* ComparisonWindow);
    void retranslateUi(QMainWindow* ComparisonWindow);

    // fill comboBox
    void fillComboBoxHumanizer();
    void fillComboBoxTolerance();
    bool includeFlag(QCheckBox* checkBox);
    
    //labels declaration
    QLabel* labelRNAm;
    QLabel* labelIsCirc;
    QLabel* labelOrganism;
    QLabel* labelHumanizer;
    QLabel* labelTBulge;
    QLabel* labelTInterior;
    QLabel* labelPrefold;
    QLabel* labelDontFold;

    //lineEdits declaration
    QLineEdit* nameFileRNAm;

    //comboBox declaration
    QComboBox* comboBoxHumanizer;
    QComboBox* comboBoxBulge;
    QComboBox* comboBoxInterior;

    //checkBox declaration
    QCheckBox* checkBoxIsCircYes;
    QCheckBox* checkBoxIsCircNo;
    QCheckBox* checkBoxPrefold;
    QCheckBox* checkBoxDontFold;

    //declaration radioButton
    QRadioButton* radio1;
    QRadioButton* radio2;
    QRadioButton* radio3;
    QRadioButton* radio4;
    QRadioButton* radio5;
    QRadioButton* radio6;

    //buttons declaration
    QPushButton* btnExplore;
    QPushButton* btnAccept;
    QPushButton* btnCancel;

    //others
    QAction* exit;
    QAction* about;
    QWidget* centralWidget;
    QFrame* frame;
    QMenuBar* menuBar;
    QMenu* menuFile;
    QMenu* menuHelp;
};

#endif /* COMPARISON_WINDOW_H */