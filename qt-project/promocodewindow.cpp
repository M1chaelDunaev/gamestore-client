#include "promocodewindow.h"
#include "ui_promocodewindow.h"
#include <QClipboard>
#include <QApplication>

PromocodeWindow::PromocodeWindow(const QString& _promocode) :
    QDialog(nullptr),
    ui(new Ui::PromocodeWindow)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);
    ui->Close_button->setIcon(QPixmap("ApplicationIcons/CloseCross.png"));
    ui->lineEdit->setReadOnly(true);
    ui->lineEdit->setText(_promocode);
}

PromocodeWindow::~PromocodeWindow()
{
    delete ui;
}

void PromocodeWindow::on_Copy_clicked()
{
    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(ui->lineEdit->text());

    ui->info->setText("Promocode has been copied to the clipboard");
}

void PromocodeWindow::on_Close_button_clicked()
{
    close();
}

