#include "downloader.h"
#include "ui_downloader.h"
#include "useraccount.h"
#include "functions.h"
#include "mainwindow.h"
#include <thread>
#include <chrono>
#include <random>
#include <QImage>
#include <QMessageBox>

Downloader::Downloader(MainWindow *_mainWindow, UserAccount *_currentAccount) :
    QWidget(nullptr), ui(new Ui::Downloader),
    mainWindow(_mainWindow), currentAccount(_currentAccount)
{
    ui->setupUi(this);
    setIcons();

    for(int i = 0; i < 9; ++i)
    {
        active[i] = false;
        paused[i] = false;
        downloaded[i] = 0;
    }

    connect(this, SIGNAL(completeSignal(Games)), this, SLOT(completeSlot(Games)));
    connect(this, SIGNAL(setValuesSignal(Games,int,int,int)), this, SLOT(setValuesSlot(Games,int,int,int)));

    update();
}


Downloader::~Downloader()
{
    delete ui;
}

void Downloader::update()
{
    if(active[(int)Games::ELDEN_RING])
    {
        ui->ER_widget->show();
    }
    else
    {
        ui->ER_widget->hide();
    }

    if(active[(int)Games::GOD_OF_WAR])
    {
        ui->GOW_widget->show();
    }
    else
    {
        ui->GOW_widget->hide();
    }

    if(active[(int)Games::STRAY])
    {
        ui->Str_widget->show();
    }
    else
    {
        ui->Str_widget->hide();
    }

    if(active[(int)Games::HORIZON])
    {
        ui->HFW_widget->show();
    }
    else
    {
        ui->HFW_widget->hide();
    }

    if(active[(int)Games::PLAGUE_TALE])
    {
        ui->PT_widget->show();
    }
    else
    {
        ui->PT_widget->hide();
    }

    if(active[(int)Games::LAST_OF_US])
    {
        ui->LOU_widget->show();
    }
    else
    {
        ui->LOU_widget->hide();
    }

    if(active[(int)Games::CUPHEAD])
    {
        ui->Cup_widget->show();
    }
    else
    {
        ui->Cup_widget->hide();
    }

    if(active[(int)Games::DYING_LIGHT])
    {
        ui->DL_widget->show();
    }
    else
    {
        ui->DL_widget->hide();
    }

    if(active[(int)Games::WARHAMMER])
    {
        ui->War_widget->show();
    }
    else
    {
        ui->War_widget->hide();
    }
}

int Downloader::getGameSize(Games _game)
{
    if(_game == Games::ELDEN_RING)
    {
        return calc(ui->ER_size->text());
    }

    if(_game == Games::GOD_OF_WAR)
    {
        return calc(ui->GOW_size->text());
    }

    if(_game == Games::STRAY)
    {
        return calc(ui->Str_size->text());
    }

    if(_game == Games::HORIZON)
    {
        return calc(ui->HFW_size->text());
    }

    if(_game == Games::PLAGUE_TALE)
    {
        return calc(ui->PT_size->text());
    }

    if(_game == Games::LAST_OF_US)
    {
        return calc(ui->LOU_size->text());
    }

    if(_game == Games::CUPHEAD)
    {
        return calc(ui->Cup_size->text());
    }

    if(_game == Games::DYING_LIGHT)
    {
        return calc(ui->DL_size->text());
    }

    return calc(ui->War_size->text());

}

int Downloader::calc(QString _str)
{
    _str.removeFirst();
    _str.removeFirst();

    _str.removeLast();
    _str.removeLast();
    _str.removeLast();

    return _str.toInt();
}

