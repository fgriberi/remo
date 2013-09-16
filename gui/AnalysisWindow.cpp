#include <list>
#include <iostream>
#include "AboutDialog.h"
#include "Service.h"
#include "AnalysisWindow.h"

AnalysisWindow::AnalysisWindow(QWidget* parent) : QMainWindow(parent)
{
    this->setGeometry(500, 200, 339, 422);
    this->setFixedSize(420, 497); 

    setupUi(this);
    connect(this->checkBoxIsCircYes, SIGNAL(stateChanged(int)), this, SLOT(checkBoxYesCirc(int)));
    connect(this->checkBoxIsCircNo, SIGNAL(stateChanged(int)), this, SLOT(checkBoxNoCirc(int)));
    connect(this->comboBoxMethod, SIGNAL(activated(int)), this, SLOT(comboBoxHumanizerActivated()));
    connect(this->comboBoxMethod, SIGNAL(activated(int)), this, SLOT(comboBoxBackendActivated()));
    connect(this->comboBoxMethod, SIGNAL(activated(int)), this, SLOT(checkPrefoldAndDontFoldActivate()));
    connect(this->comboBoxHumanizer, SIGNAL(activated(int)), this, SLOT(comboBoxBackendActivated()));
    connect(this->comboBoxBackend, SIGNAL(activated(int)), this, SLOT(btnAcceptActivated()));   
    this->setWindowModality(Qt::ApplicationModal);
}

