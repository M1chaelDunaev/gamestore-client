#include "storeitem.h"
#include "ui_storeitem.h"

#include <thread>
#include <QFontMetrics>
#include "mainwindow.h"
#include "useraccount.h"
#include "functions.h"
#include <QString>

StoreItem::StoreItem(MainWindow* _mainWindow, UserAccount* _currentAccount) :
    QWidget(nullptr), ui(new Ui::StoreItem), mainWindow(_mainWindow), currentAccount(_currentAccount)
{
    ui->setupUi(this);
}

StoreItem::~StoreItem()
{
    delete ui;
    delete screen_1;
    delete screen_2;
    delete screen_3;
    delete screen_4;
    delete screen_5;
}

void StoreItem::loadScreens(const QString &_scr1, const QString &_scr2, const QString &_scr3, const QString &_scr4, const QString &_scr5)
{
    screen_1 = new QImage(_scr1);
    screen_2 = new QImage(_scr2);
    screen_3 = new QImage(_scr3);
    screen_4 = new QImage(_scr4);
    screen_5 = new QImage(_scr5);
}

void StoreItem::setScreens()
{
    QSize buttonSize = ui->Screen1_pushButton->size();

    ui->Screen1_pushButton->setIcon( QPixmap::fromImage( screen_1->scaled(buttonSize) ) );
    ui->Screen2_pushButton->setIcon( QPixmap::fromImage( screen_2->scaled(buttonSize) ) );
    ui->Screen3_pushButton->setIcon( QPixmap::fromImage( screen_3->scaled(buttonSize) ) );
    ui->Screen4_pushButton->setIcon( QPixmap::fromImage( screen_4->scaled(buttonSize) ) );
    ui->Screen5_pushButton->setIcon( QPixmap::fromImage( screen_5->scaled(buttonSize) ) );

    ui->Screen1_arrow->setPixmap(QPixmap("ApplicationIcons/Arrow.png"));
    ui->Screen2_arrow->setPixmap(QPixmap("ApplicationIcons/Arrow.png"));
    ui->Screen3_arrow->setPixmap(QPixmap("ApplicationIcons/Arrow.png"));
    ui->Screen4_arrow->setPixmap(QPixmap("ApplicationIcons/Arrow.png"));
    ui->Screen5_arrow->setPixmap(QPixmap("ApplicationIcons/Arrow.png"));

    setCurrentScreenshot(1);
}

void StoreItem::setCover(const QString &_cover)
{
    ui->Cover_label->setPixmap(QPixmap(_cover));
}

void StoreItem::setCurrentScreenshot(int _number)
{
    QSize displaySize = ui->ScreenDisplay_label->size();

    if(_number == 1)
    {
        ui->ScreenDisplay_label->setPixmap( QPixmap::fromImage( screen_1->scaled(displaySize) ) );
        ui->Screen1_holder->setStyleSheet("background-color: rgb(208, 208, 208);");
        ui->Screen1_arrow->show();
    }
    else
    {
        ui->Screen1_holder->setStyleSheet("background-color: none;");
        ui->Screen1_arrow->hide();
    }

    if(_number == 2)
    {
        ui->ScreenDisplay_label->setPixmap( QPixmap::fromImage( screen_2->scaled(displaySize) ) );
        ui->Screen2_holder->setStyleSheet("background-color: rgb(208, 208, 208);");
        ui->Screen2_arrow->show();
    }
    else
    {
        ui->Screen2_holder->setStyleSheet("background-color: none;");
        ui->Screen2_arrow->hide();
    }

    if(_number == 3)
    {
        ui->ScreenDisplay_label->setPixmap( QPixmap::fromImage( screen_3->scaled(displaySize) ) );
        ui->Screen3_holder->setStyleSheet("background-color: rgb(208, 208, 208);");
        ui->Screen3_arrow->show();
    }
    else
    {
        ui->Screen3_holder->setStyleSheet("background-color: none;");
        ui->Screen3_arrow->hide();
    }

    if(_number == 4)
    {
        ui->ScreenDisplay_label->setPixmap( QPixmap::fromImage( screen_4->scaled(displaySize) ) );
        ui->Screen4_holder->setStyleSheet("background-color: rgb(208, 208, 208);");
        ui->Screen4_arrow->show();
    }
    else
    {
        ui->Screen4_holder->setStyleSheet("background-color: none;");
        ui->Screen4_arrow->hide();
    }

    if(_number == 5)
    {
        ui->ScreenDisplay_label->setPixmap( QPixmap::fromImage( screen_5->scaled(displaySize) ) );
        ui->Screen5_holder->setStyleSheet("background-color: rgb(208, 208, 208);");
        ui->Screen5_arrow->show();
    }
    else
    {
        ui->Screen5_holder->setStyleSheet("background-color: none;");
        ui->Screen5_arrow->hide();
    }
}