void Downloader::setIcons()
{
    QSize iconSize = ui->ER_icon->size();
    QImage tempImage;

    tempImage.load("GameImages/EldenRing_cover.png");
    ui->ER_icon->setPixmap( QPixmap::fromImage( tempImage.scaled(iconSize) ) );

    tempImage.load("GameImages/GodOfWar_cover.png");
    ui->GOW_icon->setPixmap( QPixmap::fromImage( tempImage.scaled(iconSize) ) );

    tempImage.load("GameImages/Stray_cover.png");
    ui->Str_icon->setPixmap( QPixmap::fromImage( tempImage.scaled(iconSize) ) );

    tempImage.load("GameImages/Horizon_cover.png");
    ui->HFW_icon->setPixmap( QPixmap::fromImage( tempImage.scaled(iconSize) ) );

    tempImage.load("GameImages/PlagueTale_cover.png");
    ui->PT_icon->setPixmap( QPixmap::fromImage( tempImage.scaled(iconSize) ) );

    tempImage.load("GameImages/LastOfUs_cover.png");
    ui->LOU_icon->setPixmap( QPixmap::fromImage( tempImage.scaled(iconSize) ) );

    tempImage.load("GameImages/Cuphead_cover.png");
    ui->Cup_icon->setPixmap( QPixmap::fromImage( tempImage.scaled(iconSize) ) );

    tempImage.load("GameImages/DyingLight_cover.png");
    ui->DL_icon->setPixmap( QPixmap::fromImage( tempImage.scaled(iconSize) ) );

    tempImage.load("GameImages/Warhammer_cover.png");
    ui->War_icon->setPixmap( QPixmap::fromImage( tempImage.scaled(iconSize) ) );

    ui->ER_button->setIcon(QPixmap("ApplicationIcons/Pause.png"));
    ui->GOW_button->setIcon(QPixmap("ApplicationIcons/Pause.png"));
    ui->Str_button->setIcon(QPixmap("ApplicationIcons/Pause.png"));
    ui->HFW_button->setIcon(QPixmap("ApplicationIcons/Pause.png"));
    ui->PT_button->setIcon(QPixmap("ApplicationIcons/Pause.png"));
    ui->LOU_button->setIcon(QPixmap("ApplicationIcons/Pause.png"));
    ui->Cup_button->setIcon(QPixmap("ApplicationIcons/Pause.png"));
    ui->DL_button->setIcon(QPixmap("ApplicationIcons/Pause.png"));
    ui->War_button->setIcon(QPixmap("ApplicationIcons/Pause.png"));
}

void Downloader::setPauseStyle(QPushButton *_button, QLabel *_label)
{
    _label->setText("PAUSED");
    _button->setIcon(QPixmap("ApplicationIcons/Resume.png"));
}

void Downloader::setActiveStyle(QPushButton *_button, QLabel *_label)
{
    _label->setText("DOWNLOADING");
    _button->setIcon(QPixmap("ApplicationIcons/Pause.png"));
}

int generateSpeed(int _prevSpeed)
{
    int minSpeed = 1000;
    int maxSpeed = 3000;
    int newSpeed;

    int variant = getRandomValue(0, 1);
    int value = getRandomValue(0, 100);

    if(variant == 1)
    {
        if(_prevSpeed + value > maxSpeed)
            newSpeed = _prevSpeed - value;
        else
            newSpeed = _prevSpeed + value;
    }
    else
    {
        if(_prevSpeed - value < minSpeed)
            newSpeed = _prevSpeed + value;
        else
            newSpeed = _prevSpeed - value;
    }

    return newSpeed;
}

int calculateProcents(int _current, int _total)
{
    return ((_current * 100) / _total);
}


void Downloader::setValues(Games _game, int _speed, int _downloadedValue, int _procents)
{
    emit setValuesSignal(_game, _speed, _downloadedValue, _procents);
}

void Downloader::setValuesSlot(Games _game, int _speed, int _downloadedValue, int _procents)
{
    downloaded[static_cast<int>(_game)] = _downloadedValue;

    QString speedStr = QString::number(_speed) + " MB/s";
    QString downloadedValueStr = QString::number(_downloadedValue) + " MB";
    QString procentsStr = QString::number(_procents) + "%";

    if(_game == Games::ELDEN_RING)
    {
        ui->ER_speed->setText(speedStr);
        ui->ER_total->setText(downloadedValueStr);
        ui->ER_procents->setText(procentsStr);
        ui->ER_progressBar->setValue(_procents);
        return;
    }

    if(_game == Games::GOD_OF_WAR)
    {
        ui->GOW_speed->setText(speedStr);
        ui->GOW_total->setText(downloadedValueStr);
        ui->GOW_procents->setText(procentsStr);
        ui->GOW_progressBar->setValue(_procents);
        return;
    }

    if(_game == Games::STRAY)
    {
        ui->Str_speed->setText(speedStr);
        ui->Str_total->setText(downloadedValueStr);
        ui->Str_procents->setText(procentsStr);
        ui->Str_progressBar->setValue(_procents);
        return;
    }

    if(_game == Games::HORIZON)
    {
        ui->HFW_speed->setText(speedStr);
        ui->HFW_total->setText(downloadedValueStr);
        ui->HFW_procents->setText(procentsStr);
        ui->HFW_progressBar->setValue(_procents);
        return;
    }

    if(_game == Games::PLAGUE_TALE)
    {
        ui->PT_speed->setText(speedStr);
        ui->PT_total->setText(downloadedValueStr);
        ui->PT_procents->setText(procentsStr);
        ui->PT_progressBar->setValue(_procents);
        return;
    }

    if(_game == Games::LAST_OF_US)
    {
        ui->LOU_speed->setText(speedStr);
        ui->LOU_total->setText(downloadedValueStr);
        ui->LOU_procents->setText(procentsStr);
        ui->LOU_progressBar->setValue(_procents);
        return;
    }

    if(_game == Games::CUPHEAD)
    {
        ui->Cup_speed->setText(speedStr);
        ui->Cup_total->setText(downloadedValueStr);
        ui->Cup_procents->setText(procentsStr);
        ui->Cup_progressBar->setValue(_procents);
        return;
    }

    if(_game == Games::DYING_LIGHT)
    {
        ui->DL_speed->setText(speedStr);
        ui->DL_total->setText(downloadedValueStr);
        ui->DL_procents->setText(procentsStr);
        ui->DL_progressBar->setValue(_procents);
        return;
    }

    if(_game == Games::WARHAMMER)
    {
        ui->War_speed->setText(speedStr);
        ui->War_total->setText(downloadedValueStr);
        ui->War_procents->setText(procentsStr);
        ui->War_progressBar->setValue(_procents);
        return;
    }
}