void AnalysisWindow::setupUi(QMainWindow* AnalysisWindow)
{
    if (AnalysisWindow->objectName().isEmpty())
    {
        AnalysisWindow->setObjectName(QString::fromUtf8("AnalysisWindow"));
    }
    /// create the objects
    centralWidget = new QWidget(AnalysisWindow);
    centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
    frame = new QFrame(centralWidget);
    frame->setObjectName(QString::fromUtf8("frame"));
    frame->setGeometry(QRect(10, 10, 390, 475));
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Raised);

    // labels
    labelRNAm = new QLabel(frame);
    labelRNAm->setObjectName(QString::fromUtf8("labelRNAm"));
    labelRNAm->setGeometry(QRect(20, 12, 81, 21));

    labelIsCirc = new QLabel(frame);
    labelIsCirc->setObjectName(QString::fromUtf8("labelIsCirc"));
    labelIsCirc->setGeometry(QRect(7, 50, 85, 21));

    labelmiRNA = new QLabel(frame);
    labelmiRNA->setObjectName(QString::fromUtf8("labelmiRNA"));
    labelmiRNA->setGeometry(QRect(18, 93, 81, 17));

    labelOrganism = new QLabel(frame);
    labelOrganism->setObjectName(QString::fromUtf8("nameFilemiRNA"));
    labelOrganism->setGeometry(QRect(22, 130, 165, 27));

    labelMethod = new QLabel(frame);
    labelMethod->setObjectName(QString::fromUtf8("labelMethod"));
    labelMethod->setGeometry(QRect(20, 246, 72, 17));

    labelHumanizer = new QLabel(frame);
    labelHumanizer->setObjectName(QString::fromUtf8("labelHumanizer"));
    labelHumanizer->setGeometry(QRect(17, 282, 74, 17));

    labelBackend = new QLabel(frame);
    labelBackend->setObjectName(QString::fromUtf8("labelBackend"));
    labelBackend->setGeometry(QRect(30, 324, 71, 17));

    labelPrefold = new QLabel(frame);
    labelPrefold->setObjectName(QString::fromUtf8("labelPrefold"));
    labelPrefold->setGeometry(QRect(33, 365, 85, 21));

    labelDontFold = new QLabel(frame);
    labelDontFold->setObjectName(QString::fromUtf8("labelDontFold"));
    labelDontFold->setGeometry(QRect(28, 390, 85, 21));

    //lineEdit
    nameFileRNAm = new QLineEdit(frame);
    nameFileRNAm->setObjectName(QString::fromUtf8("nameFileRNAm"));
    nameFileRNAm->setGeometry(QRect(105, 10, 230, 27));

    nameFilemiRNA = new QLineEdit(frame);
    nameFilemiRNA->setObjectName(QString::fromUtf8("nameFilemiRNA"));
    nameFilemiRNA->setGeometry(QRect(105, 90, 230, 27));
    nameFilemiRNA->setEnabled(false);

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
    checkBoxPrefold->setGeometry(QRect(100, 365, 161, 27));
    checkBoxPrefold->setText("");
    checkBoxPrefold->setEnabled(false);
    
    checkBoxDontFold = new QCheckBox(frame);
    checkBoxDontFold->setGeometry(QRect(100, 390, 161, 27));
    checkBoxDontFold->setText("");
    checkBoxDontFold->setEnabled(false);

    //radioButton
    radio1 = new QRadioButton(frame);
    radio1->setObjectName(QString::fromUtf8("radio1"));
    radio1->setGeometry(QRect(100, 130, 130, 27));
    radio1->setEnabled(false);

    radio2 = new QRadioButton(frame);
    radio2->setObjectName(QString::fromUtf8("radio2"));
    radio2->setGeometry(QRect(100, 160, 130, 27));
    radio2->setEnabled(false);

    radio3 = new QRadioButton(frame);
    radio3->setObjectName(QString::fromUtf8("radio3"));
    radio3->setGeometry(QRect(100, 190, 130, 27));
    radio3->setEnabled(false);

    radio4 = new QRadioButton(frame);
    radio4->setObjectName(QString::fromUtf8("radio4"));
    radio4->setGeometry(QRect(230, 130, 130, 27));
    radio4->setEnabled(false);

    radio5 = new QRadioButton(frame);
    radio5->setObjectName(QString::fromUtf8("radio5"));
    radio5->setGeometry(QRect(230, 160, 130, 27));
    radio5->setEnabled(false);

    radio6 = new QRadioButton(frame);
    radio6->setObjectName(QString::fromUtf8("radio6"));
    radio6->setGeometry(QRect(230, 190, 130, 27));
    radio6->setEnabled(false);

    //comboBox
    comboBoxMethod = new QComboBox(frame);
    comboBoxMethod->setObjectName(QString::fromUtf8("comboBoxMethod"));
    comboBoxMethod->setGeometry(QRect(100, 240, 270, 27));
    comboBoxMethod->setEnabled(false);
    fillcomboBoxMethod();

    comboBoxHumanizer = new QComboBox(frame);
    comboBoxHumanizer->setObjectName(QString::fromUtf8("comboBoxHumanizer"));
    comboBoxHumanizer->setGeometry(QRect(100, 280, 270, 27));
    fillComboBoxHumanizer();
    comboBoxHumanizer->setEnabled(false);

    comboBoxBackend = new QComboBox(frame);
    comboBoxBackend->setObjectName(QString::fromUtf8("comboBoxBackend"));
    comboBoxBackend->setGeometry(QRect(100, 320, 270, 27));
    fillComboBoxBackendFolding();
    comboBoxBackend->setEnabled(false);

    //buttons
    btnExplore = new QPushButton(frame);
    btnExplore->setObjectName(QString::fromUtf8("btnExplore"));
    btnExplore->setGeometry(QRect(336, 10, 31, 25));

    btnExplore2 = new QPushButton(frame);
    btnExplore2->setObjectName(QString::fromUtf8("btnExplore2"));
    btnExplore2->setGeometry(QRect(336, 90, 31, 25));
    btnExplore2->setEnabled(false);

    btnCancel = new QPushButton(frame);
    btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
    btnCancel->setGeometry(QRect(170, 430, 98, 27));

    btnAccept = new QPushButton(frame);
    btnAccept->setObjectName(QString::fromUtf8("btnAccept"));
    btnAccept->setGeometry(QRect(270, 430, 98, 27));
    btnAccept->setEnabled(false);

    //menuBar and others
    exit = new QAction(AnalysisWindow);
    exit->setObjectName(QString::fromUtf8("exit"));
    about = new QAction(AnalysisWindow);
    about->setObjectName(QString::fromUtf8("about"));
    AnalysisWindow->setCentralWidget(centralWidget);
    menuBar = new QMenuBar(AnalysisWindow);
    menuBar->setObjectName(QString::fromUtf8("menuBar"));
    menuBar->setGeometry(QRect(0, 0, 510, 23));
    menuFile = new QMenu(menuBar);
    menuFile->setObjectName(QString::fromUtf8("menuFile"));
    menuHelp = new QMenu(menuBar);
    menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
    AnalysisWindow->setMenuBar(menuBar);
    menuBar->addAction(menuFile->menuAction());
    menuBar->addAction(menuHelp->menuAction());
    menuFile->addAction(exit);
    menuHelp->addAction(about);
    retranslateUi(this);
    QMetaObject::connectSlotsByName(AnalysisWindow);
} // setupUi