void StoreItem::setName(const QString &_name)
{
    ui->GameName_label->setText(_name);
    if(_name.size() > 25 )
    {
        QString temp = "";
        for(int i = 0; i < 25; ++i)
        {
            temp.push_back(_name[i]);
        }

        temp.push_back("...");
        this->shortName = temp;
    }
    else
    {
        this->shortName = _name;
    }

    ui->BuyGameName_label->setText("Buy " + shortName);
}

void StoreItem::setPrice(const QString &_price)
{
    ui->Price_label->setText(_price);
}

void StoreItem::setMainDescription(const QString &_description)
{
    ui->Descriptin_label->setText(transformByLength(_description, ui->Descriptin_label->size(), ui->Descriptin_label->font()));
}

void StoreItem::setSmallDescriptions(const QString &_first, const QString &_second, const QString &_third,
                                     const QString &_fourth, const QString &_fifth)
{
    QFontMetrics metric(ui->RR_pushButton->font());

    ui->RR_pushButton->resize(metric.size(Qt::TextSingleLine, _first));
    ui->RR_pushButton->setText(_first);

    ui->AR_pushButton->resize(metric.size(Qt::TextSingleLine, _second));
    ui->AR_pushButton->setText(_second);

    ui->RD_label->setText(_third);

    ui->DEV_pushButton->resize(metric.size(Qt::TextSingleLine, _fourth));
    ui->DEV_pushButton->setText(_fourth);

    ui->PUB_pushButton->resize(metric.size(Qt::TextSingleLine, _fifth));
    ui->PUB_pushButton->setText(_fifth);
}

void StoreItem::setLanguages(const QString &_lang)
{
    int index = 1;
    for (auto elem : _lang)
    {
        if(elem != '-')
        {
            if(index == 1)
            {
                if(elem == '1')
                    ui->L1->setPixmap(QPixmap("ApplicationIcons/Supported.png"));
            }
            if(index == 2)
            {
                if(elem == '1')
                    ui->L2->setPixmap(QPixmap("ApplicationIcons/Supported.png"));
            }
            if(index == 3)
            {
                if(elem == '1')
                    ui->L3->setPixmap(QPixmap("ApplicationIcons/Supported.png"));
            }
            if(index == 4)
            {
                if(elem == '1')
                    ui->L4->setPixmap(QPixmap("ApplicationIcons/Supported.png"));
            }
            if(index == 5)
            {
                if(elem == '1')
                    ui->L5->setPixmap(QPixmap("ApplicationIcons/Supported.png"));
            }
            if(index == 6)
            {
                if(elem == '1')
                    ui->L6->setPixmap(QPixmap("ApplicationIcons/Supported.png"));
            }
            if(index == 7)
            {
                if(elem == '1')
                    ui->L7->setPixmap(QPixmap("ApplicationIcons/Supported.png"));
            }
            if(index == 8)
            {
                if(elem == '1')
                    ui->L8->setPixmap(QPixmap("ApplicationIcons/Supported.png"));
            }
            if(index == 9)
            {
                if(elem == '1')
                    ui->L9->setPixmap(QPixmap("ApplicationIcons/Supported.png"));
            }
            if(index == 10)
            {
                if(elem == '1')
                    ui->L10->setPixmap(QPixmap("ApplicationIcons/Supported.png"));
            }
            if(index == 11)
            {
                if(elem == '1')
                    ui->L11->setPixmap(QPixmap("ApplicationIcons/Supported.png"));
            }
            if(index == 12)
            {
                if(elem == '1')
                    ui->L12->setPixmap(QPixmap("ApplicationIcons/Supported.png"));
            }
            if(index == 13)
            {
                if(elem == '1')
                    ui->L13->setPixmap(QPixmap("ApplicationIcons/Supported.png"));
            }
            if(index == 14)
            {
                if(elem == '1')
                    ui->L14->setPixmap(QPixmap("ApplicationIcons/Supported.png"));
            }
            if(index == 15)
            {
                if(elem == '1')
                    ui->L15->setPixmap(QPixmap("ApplicationIcons/Supported.png"));
            }

            ++index;
        }
        else
            continue;
    }
}

