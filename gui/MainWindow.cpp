#include <list>
#include <iostream>
#include "MainWindow.h"
#include "AboutDialog.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    this->setGeometry(500, 200, 339, 422);
    this->setFixedSize(280, 170);

    setupUi(this);
}

void MainWindow::setupUi(QMainWindow* MainWindow)
{
    if (MainWindow->objectName().isEmpty())
    {
        MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
    }
    /// create the objects
    centralWidget = new QWidget(MainWindow);
    centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
    frame = new QFrame(centralWidget);
    frame->setObjectName(QString::fromUtf8("frame"));
    frame->setGeometry(QRect(10, 10, 260, 150));
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Raised);

    btnComparison = new QPushButton(frame);
    btnComparison->setObjectName(QString::fromUtf8("btnComparison"));
    btnComparison->setGeometry(QRect(40, 60, 170, 27));

    btnAnalysis = new QPushButton(frame);
    btnAnalysis->setObjectName(QString::fromUtf8("btnAnalysis"));
    btnAnalysis->setGeometry(QRect(40, 20, 170, 27));

    btnCancel = new QPushButton(frame);
    btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
    btnCancel->setGeometry(QRect(80, 105, 98, 27));

    //menuBar and others
    exit = new QAction(MainWindow);
    exit->setObjectName(QString::fromUtf8("exit"));
    about = new QAction(MainWindow);
    about->setObjectName(QString::fromUtf8("about"));
    MainWindow->setCentralWidget(centralWidget);
    menuBar = new QMenuBar(MainWindow);
    menuBar->setObjectName(QString::fromUtf8("menuBar"));
    menuBar->setGeometry(QRect(0, 0, 510, 23));
    menuFile = new QMenu(menuBar);
    menuFile->setObjectName(QString::fromUtf8("menuFile"));
    menuHelp = new QMenu(menuBar);
    menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
    MainWindow->setMenuBar(menuBar);
    menuBar->addAction(menuFile->menuAction());
    menuBar->addAction(menuHelp->menuAction());
    menuFile->addAction(exit);
    menuHelp->addAction(about);
    retranslateUi(this);
    QMetaObject::connectSlotsByName(MainWindow);
} // setupUi

void MainWindow::retranslateUi(QMainWindow* MainWindow)
{
    MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Remo Project", 0, QApplication::UnicodeUTF8));
    exit->setText(QApplication::translate("MainWindow", "Exit", 0, QApplication::UnicodeUTF8));
    about->setText(QApplication::translate("MainWindow", "About", 0, QApplication::UnicodeUTF8));
    btnCancel->setText(QApplication::translate("MainWindow", "Cancel", 0, QApplication::UnicodeUTF8));
    btnAnalysis->setText(QApplication::translate("MainWindow", "Analyze sequences", 0, QApplication::UnicodeUTF8));
    btnComparison->setText(QApplication::translate("MainWindow", "Comparision Structure", 0, QApplication::UnicodeUTF8));
    menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
    menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
}  //retranslateUi

void MainWindow::on_btnAnalysis_clicked()
{
    analysisWindow = new AnalysisWindow(this);
    analysisWindow->show();
}

void MainWindow::on_btnComparison_clicked()
{
    comparisonWindow = new ComparisonWindow(this);
    comparisonWindow->show();
}

void MainWindow::on_btnCancel_clicked()
{
    QCoreApplication::exit();
}

void MainWindow::on_exit_triggered()
{
    QCoreApplication::exit();
}

void MainWindow::on_about_triggered()
{
    AboutDialog about(this);
    about.exec();
}

MainWindow::~MainWindow()
{
    delete analysisWindow;
    delete comparisonWindow;
}