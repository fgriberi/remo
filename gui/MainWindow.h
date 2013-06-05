#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QString>
#include <QDir>
#include <QtGui/QAction>
#include <QtGui/QFrame>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QComboBox>
#include <QtGui/QCheckBox>
#include <QtGui/QGroupBox>
#include <QtGui/QRadioButton>
#include "AnalysisWindow.h"
#include "ComparisonWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

private slots:
    void on_btnCancel_clicked();
    void on_btnAnalysis_clicked();
    void on_btnComparison_clicked();
    void on_exit_triggered();
    void on_about_triggered();

private:
    // setup window
    void setupUi(QMainWindow* MainWindow);
    void retranslateUi(QMainWindow* MainWindow);

    //options
    QPushButton* btnComparison;
    QPushButton* btnAnalysis;
    QPushButton* btnCancel;

    //others
    QAction* exit;
    QAction* about;
    QWidget* centralWidget;
    QFrame* frame;
    QMenuBar* menuBar;
    QMenu* menuFile;
    QMenu* menuHelp;

    AnalysisWindow* analysisWindow;
    ComparisonWindow* comparisonWindow;
};

#endif