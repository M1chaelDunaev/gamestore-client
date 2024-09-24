#include "playwindow.h"
#include "ui_playwindow.h"

PlayWindow::PlayWindow(const QString& _gameName, const QString& _iconPath) :
    QDialog(nullptr), ui(new Ui::PlayWindow)
{
    ui->setupUi(this);

    setCursor(Qt::WaitCursor);
    setWindowTitle(_gameName);
    setWindowIcon(QPixmap(_iconPath));
    showMaximized();
    setWindowFlag(Qt::Widget);
}

PlayWindow::~PlayWindow()
{
    delete ui;
}
