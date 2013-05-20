#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCoreApplication>
#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QString>
#include <QDir>

//#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QFrame>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>
#include <QtGui/QComboBox>
#include <QtGui/QCheckBox>
#include <QtGui/QGroupBox>
#include <QtGui/QRadioButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow() {};

private slots:
    void on_btnExplore_clicked();
    void on_btnExplore2_clicked();
    void on_btnAccept_clicked();
    void on_btnCancel_clicked();

    void on_exit_triggered();
    void on_about_triggered();

    void checkBoxIsCirc_Activated();
    void checkBoxYesCirc(int state);
    void checkBoxNoCirc(int state);
    void btnExplore2_Activated();
    void radioButton_Activated();
    void nameFilemiRNA_Activated();
    void comboBoxMethod_Activated();
    void comboBoxHumanizer_Activated();
    void comboBoxBackend_Activated();
    void btnAccept_Activated();

private:
    // setup window
    void setupUi(QMainWindow* MainWindow);
    void retranslateUi(QMainWindow* MainWindow);

    // fill comboBox
    void fillcomboBoxMethod();
    void fillComboBoxHumanizer();
    void fillComboBoxBackendFolding();
    void fillComboBoxBackendHybridize();

    //labels declaration
    QLabel* labelRNAm;
    QLabel* labelmiRNA;
    QLabel* labelIsCirc;
    QLabel* labelOrganism;
    QLabel* labelMethod;
    QLabel* labelHumanizer;
    QLabel* labelBackend;

    //lineEdits declaration
    QLineEdit* nameFileRNAm;
    QLineEdit* nameFilemiRNA;

    //comboBox declaration
    QComboBox* comboBoxMethod;
    QComboBox* comboBoxHumanizer;
    QComboBox* comboBoxBackend;

    //checkBox declaration
    QCheckBox* checkBoxIsCircYes;
    QCheckBox* checkBoxIsCircNo;

    //declaration radioButton
    QRadioButton* radio1;
    QRadioButton* radio2;
    QRadioButton* radio3;
    QRadioButton* radio4;
    QRadioButton* radio5;
    QRadioButton* radio6;

    //buttons declaration
    QPushButton* btnExplore;
    QPushButton* btnExplore2;
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

#endif