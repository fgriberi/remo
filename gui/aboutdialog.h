#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    AboutDialog(QWidget* parent = NULL);
    ~AboutDialog();

private:
    QLabel* logoLabel;
    QLabel* remoLabel;
    QLabel* contributorsLabel;
    QPushButton* okButton;

private slots:
    void okButtonAction();
};

#endif // ABOUTDIALOG_H