void AnalysisWindow::retranslateUi(QMainWindow* AnalysisWindow)
{
    AnalysisWindow->setWindowTitle(QApplication::translate("AnalysisWindow", "Remo Project", 0, QApplication::UnicodeUTF8));
    exit->setText(QApplication::translate("AnalysisWindow", "Exit", 0, QApplication::UnicodeUTF8));
    about->setText(QApplication::translate("AnalysisWindow", "About", 0, QApplication::UnicodeUTF8));
    labelRNAm->setText(QApplication::translate("AnalysisWindow", "File RNAm:", 0, QApplication::UnicodeUTF8));
    labelIsCirc->setText(QApplication::translate("AnalysisWindow", "IsCirc RNAm:  fdfd", 0, QApplication::UnicodeUTF8));
    labelPrefold->setText(QApplication::translate("AnalysisWindow", "Prefold: ", 0, QApplication::UnicodeUTF8));
    labelDontFold->setText(QApplication::translate("AnalysisWindow", "Dont Fold: ", 0, QApplication::UnicodeUTF8));
    labelOrganism->setText(QApplication::translate("AnalysisWindow", "Organism:", 0, QApplication::UnicodeUTF8));
    radio1->setText(QApplication::translate("AnalysisWindow", "SCerevisiae", 0, QApplication::UnicodeUTF8));
    radio2->setText(QApplication::translate("AnalysisWindow", "EColi", 0, QApplication::UnicodeUTF8));
    radio3->setText(QApplication::translate("AnalysisWindow", "HSapiens", 0, QApplication::UnicodeUTF8));
    radio4->setText(QApplication::translate("AnalysisWindow", "CElegans", 0, QApplication::UnicodeUTF8));
    radio5->setText(QApplication::translate("AnalysisWindow", "DMelanogaster", 0, QApplication::UnicodeUTF8));
    radio6->setText(QApplication::translate("AnalysisWindow", "BSubtilis", 0, QApplication::UnicodeUTF8));
    labelmiRNA->setText(QApplication::translate("AnalysisWindow", "File miRNA:", 0, QApplication::UnicodeUTF8));
    labelMethod->setText(QApplication::translate("AnalysisWindow", "     Method:", 0, QApplication::UnicodeUTF8));
    labelHumanizer->setText(QApplication::translate("AnalysisWindow", "Humanizer:", 0, QApplication::UnicodeUTF8));
    labelBackend->setText(QApplication::translate("AnalysisWindow", "Backend:", 0, QApplication::UnicodeUTF8));
    btnExplore->setText(QApplication::translate("AnalysisWindow", "...", 0, QApplication::UnicodeUTF8));
    btnExplore2->setText(QApplication::translate("AnalysisWindow", "...", 0, QApplication::UnicodeUTF8));
    btnAccept->setText(QApplication::translate("AnalysisWindow", "Accept", 0, QApplication::UnicodeUTF8));
    btnCancel->setText(QApplication::translate("AnalysisWindow", "Cancel", 0, QApplication::UnicodeUTF8));
    menuFile->setTitle(QApplication::translate("AnalysisWindow", "File", 0, QApplication::UnicodeUTF8));
    menuHelp->setTitle(QApplication::translate("AnalysisWindow", "Help", 0, QApplication::UnicodeUTF8));
}  //retranslateUi

static const std::string CHOOSE_OPTION = "Choose option";
static const std::string AD_HOC = "Ad hoc";
static const std::string FORMAL = "Formal";

void AnalysisWindow::fillcomboBoxMethod()
{
    QList<QString> options;
    options.append(CHOOSE_OPTION.c_str());
    options.append(AD_HOC.c_str());   //with folding
    options.append(FORMAL.c_str());   //with hybridize
    comboBoxMethod->addItems(options);
}

void AnalysisWindow::fillComboBoxHumanizer()
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

void AnalysisWindow::fillComboBoxBackendFolding()
{
    std::list<std::string> foldBackend;
    Service::getFoldingBackend(foldBackend);
    QList<QString> foldingBackend;
    foldingBackend.append(CHOOSE_OPTION.c_str());
    std::list<std::string>::iterator it;
    for (it = foldBackend.begin(); it != foldBackend.end(); it++)
    {
        foldingBackend.append((*it).c_str());
    }
    comboBoxBackend ->addItems(foldingBackend);
}

void AnalysisWindow::fillComboBoxBackendHybridize()
{
    std::list<std::string> hyBackend;
    Service::getHybridizeBackend(hyBackend);
    QList<QString> hybridizeBackend;
    hybridizeBackend.append(CHOOSE_OPTION.c_str());
    std::list<std::string>::iterator it;
    for (it = hyBackend.begin(); it != hyBackend.end(); it++)
    {
        hybridizeBackend.append((*it).c_str());
    }
    comboBoxBackend->addItems(hybridizeBackend);
}