int Downloader::getDownloadedValue(Games _game)
{
    return downloaded[static_cast<int>(_game)];
}

bool Downloader::isActive(Games _game)
{
    return active[static_cast<int>(_game)];
}

bool Downloader::isPaused(Games _game)
{
    return paused[static_cast<int>(_game)];
}

void executeDownload(Games _game, Downloader* _downloader)
{
    int size = _downloader->getGameSize(_game);
    int downloadedValue = _downloader->getDownloadedValue(_game);
    int speed = 800;

    int iteration = 1;

    while(true)
    {
        if(!_downloader->isActive(_game))
        {
            _downloader->setValues(_game, 0, 0, 0);
            return;
        }

        if(_downloader->isPaused(_game))
        {
            _downloader->setValues(_game, 0, downloadedValue, calculateProcents(downloadedValue, size));
            return;
        }

        if(iteration == 1 || iteration % 5 == 0)
        {
            speed = generateSpeed(speed);

            if(downloadedValue + speed >= size)
            {
                _downloader->downloadComleted(_game);
                return;
            }

            downloadedValue += speed;
            _downloader->setValues(_game, speed, downloadedValue, calculateProcents(downloadedValue, size));
        }

        ++iteration;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void Downloader::startDownload(Games _game)
{
    active[static_cast<int>(_game)] = true;
    update();

    std::thread th(executeDownload, _game, this);
    th.detach();
}

void Downloader::downloadComleted(Games _game)
{
    emit completeSignal(_game);
}

void Downloader::completeSlot(Games _game)
{
    active[int(_game)] = false;
    setValues(_game, 0, getGameSize(_game), 100);

    QString gameName = getFullGameName(_game);

    currentAccount->library.installed[static_cast<int>(_game)] = true;
    mainWindow->updateUserLibrary();
    mainWindow->showInformationalWindow("Download completed", ("Game " + gameName + "\nhas been successfully installed"));
    update();
}


void Downloader::on_ER_button_clicked()
{
    if(paused[static_cast<int>(Games::ELDEN_RING)])
    {
        paused[static_cast<int>(Games::ELDEN_RING)] = false;
        startDownload(Games::ELDEN_RING);
        setActiveStyle(ui->ER_button, ui->ER_status);
    }
    else
    {
        paused[static_cast<int>(Games::ELDEN_RING)] = true;
        setPauseStyle(ui->ER_button, ui->ER_status);
    }
}


void Downloader::on_GOW_button_clicked()
{
    if(paused[static_cast<int>(Games::GOD_OF_WAR)])
    {
        paused[static_cast<int>(Games::GOD_OF_WAR)] = false;
        startDownload(Games::GOD_OF_WAR);
        setActiveStyle(ui->GOW_button, ui->GOW_status);
    }
    else
    {
        paused[static_cast<int>(Games::GOD_OF_WAR)] = true;
        setPauseStyle(ui->GOW_button, ui->GOW_status);
    }
}


void Downloader::on_Str_button_clicked()
{
    if(paused[static_cast<int>(Games::STRAY)])
    {
        paused[static_cast<int>(Games::STRAY)] = false;
        startDownload(Games::STRAY);
        setActiveStyle(ui->Str_button, ui->Str_status);
    }
    else
    {
        paused[static_cast<int>(Games::STRAY)] = true;
        setPauseStyle(ui->Str_button, ui->Str_status);
    }
}


void Downloader::on_HFW_button_clicked()
{
    if(paused[static_cast<int>(Games::HORIZON)])
    {
        paused[static_cast<int>(Games::HORIZON)] = false;
        startDownload(Games::HORIZON);
        setActiveStyle(ui->HFW_button, ui->HFW_status);
    }
    else
    {
        paused[static_cast<int>(Games::HORIZON)] = true;
        setPauseStyle(ui->HFW_button, ui->HFW_status);
    }
}


void Downloader::on_PT_button_clicked()
{
    if(paused[static_cast<int>(Games::PLAGUE_TALE)])
    {
        paused[static_cast<int>(Games::PLAGUE_TALE)] = false;
        startDownload(Games::PLAGUE_TALE);
        setActiveStyle(ui->PT_button, ui->PT_status);
    }
    else
    {
        paused[static_cast<int>(Games::PLAGUE_TALE)] = true;
        setPauseStyle(ui->PT_button, ui->PT_status);
    }
}


void Downloader::on_LOU_button_clicked()
{
    if(paused[static_cast<int>(Games::LAST_OF_US)])
    {
        paused[static_cast<int>(Games::LAST_OF_US)] = false;
        startDownload(Games::LAST_OF_US);
        setActiveStyle(ui->LOU_button, ui->LOU_status);
    }
    else
    {
        paused[static_cast<int>(Games::LAST_OF_US)] = true;
        setPauseStyle(ui->LOU_button, ui->LOU_status);
    }
}


void Downloader::on_Cup_button_clicked()
{
    if(paused[static_cast<int>(Games::CUPHEAD)])
    {
        paused[static_cast<int>(Games::CUPHEAD)] = false;
        startDownload(Games::CUPHEAD);
        setActiveStyle(ui->Cup_button, ui->Cup_status);
    }
    else
    {
        paused[static_cast<int>(Games::CUPHEAD)] = true;
        setPauseStyle(ui->Cup_button, ui->Cup_status);
    }
}


void Downloader::on_DL_button_clicked()
{
    if(paused[static_cast<int>(Games::DYING_LIGHT)])
    {
        paused[static_cast<int>(Games::DYING_LIGHT)] = false;
        startDownload(Games::DYING_LIGHT);
        setActiveStyle(ui->DL_button, ui->DL_status);
    }
    else
    {
        paused[static_cast<int>(Games::DYING_LIGHT)] = true;
        setPauseStyle(ui->DL_button, ui->DL_status);
    }
}

void Downloader::on_War_button_clicked()
{
    if(paused[static_cast<int>(Games::WARHAMMER)])
    {
        paused[static_cast<int>(Games::WARHAMMER)] = false;
        startDownload(Games::WARHAMMER);
        setActiveStyle(ui->War_button, ui->War_status);
    }
    else
    {
        paused[static_cast<int>(Games::WARHAMMER)] = true;
        setPauseStyle(ui->War_button, ui->War_status);
    }
}


void Downloader::on_ER_cancel_clicked()
{
    active[static_cast<int>(Games::ELDEN_RING)] = false;
    update();
}

void Downloader::on_GOW_cancel_clicked()
{
    active[static_cast<int>(Games::GOD_OF_WAR)] = false;
    update();
}

void Downloader::on_Str_cancel_clicked()
{
    active[static_cast<int>(Games::STRAY)] = false;
    update();
}

void Downloader::on_HFW_cancel_clicked()
{
    active[static_cast<int>(Games::HORIZON)] = false;
    update();
}

void Downloader::on_PT_cancel_clicked()
{
    active[static_cast<int>(Games::PLAGUE_TALE)] = false;
    update();
}

void Downloader::on_LOU_cancel_clicked()
{
    active[static_cast<int>(Games::LAST_OF_US)] = false;
    update();
}

void Downloader::on_Cup_cancel_clicked()
{
    active[static_cast<int>(Games::CUPHEAD)] = false;
    update();
}

void Downloader::on_DL_cancel_clicked()
{
    active[static_cast<int>(Games::DYING_LIGHT)] = false;
    update();
}

void Downloader::on_War_cancel_clicked()
{
    active[static_cast<int>(Games::WARHAMMER)] = false;
    update();
}


void Downloader::on_Library_pushButton_clicked()
{
    mainWindow->showLibrary();
}

