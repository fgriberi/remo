#include <etilico/etilico.h>
#include "AboutDialog.h"

AboutDialog::AboutDialog(QWidget* parent) : QDialog(parent)
{
    this->setBaseSize(350, 235);
    this->setFixedSize(this->baseSize());

    this->setWindowTitle("About Us");

    this->remoLabel = new QLabel(this);
    this->remoLabel->setGeometry(139, 7, 100, 15);
    this->remoLabel->setText("<a href='http://code.google.com/p/r-emo/' style='text-decoration:none;'>Remo V1.0</>");
    this->remoLabel->setOpenExternalLinks(true);

    this->logoLabel = new QLabel(this);
    this->logoLabel->setGeometry(60, 13, 220, 150);
    std::string currentPath;
    etilico::getCurrentPath(currentPath);
    currentPath += "/projects/remo/gui/img/logo-fudepan.png";
    QPixmap* image = new QPixmap(currentPath.c_str());
    this->logoLabel->setPixmap(*image);
    this->logoLabel->show();
    this->logoLabel->setToolTip(tr("Fundacion para el desarrollo de la Programacion en acidos Nucleicos"));

    this->contributorsLabel = new QLabel(this);
    this->contributorsLabel->setGeometry(105, 120, 150, 100);
    this->contributorsLabel->setText("<P align='center'>Franco Riberi<BR>Daniel Gutson</P>");

    this->okButton = new QPushButton(this);
    this->okButton->setGeometry(160, 205, 40, 20);
    this->okButton->setText("OK");

    connect(this->okButton, SIGNAL(clicked()), this, SLOT(okButtonAction()));
}

AboutDialog::~AboutDialog()
{
    delete this->logoLabel;
    delete this->contributorsLabel;
    delete this->remoLabel;
    delete this->okButton;
}

void AboutDialog::okButtonAction()
{
    this->close();
}