void AnalysisWindow::on_btnExplore_clicked()
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

void AnalysisWindow::on_btnExplore2_clicked()
{
    QString file_selected = QFileDialog::getOpenFileName(this, tr("Select File"), QDir::currentPath(), tr("All files (*.*)"));

    if (!file_selected.isNull() && !file_selected.isEmpty())
    {
        nameFilemiRNA->setText(file_selected);
        radioButtonActivated();
        comboBoxMethodActivated();
    }
    else
    {
        QMessageBox msgBox(QMessageBox::Information, "Remo", "A file must be selected");
        msgBox.exec();
    }
}

void AnalysisWindow::checkBoxYesCirc(int state)
{
    if (state == Qt::Checked)
    {
        checkBoxIsCircNo->setCheckState(Qt::Unchecked);
    }
    nameFilemiRNAActivated();
}

void AnalysisWindow::checkBoxNoCirc(int state)
{
    if (state == Qt::Checked)
    {
        checkBoxIsCircYes->setCheckState(Qt::Unchecked);
    }
    nameFilemiRNAActivated();
}

void AnalysisWindow::radioButtonActivated()
{
    radio1->setEnabled(true);
    radio2->setEnabled(true);
    radio3->setEnabled(true);
    radio3->setChecked(true);
    radio4->setEnabled(true);
    radio5->setEnabled(true);
    radio6->setEnabled(true);
}

void AnalysisWindow::nameFilemiRNAActivated()
{
    nameFilemiRNA->setEnabled(true);
    btnExplore2->setEnabled(true);
}

void AnalysisWindow::checkBoxIsCircActivated()
{
    checkBoxIsCircYes->setEnabled(true);
    checkBoxIsCircYes->setChecked(true);
    checkBoxIsCircNo->setEnabled(true);
}

void AnalysisWindow::btnExplore2Activated()
{
    nameFilemiRNA->setEnabled(true);
    btnExplore2->setEnabled(true);
}

void AnalysisWindow::comboBoxMethodActivated()
{
    comboBoxMethod->setEnabled(true);
}

void AnalysisWindow::comboBoxHumanizerActivated()
{
    comboBoxHumanizer->setEnabled(true);
}

void AnalysisWindow::comboBoxBackendActivated()
{
    QString method1(AD_HOC.c_str());
    QString method2(FORMAL.c_str());
    QString temp;
    if (comboBoxMethod->currentText() == method2)
    {
        comboBoxBackend->clear();
        fillComboBoxBackendHybridize();
    }
    else
    {
        if (comboBoxMethod->currentText() == method1)
        {
            comboBoxBackend->clear();
            fillComboBoxBackendFolding();
        }
    }
    comboBoxBackend->setEnabled(true);
}

void AnalysisWindow::checkPrefoldAndDontFoldActivate()
{
    checkBoxPrefold->setEnabled(true);
    checkBoxDontFold->setEnabled(true);
}

void AnalysisWindow::btnAcceptActivated()
{
    btnAccept->setEnabled(true);
}

bool AnalysisWindow::includeFlag(QCheckBox* checkBox)
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

void AnalysisWindow::on_btnAccept_clicked()
{
    // check that all correct fields
    if (!nameFileRNAm->text().isNull() && !nameFilemiRNA->text().isNull()
            && !nameFileRNAm->text().isEmpty() && !nameFilemiRNA->text().isEmpty())
    {
        const std::string method = comboBoxMethod->currentText().toStdString();
        const std::string humanizer = comboBoxHumanizer->currentText().toStdString();
        const std::string backend   = comboBoxBackend->currentText().toStdString();
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
        if ((method != CHOOSE_OPTION) && (humanizer != CHOOSE_OPTION) && (backend != CHOOSE_OPTION))
        {            
            const std::string fileRNAm  = nameFileRNAm->text().toStdString();
            const std::string filemiRNA = nameFilemiRNA->text().toStdString();

            std::string command;
            Service::generateArgumentToAnalysis(fileRNAm, filemiRNA, method, humanizer, backend, isCirc, org, command, prefold, dontFold);
            std::cout << "Execute: " << command << std::endl;
            Service::startRemo(command);            
            QMessageBox msgBox(QMessageBox::Information, "Remo", "File generation completed");
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

void AnalysisWindow::on_btnCancel_clicked()
{
    this->close();
}

void AnalysisWindow::on_exit_triggered()
{
    QCoreApplication::exit();
}

void AnalysisWindow::on_about_triggered()
{
    AboutDialog about(this);
    about.exec();
}