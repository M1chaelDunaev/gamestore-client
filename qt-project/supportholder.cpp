#include "supportholder.h"
#include "ui_supportholder.h"
#include "mainapplication.h"
#include "support.h"
#include <QVBoxLayout>
#include <QMouseEvent>

SupportHolder::SupportHolder(MainApplication* _mainApp) :
    QWidget(nullptr), ui(new Ui::SupportHolder), mainApp(_mainApp)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);
    setWindowIcon(QPixmap("ApplicationIcons/Logotype.png"));
    setWindowTitle("Support");
    screenInfo = QApplication::primaryScreen();

    ui->Close_pushButton->setIcon(QPixmap("ApplicationIcons/CloseCross.png"));
    ui->Minimized_pushButton->setIcon(QPixmap("ApplicationIcons/ShowMinimized.png"));
    ui->MaximizedNormal_pushButton->setIcon(QPixmap("ApplicationIcons/ShowNormal.png"));

    support = new Support(mainApp);
    mainLayout = new QVBoxLayout();
    mainLayout->addWidget(support);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    ui->Main->setLayout(mainLayout);
}

SupportHolder::~SupportHolder()
{
    delete ui;
    delete support;
    delete mainLayout;
}

void SupportHolder::on_Close_pushButton_clicked()
{
    hide();
    mainApp->showLoginWindow();
}

void SupportHolder::on_MaximizedNormal_pushButton_clicked()
{
    if(isMaximized())
    {
        showNormal();
        ui->MaximizedNormal_pushButton->setIcon(QPixmap("ApplicationIcons/ShowMaximized.png"));
    }
    else
    {
        showMaximized();
        ui->MaximizedNormal_pushButton->setIcon(QPixmap("ApplicationIcons/ShowNormal.png"));
    }
}


void SupportHolder::on_Minimized_pushButton_clicked()
{
    showMinimized();
}

void SupportHolder::mousePressEvent(QMouseEvent *event)
{
    lastPressedMouseButton = event->button();

    if(lastPressedMouseButton == Qt::LeftButton)
    {
        prevMousePos = event->globalPosition();
    }

    QWidget::mousePressEvent(event);
}

void SupportHolder::mouseMoveEvent(QMouseEvent *event)
{
    if(lastPressedMouseButton != Qt::LeftButton)
        return;

    QPointF delta = event->globalPosition() - prevMousePos;


    if(event->globalPosition().x() <= 0 || event->globalPosition().y() <= 0)
        return;

    if(event->globalPosition().y() >= screenInfo->size().height() - 40 ||
        event->globalPosition().x() >= screenInfo->size().width())
        return;

    move(this->pos() + delta.toPoint());
    prevMousePos = event->globalPosition();

    QWidget::mousePressEvent(event);
}

