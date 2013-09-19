/**
 * @file     ComparisonWindow.cpp
 * @brief    Is a implementation of Comparison interface.
 *
 * @author   Franco Riberi
 * @email    fgriberi AT gmail.com
 *
 * Contents: Source file for r-emo providing Comparison window implementation.
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

#include <list>
#include <iostream>
#include "AboutDialog.h"
#include "Service.h"
#include "ComparisonWindow.h"

ComparisonWindow::ComparisonWindow(QWidget* parent) : QMainWindow(parent)
{
    this->setGeometry(500, 200, 450, 422);
    this->setFixedSize(400, 420);

    setupUi(this);
    connect(this->checkBoxIsCircYes, SIGNAL(stateChanged(int)), this, SLOT(checkBoxYesCirc(int)));
    connect(this->checkBoxIsCircNo, SIGNAL(stateChanged(int)), this, SLOT(checkBoxNoCirc(int)));
    connect(this->comboBoxHumanizer, SIGNAL(activated(int)), this, SLOT(comboBoxBulgeActivated()));
    connect(this->comboBoxHumanizer, SIGNAL(activated(int)), this, SLOT(comboBoxInteriorActivated()));
    connect(this->comboBoxHumanizer, SIGNAL(activated(int)), this, SLOT(checkPrefoldAndDontFoldActivate()));
    connect(this->comboBoxHumanizer, SIGNAL(activated(int)), this, SLOT(btnAcceptActivated()));
    this->setWindowModality(Qt::ApplicationModal);
}

void ComparisonWindow::setupUi(QMainWindow* ComparisonWindow)
{
    if (ComparisonWindow->objectName().isEmpty())
    {
        ComparisonWindow->setObjectName(QString::fromUtf8("ComparisonWindow"));
    }
    /// create the objects
    centralWidget = new QWidget(ComparisonWindow);
    centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
    frame = new QFrame(centralWidget);
    frame->setObjectName(QString::fromUtf8("frame"));
    frame->setGeometry(QRect(10, 10, 380, 400));
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Raised);

    // labels
    labelRNAm = new QLabel(frame);
    labelRNAm->setObjectName(QString::fromUtf8("labelRNAm"));
    labelRNAm->setGeometry(QRect(20, 12, 81, 21));

    labelIsCirc = new QLabel(frame);
    labelIsCirc->setObjectName(QString::fromUtf8("labelIsCirc"));
    labelIsCirc->setGeometry(QRect(7, 50, 85, 21));

    labelOrganism = new QLabel(frame);
    labelOrganism->setObjectName(QString::fromUtf8("nameFilemiRNA"));
    labelOrganism->setGeometry(QRect(22, 80, 165, 27));

    labelHumanizer = new QLabel(frame);
    labelHumanizer->setObjectName(QString::fromUtf8("labelHumanizer"));
    labelHumanizer->setGeometry(QRect(17, 185, 74, 17));

    labelTBulge = new QLabel(frame);
    labelTBulge->setObjectName(QString::fromUtf8("labelTBulbe"));
    labelTBulge->setGeometry(QRect(18, 225, 110, 17));

    labelTInterior = new QLabel(frame);
    labelTInterior->setObjectName(QString::fromUtf8("labelTInterior"));
    labelTInterior->setGeometry(QRect(17, 263, 120, 17));

    labelPrefold = new QLabel(frame);
    labelPrefold->setObjectName(QString::fromUtf8("labelPrefold"));
    labelPrefold->setGeometry(QRect(85, 295, 85, 21));

    labelDontFold = new QLabel(frame);
    labelDontFold->setObjectName(QString::fromUtf8("labelDontFold"));
    labelDontFold->setGeometry(QRect(70, 317, 85, 21));

    //lineEdit
    nameFileRNAm = new QLineEdit(frame);
    nameFileRNAm->setObjectName(QString::fromUtf8("nameFileRNAm"));
    nameFileRNAm->setGeometry(QRect(105, 10, 230, 27));

    //checkBox
    checkBoxIsCircYes = new QCheckBox(frame);
    checkBoxIsCircYes->setGeometry(QRect(105, 50, 161, 27));
    checkBoxIsCircYes->setText("Yes");
    checkBoxIsCircYes->setEnabled(false);

    checkBoxIsCircNo = new QCheckBox(frame);
    checkBoxIsCircNo->setGeometry(QRect(180, 50, 161, 27));
    checkBoxIsCircNo->setText("No");
    checkBoxIsCircNo->setEnabled(false);

    checkBoxPrefold = new QCheckBox(frame);
    checkBoxPrefold->setGeometry(QRect(146, 295, 161, 27));
    checkBoxPrefold->setText("");
    checkBoxPrefold->setEnabled(false);
    
    checkBoxDontFold = new QCheckBox(frame);
    checkBoxDontFold->setGeometry(QRect(146, 317, 161, 27));
    checkBoxDontFold->setText("");
    checkBoxDontFold->setEnabled(false);

    //radioButton
    radio1 = new QRadioButton(frame);
    radio1->setObjectName(QString::fromUtf8("radio1"));
    radio1->setGeometry(QRect(105, 85, 130, 27));
    radio1->setEnabled(false);

    radio2 = new QRadioButton(frame);
    radio2->setObjectName(QString::fromUtf8("radio2"));
    radio2->setGeometry(QRect(105, 115, 130, 27));
    radio2->setEnabled(false);

    radio3 = new QRadioButton(frame);
    radio3->setObjectName(QString::fromUtf8("radio3"));
    radio3->setGeometry(QRect(105, 145, 130, 27));
    radio3->setEnabled(false);

    radio4 = new QRadioButton(frame);
    radio4->setObjectName(QString::fromUtf8("radio4"));
    radio4->setGeometry(QRect(230, 85, 130, 27));
    radio4->setEnabled(false);

    radio5 = new QRadioButton(frame);
    radio5->setObjectName(QString::fromUtf8("radio5"));
    radio5->setGeometry(QRect(230, 115, 130, 27));
    radio5->setEnabled(false);

    radio6 = new QRadioButton(frame);
    radio6->setObjectName(QString::fromUtf8("radio6"));
    radio6->setGeometry(QRect(230, 145, 130, 27));
    radio6->setEnabled(false);

    //comboBox
    comboBoxHumanizer = new QComboBox(frame);
    comboBoxHumanizer->setObjectName(QString::fromUtf8("comboBoxHumanizer"));
    comboBoxHumanizer->setGeometry(QRect(100, 182, 270, 27));
    fillComboBoxHumanizer();
    comboBoxHumanizer->setEnabled(false);

    comboBoxBulge = new QComboBox(frame);
    comboBoxBulge->setObjectName(QString::fromUtf8("comboBoxBulge"));
    comboBoxBulge->setGeometry(QRect(148, 224, 220, 27));
    comboBoxBulge->setEnabled(false);

    comboBoxInterior = new QComboBox(frame);
    comboBoxInterior->setObjectName(QString::fromUtf8("comboBoxInterior"));
    comboBoxInterior->setGeometry(QRect(148, 261, 220, 27));
    comboBoxInterior->setEnabled(false);
    fillComboBoxTolerance();

    //buttons
    btnExplore = new QPushButton(frame);
    btnExplore->setObjectName(QString::fromUtf8("btnExplore"));
    btnExplore->setGeometry(QRect(336, 10, 31, 25));

    btnCancel = new QPushButton(frame);
    btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
    btnCancel->setGeometry(QRect(170, 355, 98, 27));

    btnAccept = new QPushButton(frame);
    btnAccept->setObjectName(QString::fromUtf8("btnAccept"));
    btnAccept->setGeometry(QRect(270, 355, 98, 27));
    btnAccept->setEnabled(false);

    //menuBar and others
    exit = new QAction(ComparisonWindow);
    exit->setObjectName(QString::fromUtf8("exit"));
    about = new QAction(ComparisonWindow);
    about->setObjectName(QString::fromUtf8("about"));
    ComparisonWindow->setCentralWidget(centralWidget);
    menuBar = new QMenuBar(ComparisonWindow);
    menuBar->setObjectName(QString::fromUtf8("menuBar"));
    menuBar->setGeometry(QRect(0, 0, 510, 23));
    menuFile = new QMenu(menuBar);
    menuFile->setObjectName(QString::fromUtf8("menuFile"));
    menuHelp = new QMenu(menuBar);
    menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
    ComparisonWindow->setMenuBar(menuBar);
    menuBar->addAction(menuFile->menuAction());
    menuBar->addAction(menuHelp->menuAction());
    menuFile->addAction(exit);
    menuHelp->addAction(about);
    retranslateUi(this);
    QMetaObject::connectSlotsByName(ComparisonWindow);
} // setupUi

void ComparisonWindow::retranslateUi(QMainWindow* ComparisonWindow)
{
    ComparisonWindow->setWindowTitle(QApplication::translate("ComparisonWindow", "Remo Project", 0, QApplication::UnicodeUTF8));
    exit->setText(QApplication::translate("ComparisonWindow", "Exit", 0, QApplication::UnicodeUTF8));
    about->setText(QApplication::translate("ComparisonWindow", "About", 0, QApplication::UnicodeUTF8));
    labelRNAm->setText(QApplication::translate("ComparisonWindow", "File RNAm:", 0, QApplication::UnicodeUTF8));
    labelIsCirc->setText(QApplication::translate("ComparisonWindow", "IsCirc RNAm:  fdfd", 0, QApplication::UnicodeUTF8));
    labelOrganism->setText(QApplication::translate("ComparisonWindow", "Organism:", 0, QApplication::UnicodeUTF8));
    labelPrefold->setText(QApplication::translate("ComparisonWindow", "Prefold: ", 0, QApplication::UnicodeUTF8));
    labelDontFold->setText(QApplication::translate("ComparisonWindow", "Dont Fold: ", 0, QApplication::UnicodeUTF8));
    radio1->setText(QApplication::translate("ComparisonWindow", "SCerevisiae", 0, QApplication::UnicodeUTF8));
    radio2->setText(QApplication::translate("ComparisonWindow", "EColi", 0, QApplication::UnicodeUTF8));
    radio3->setText(QApplication::translate("ComparisonWindow", "HSapiens", 0, QApplication::UnicodeUTF8));
    radio4->setText(QApplication::translate("ComparisonWindow", "CElegans", 0, QApplication::UnicodeUTF8));
    radio5->setText(QApplication::translate("ComparisonWindow", "DMelanogaster", 0, QApplication::UnicodeUTF8));
    radio6->setText(QApplication::translate("ComparisonWindow", "BSubtilis", 0, QApplication::UnicodeUTF8));
    labelHumanizer->setText(QApplication::translate("ComparisonWindow", "Humanizer:", 0, QApplication::UnicodeUTF8));
    labelTBulge->setText(QApplication::translate("ComparisonWindow", "Bulge Tolerance:", 0, QApplication::UnicodeUTF8));
    labelTInterior->setText(QApplication::translate("ComparisonWindow", "Interior Tolerance:", 0, QApplication::UnicodeUTF8));
    btnExplore->setText(QApplication::translate("ComparisonWindow", "...", 0, QApplication::UnicodeUTF8));
    btnAccept->setText(QApplication::translate("ComparisonWindow", "Accept", 0, QApplication::UnicodeUTF8));
    btnCancel->setText(QApplication::translate("ComparisonWindow", "Cancel", 0, QApplication::UnicodeUTF8));
    menuFile->setTitle(QApplication::translate("ComparisonWindow", "File", 0, QApplication::UnicodeUTF8));
    menuHelp->setTitle(QApplication::translate("ComparisonWindow", "Help", 0, QApplication::UnicodeUTF8));
}  //retranslateUi

static const std::string CHOOSE_OPTION = "Choose option";
static const std::string AD_HOC = "Ad hoc";
static const std::string FORMAL = "Formal";

void ComparisonWindow::fillComboBoxHumanizer()
{
    std::list<std::string> humBackends;
    Service::getHumanizerBackend(humBackends);
    QList<QString> stringsList;
    stringsList.append(CHOOSE_OPTION.c_str());
    std::list<std::string>::iterator it;
    for (it = humBackends.begin(); it != humBackends.end(); it++)
    {
        stringsList.append((*it).c_str());
    }
    comboBoxHumanizer->addItems(stringsList);
}

static const unsigned int LIMIT = 10;

void ComparisonWindow::fillComboBoxTolerance()
{
    QList<QString> list;
    for (unsigned int i = 0; i < LIMIT; ++i)
    {
        list.append(QString::number(i));
    }
    comboBoxBulge->addItems(list);
    comboBoxInterior->addItems(list);
}


void ComparisonWindow::on_btnExplore_clicked()
{
    QString file_selected = QFileDialog::getOpenFileName(this, tr("Select File"), QDir::currentPath(), tr("All files (*.*)"));

    if (!file_selected.isNull() && !file_selected.isEmpty())
    {
        nameFileRNAm->setText(file_selected);
        checkBoxIsCircActivated();
    }
    else
    {
        QMessageBox msgBox(QMessageBox::Information, "Remo", "A file must be selected");
        msgBox.exec();
    }
}

void ComparisonWindow::checkBoxYesCirc(int state)
{
    if (state == Qt::Checked)
    {
        checkBoxIsCircNo->setCheckState(Qt::Unchecked);
    }
}

void ComparisonWindow::checkBoxNoCirc(int state)
{
    if (state == Qt::Checked)
    {
        checkBoxIsCircYes->setCheckState(Qt::Unchecked);
    }
}

void ComparisonWindow::radioButtonActivated()
{
    radio1->setEnabled(true);
    radio2->setEnabled(true);
    radio3->setEnabled(true);
    radio3->setChecked(true);
    radio4->setEnabled(true);
    radio5->setEnabled(true);
    radio6->setEnabled(true);
}

void ComparisonWindow::checkBoxIsCircActivated()
{
    checkBoxIsCircYes->setEnabled(true);
    checkBoxIsCircYes->setChecked(true);
    checkBoxIsCircNo->setEnabled(true);
    radioButtonActivated();
    comboBoxHumanizerActivated();
}

void ComparisonWindow::checkPrefoldAndDontFoldActivate()
{
    checkBoxPrefold->setEnabled(true);
    checkBoxDontFold->setEnabled(true);
}

void ComparisonWindow::comboBoxBulgeActivated()
{
    comboBoxBulge->setEnabled(true);
}

void ComparisonWindow::comboBoxInteriorActivated()
{
    comboBoxInterior->setEnabled(true);
}

void ComparisonWindow::comboBoxHumanizerActivated()
{
    comboBoxHumanizer->setEnabled(true);
}

void ComparisonWindow::btnAcceptActivated()
{
    btnAccept->setEnabled(true);
}

bool ComparisonWindow::includeFlag(QCheckBox* checkBox)
{
    bool ret;
    if (checkBox->isChecked())
    {
        ret = true;
    }
    else
    {
        ret = false;
    }
    return ret;
}

void ComparisonWindow::on_btnAccept_clicked()
{
    // check that all correct fields
    if (!nameFileRNAm->text().isNull() && !nameFileRNAm->text().isEmpty())
    {
        const std::string humanizer = comboBoxHumanizer->currentText().toStdString();
        const std::string tBulge    = comboBoxBulge->currentText().toStdString();
        const std::string tInterior = comboBoxInterior->currentText().toStdString();
        const bool isCirc = includeFlag(checkBoxIsCircYes);
        const bool prefold = includeFlag(checkBoxPrefold);
        const bool dontFold = includeFlag(checkBoxDontFold);
        size_t org;
        if (radio1->isChecked())
        {
            org = 1;
        }
        else if (radio2->isChecked())
        {
            org = 2;
        }
        else if (radio3->isChecked())
        {
            org = 3;
        }
        else if (radio4->isChecked())
        {
            org = 4;
        }
        else if (radio5->isChecked())
        {
            org = 5;
        }
        else if (radio6->isChecked())
        {
            org = 6;
        }
        if (humanizer != CHOOSE_OPTION)
        {            
            const std::string fileRNAm  = nameFileRNAm->text().toStdString();
            std::string command;
            Service::generateArgumentToComparison(fileRNAm, humanizer, isCirc, org, tBulge, tInterior, command, prefold, dontFold);
            std::cout << "Execute: " << command << std::endl;
            Service::startRemo(command);
            QMessageBox msgBox(QMessageBox::Information, "Remo", "File generation completed.");
            msgBox.exec();
        }
        else
        {
            QMessageBox msgBox(QMessageBox::Information, "Remo", "A option must be selected");
            msgBox.exec();
        }
    }
    else
    {
        QMessageBox msgBox(QMessageBox::Information, "Remo", "A file must be selected");
        msgBox.exec();
    }
}

void ComparisonWindow::on_btnCancel_clicked()
{
    this->close();
}

void ComparisonWindow::on_exit_triggered()
{
    QCoreApplication::exit();
}

void ComparisonWindow::on_about_triggered()
{
    AboutDialog about(this);
    about.exec();
}