void StoreItem::setMinSR(const QString &_first, const QString &_second, const QString &_third, const QString &_fourth, const QString &_fifth)
{
    ui->minSR_proc->setText(_first);
    ui->minSR_mem->setText(_second);
    ui->minSR_graphic->setText(_third);
    ui->minSR_directx->setText(_fourth);
    ui->minSR_storage->setText(_fifth);
}

void StoreItem::setRecSR(const QString &_first, const QString &_second, const QString &_third, const QString &_fourth, const QString &_fifth)
{
    ui->recSR_proc->setText(_first);
    ui->recSR_mem->setText(_second);
    ui->recSR_graphic->setText(_third);
    ui->recSR_directx->setText(_fourth);
    ui->recSR_storage->setText(_fifth);
}

QString StoreItem::inCartButton_styleSheet()
{
    QString str = "";
    str += "color: rgb(255, 255, 255);";
    str += "background-color: qlineargradient(spread:pad, x1:0.516864, y1:0.722, x2:0.852, y2:1, stop: ";
    str += "0 rgba(160, 200, 24, 255), stop:1 rgba(188, 238, 13, 255));";
    str += "border: 0px;";

    return str;
}

QString StoreItem::baseButton_styleSheet()
{
    QString str = "";
    str += "QPushButton {";
    str += inCartButton_styleSheet() + " }";
    str += "QPushButton::hover {";
    str += "background-color: rgb(200, 255, 63); color: rgb(70, 70, 70); }";

    return str;
}

void StoreItem::updateWidget()
{
    setStatus();
    ui->Uninstall->hide();

    int count = currentAccount->cart.countOfItems();
    ui->Cart_pushButton->setText("CART(" + QString::number(count) + ")");

    ui->Price_label->hide();
    ui->panel->setStyleSheet("background-color: rgba(0, 0, 0, 0);");
    ui->addToCart_Play_Install->setStyleSheet(baseButton_styleSheet());

    if(bought)
    {
        if(installed)
        {
            ui->Uninstall->show();
            ui->addToCart_Play_Install->setText("Play");
            ui->BuyGameName_label->setText("Play " + shortName);
        }
        else
        {
            ui->addToCart_Play_Install->setText("Install");
            ui->BuyGameName_label->setText("Install " + shortName);
        }
    }
    else
    {
        if(!inCart)
        {
            ui->Price_label->show();
            ui->addToCart_Play_Install->setText("Add to cart");
            ui->panel->setStyleSheet("background-color: rgba(0, 0, 0, 255);");
            ui->BuyGameName_label->setText("Buy " + shortName);
        }
        else
        {
            ui->addToCart_Play_Install->setStyleSheet(inCartButton_styleSheet());
            ui->addToCart_Play_Install->setText("Item in cart");
        }
    }
}

void StoreItem::on_addToCart_Play_Install_clicked()
{
    if(bought)
    {
        if(installed)
        {
            pressPlay();
        }
        else
        {
            pressInstall();
            mainWindow->setCurrentMenu(nullptr);
        }

        return;
    }

    if(!inCart)
    {
        pressAddToCart();
        updateWidget();
    }
}

void StoreItem::on_Screen1_pushButton_clicked()
{
    setCurrentScreenshot(1);
}

void StoreItem::on_Screen2_pushButton_clicked()
{
    setCurrentScreenshot(2);
}

void StoreItem::on_Screen3_pushButton_clicked()
{
    setCurrentScreenshot(3);
}

void StoreItem::on_Screen4_pushButton_clicked()
{
    setCurrentScreenshot(4);
}

void StoreItem::on_Screen5_pushButton_clicked()
{
    setCurrentScreenshot(5);
}

void StoreItem::showEvent(QShowEvent *event)
{
    updateWidget();
}

void StoreItem::on_Cart_pushButton_clicked()
{
    mainWindow->showCart();
}

void StoreItem::on_Uninstall_clicked()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1050));
    pressUninstall();
    mainWindow->updateUserLibrary();
}


void StoreItem::on_RR_pushButton_clicked()
{
    mainWindow->showCommunity();
    mainWindow->setCurrentMenu(nullptr);
}


void StoreItem::on_AR_pushButton_clicked()
{
    mainWindow->showCommunity();
    mainWindow->setCurrentMenu(nullptr);
}


void StoreItem::on_DEV_pushButton_clicked()
{
    mainWindow->showCommunity();
    mainWindow->setCurrentMenu(nullptr);
}


void StoreItem::on_PUB_pushButton_clicked()
{
    mainWindow->showCommunity();
    mainWindow->setCurrentMenu(nullptr);
}

