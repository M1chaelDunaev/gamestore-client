#include "informationalwindow.h"
#include "ui_informationalwindow.h"

InformationalWindow::InformationalWindow(const QString& _tittle, const QString& _text) :
    QDialog(nullptr), ui(new Ui::InformationalWindow)
{
    setWindowFlag(Qt::FramelessWindowHint);
    ui->setupUi(this);
    ui->Close_button->setIcon(QPixmap("ApplicationIcons/CloseCross.png"));

    ui->Tittle->setText(_tittle);
    ui->Text->setText(_text);

}

InformationalWindow::~InformationalWindow()
{
    delete ui;
}

void InformationalWindow::on_Close_button_clicked()
{
    close();
}

