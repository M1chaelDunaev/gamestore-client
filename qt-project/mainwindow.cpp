#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QSqlQuery>
#include <QCryptographicHash>
#include <thread>
#include <QMouseEvent>
#include <QSizeGrip>

#include "promocodewindow.h"
#include "promocodeslist.h"
#include "informationalwindow.h"
#include "gifts.h"

#include "useraccount.h"
#include "functions.h"
#include "store.h"
#include "library.h"
#include "community.h"
#include "userprofile.h"
#include "editprofile.h"
#include "wallet.h"
#include "mainapplication.h"
#include "support.h"
#include "cart.h"
#include "downloader.h"
#include "playwindow.h"
#include "imagecropper.h"

#include "itemeldenring.h"
#include "itemgodofwar.h"
#include "itemstray.h"
#include "itemhorizon.h"
#include "itemplaguetale.h"
#include "itemlastofus.h"
#include "itemcuphead.h"
#include "itemdyinglight.h"
#include "itemwarhammer.h"


MainWindow::MainWindow(MainApplication* _app, int _id) :
    QWidget(nullptr), ui(new Ui::MainWindow), mainApp(_app)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);
    setMouseTracking(true);
    screenInfo = QApplication::primaryScreen();
    setMaximumSize(screenInfo->size());

    QSizeGrip* sg = new QSizeGrip(this);
    ui->SizeGripLayout->addWidget(sg);
    ui->LogOut->hide();

    currentAccount = mainApp->initCurrentAccount(_id);
    promocodesList = mainApp->initPromocodesList();

    setWindowTitle("Games Store");
    setIcons();
    createWindows();
    makeCentralLayout();
    ui->Central_widget->setLayout(centralLayout);
    setCurrentMenu(ui->Store_pushButton);

    connect(this, SIGNAL(showBankMessageSignal(QString,QString)), mainApp, SLOT(showBankMessageSlot(QString,QString)));
}


MainWindow::~MainWindow()
{
    delete ui;
    deleteWindows();
    delete centralLayout;
    delete currentAccount;
    delete promocodesList;
}


void MainWindow::createWindows()
{
    store = new Store(this, currentAccount);
    library = new Library(this, currentAccount);
    community = new Community();
    profile =  new UserProfile(this, currentAccount);
    wallet = new Wallet(this, currentAccount);
    support = new Support(mainApp);
    cart = new Cart(this, currentAccount);
    downloader = new Downloader(this, currentAccount);

    editProfile = nullptr;

    eldenRing = nullptr;
    godOfWar = nullptr;
    stray = nullptr;
    horizon = nullptr;
    plagueTale = nullptr;
    lastOfUs = nullptr;
    cuphead = nullptr;
    dyingLight = nullptr;
    warhammer = nullptr;
}

void MainWindow::deleteWindows()
{
    delete store;
    delete library;
    delete community;
    delete profile;
    delete editProfile;
    delete wallet;
    delete cart;

    delete eldenRing;
    delete godOfWar;
    delete stray;
    delete horizon;
    delete plagueTale;
    delete lastOfUs;
    delete cuphead;
    delete dyingLight;
    delete warhammer;
}

void MainWindow::makeCentralLayout()
{
    centralLayout = new QStackedLayout(ui->Central_widget);
    centralLayout->addWidget(store);
    centralLayout->addWidget(library);
    centralLayout->addWidget(community);

    centralLayout->addWidget(profile);
    centralLayout->addWidget(wallet);
    centralLayout->addWidget(support);
    centralLayout->addWidget(cart);
    centralLayout->addWidget(downloader);
}

void MainWindow::setIcons()
{
    setWindowIcon(QPixmap("ApplicationIcons/Logotype.png"));
    ui->PromocodeIcon->setIcon(QPixmap("ApplicationIcons/EnterPromocode.png"));
    ui->DownloadsIcon->setIcon(QPixmap("ApplicationIcons/DownloadManager.png"));
    ui->FriendsChatIcon->setIcon(QPixmap("ApplicationIcons/FriendsAndChat.png"));
    ui->Notifications->setIcon(QPixmap("ApplicationIcons/NotificationsOn.png"));
    ui->Sounds->setIcon(QPixmap("ApplicationIcons/SoundsOn.png"));
    ui->Logo_label->setPixmap(QPixmap("ApplicationIcons/LogotypeMin.png"));

    ui->Close_pushButton->setIcon(QPixmap("ApplicationIcons/CloseCross.png"));
    ui->Minimized_pushButton->setIcon(QPixmap("ApplicationIcons/ShowMinimized.png"));
    ui->MaximizedNormal_pushButton->setIcon(QPixmap("ApplicationIcons/ShowNormal.png"));
}


void MainWindow::showStore()
{
    centralLayout->setCurrentWidget(store);
    setCurrentMenu(ui->Store_pushButton);
}

void MainWindow::showLibrary()
{
    centralLayout->setCurrentWidget(library);
    setCurrentMenu(ui->Library_pushButton);
}

void MainWindow::showCommunity()
{
    centralLayout->setCurrentWidget(community);
    setCurrentMenu(ui->Community_pushButton);
}

void MainWindow::showProfile()
{
    centralLayout->setCurrentWidget(profile);
    setCurrentMenu(ui->Account_pushButton);
}

void MainWindow::showEditProfile()
{
    if(!editProfile)
    {
        editProfile = new EditProfile(this, currentAccount);
        centralLayout->addWidget(editProfile);
    }

    centralLayout->setCurrentWidget(editProfile);
    setCurrentMenu(nullptr);
}

void MainWindow::showWallet()
{
    centralLayout->setCurrentWidget(wallet);
    setCurrentMenu(nullptr);
}

void MainWindow::showCart()
{
    centralLayout->setCurrentWidget(cart);
    setCurrentMenu(nullptr);
}

void MainWindow::showDownloader()
{
    centralLayout->setCurrentWidget(downloader);
    setCurrentMenu(nullptr);
}

void MainWindow::showGame(Games _game)
{
    setCurrentMenu(nullptr);

    switch(_game)
    {
    case Games::ELDEN_RING:
    {
        if(!eldenRing)
        {
            eldenRing = new ItemEldenRing(this, currentAccount);
            centralLayout->addWidget(eldenRing);
        }

        centralLayout->setCurrentWidget(eldenRing);
        break;
    }
    case Games::GOD_OF_WAR:
    {
        if(!godOfWar)
        {
            godOfWar = new ItemGodOfWar(this, currentAccount);
            centralLayout->addWidget(godOfWar);
        }

        centralLayout->setCurrentWidget(godOfWar);
        break;
    }
    case Games::STRAY:
    {
        if(!stray)
        {
            stray = new ItemStray(this, currentAccount);
            centralLayout->addWidget(stray);
        }

        centralLayout->setCurrentWidget(stray);
        break;
    }
    case Games::HORIZON:
    {
        if(!horizon)
        {
            horizon = new ItemHorizon(this, currentAccount);
            centralLayout->addWidget(horizon);
        }

        centralLayout->setCurrentWidget(horizon);
        break;
    }
    case Games::PLAGUE_TALE:
    {
        if(!plagueTale)
        {
            plagueTale = new ItemPlagueTale(this, currentAccount);
            centralLayout->addWidget(plagueTale);
        }

        centralLayout->setCurrentWidget(plagueTale);
        break;
    }
    case Games::LAST_OF_US:
    {
        if(!lastOfUs)
        {
            lastOfUs = new ItemLastOfUs(this, currentAccount);
            centralLayout->addWidget(lastOfUs);
        }

        centralLayout->setCurrentWidget(lastOfUs);
        break;
    }
    case Games::CUPHEAD:
    {
        if(!cuphead)
        {
            cuphead = new ItemCuphead(this, currentAccount);
            centralLayout->addWidget(cuphead);
        }

        centralLayout->setCurrentWidget(cuphead);
        break;
    }
    case Games::DYING_LIGHT:
    {
        if(!dyingLight)
        {
            dyingLight = new ItemDyingLight(this, currentAccount);
            centralLayout->addWidget(dyingLight);
        }

        centralLayout->setCurrentWidget(dyingLight);
        break;
    }
    case Games::WARHAMMER:
    {
        if(!warhammer)
        {
            warhammer = new ItemWarhammer(this, currentAccount);
            centralLayout->addWidget(warhammer);
        }

        centralLayout->setCurrentWidget(warhammer);
        break;
    }
    }
}

void MainWindow::showPlayWindow(Games _game, const QString &_iconPath)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
    PlayWindow* pw = new PlayWindow(getFullGameName(_game), _iconPath);
    pw->exec();
    delete pw;
}

void MainWindow::startDownload(Games _game)
{
    if(!downloader->isActive(_game))
    {
        downloader->startDownload(_game);
    }
    centralLayout->setCurrentWidget(downloader);
}

void MainWindow::topUpBalance()
{
    wallet->on_TopUpBalance_pushButton_clicked();
}

void MainWindow::setCurrentMenu(QPushButton* _button)
{
    if(_button == ui->Store_pushButton)
    {
        _button->setStyleSheet(bigMenuActive_styleSheet());
    }
    else
    {
        ui->Store_pushButton->setStyleSheet(bigMenuBase_styleSheet());
    }

    if(_button == ui->Library_pushButton)
    {
        _button->setStyleSheet(bigMenuActive_styleSheet());
    }
    else
    {
        ui->Library_pushButton->setStyleSheet(bigMenuBase_styleSheet());
    }

    if(_button == ui->Community_pushButton)
    {
        _button->setStyleSheet(bigMenuActive_styleSheet());
    }
    else
    {
        ui->Community_pushButton->setStyleSheet(bigMenuBase_styleSheet());
    }

    if(_button == ui->Account_pushButton)
    {
        _button->setStyleSheet(bigMenuActive_styleSheet());
    }
    else
    {
        ui->Account_pushButton->setStyleSheet(bigMenuBase_styleSheet());
    }


    if(_button == ui->Wallet_pushButton)
    {
        _button->setStyleSheet(smallMenuActive_styleSheet());
    }
    else
    {
       ui->Wallet_pushButton->setStyleSheet(smallMenuBase_styleSheet());
    }

    if(_button == ui->Friends_pushButton)
    {
        _button->setStyleSheet(smallMenuActive_styleSheet());
    }
    else
    {
        ui->Friends_pushButton->setStyleSheet(smallMenuBase_styleSheet());
    }

    if(_button == ui->Support_pushButton)
    {
        _button->setStyleSheet(smallMenuActive_styleSheet());
    }
    else
    {
        ui->Support_pushButton->setStyleSheet(smallMenuBase_styleSheet());
    }

}


void MainWindow::updateUserAccount(const QString &_field, const QString &_value)
{
    mainApp->updateUserAccount(currentAccount->id, _field, _value);
}

void MainWindow::updateUserLibrary()
{

    QString bought = "";
    QString installed = "";

    for(int i = 0; i < 9; ++i)
    {
        if(currentAccount->library.bought[i])
            bought.push_back('1');
        else
            bought.push_back('0');

        if(currentAccount->library.installed[i])
            installed.push_back('1');
        else
            installed.push_back('0');
    }

    mainApp->updateUserLibrary(currentAccount->id, bought, installed);

}

void MainWindow::updateUserActivity()
{
    QString activity = "";
    activity += QString::number(static_cast<int>(currentAccount->activity.first)) + "-";
    activity += QString::number(static_cast<int>(currentAccount->activity.second)) + "-";
    activity += QString::number(static_cast<int>(currentAccount->activity.third));

    mainApp->updateUserActivity(currentAccount->id, activity);
}

void MainWindow::setAvatar(const QPixmap &_avatar)
{
    QString newFileName = "Avatars/Avatar_";
    newFileName += QString::number(currentAccount->id);
    newFileName += ".png";

    _avatar.save(newFileName);
}

void MainWindow::updateUserBalance()
{
    wallet->setBalance();
    mainApp->updateUserBalance(currentAccount->id, currentAccount->balance);
}

QString MainWindow::createPromocode(PromocodeTypes _type, const QString& _value)
{
    QString code = QCryptographicHash::hash( QByteArray::number(getRandomValue(-100000000, 100000000)), QCryptographicHash::Blake2s_128).toHex();
    QString value = QString::number(static_cast<int>(_type)) + "-" + _value;

    promocodesList->insert(code, value);
    mainApp->addPromocode(code, value);

    return code;
}

void MainWindow::deletePromocode(const QString &_code)
{
    mainApp->deletePromocode(_code);
    promocodesList->remove(_code);
}


void MainWindow::showBankMessage(const QString& _code, const QString& _sum)
{
    auto func = [=]()
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(getRandomValue(700, 3500)));
        emit showBankMessageSignal(_code, _sum);
    };

    std::thread th(func);
    th.detach();
}

void MainWindow::showPromocodeWindow(const QString &_code)
{
    PromocodeWindow* pw = new PromocodeWindow(_code);

    pw->exec();
    delete pw;
}

void MainWindow::showGiftsWindow()
{
    Gifts* g = new Gifts(this, currentAccount, promocodesList);
    g->exec();
    delete g;
}

void MainWindow::showInformationalWindow(const QString& _tittle, const QString& _text)
{
    InformationalWindow* iw = new InformationalWindow(_tittle, _text);
    iw->setWindowTitle("Info");
    iw->exec();
    delete iw;
}


QString MainWindow::bigMenuBase_styleSheet()
{
    QString styleSheet = "";
    styleSheet += "QPushButton{ color: rgb(255, 255, 255); font: 16pt Arial; "
                  "background-color: rgba(0, 0, 0, 0); border: 0px;} "
                  "QPushButton:hover{ text-decoration: underline; }";

    return styleSheet;
}

QString MainWindow::smallMenuBase_styleSheet()
{
    QString styleSheet = "";
    styleSheet += "QPushButton{ color: rgb(182, 182, 182); font: 9pt Arial; "
                  "background-color: rgba(0, 0, 0, 0); border: 0px;} "
                  "QPushButton:hover{ color: rgb(255, 255, 255); }";

    return styleSheet;
}

QString MainWindow::bigMenuActive_styleSheet()
{
    QString styleSheet = "";
    styleSheet += "color: rgb(55, 225, 255); font: 16pt Arial; border: 0px; "
                  "background-color: rgba(0, 0, 0, 0); text-decoration: underline;";

    return styleSheet;
}

QString MainWindow::smallMenuActive_styleSheet()
{
    QString styleSheet = "";
    styleSheet += "color: rgb(255, 255, 255); font: 9pt Arial; border: 0px; "
                  "background-color: rgba(0, 0, 0, 0); text-decoration: underline;";

    return styleSheet;
}

QString MainWindow::userMenuBase_styleSheet()
{
    return "QPushButton{background-color: rgb(74, 79, 90); border: 0px; color: rgb(55, 225, 255);} QPushButton:hover{background-color: rgb(129, 138, 157)}";
}

QString MainWindow::userMenuActive_styleSheet()
{
    return "background-color: rgb(129, 138, 157); color: rgb(55, 225, 255);";
}

void MainWindow::on_Store_pushButton_clicked()
{
    centralLayout->setCurrentWidget(store);
    setCurrentMenu(ui->Store_pushButton);
}


void MainWindow::on_Library_pushButton_clicked()
{
    centralLayout->setCurrentWidget(library);
    setCurrentMenu(ui->Library_pushButton);
}


void MainWindow::on_Community_pushButton_clicked()
{
    centralLayout->setCurrentWidget(community);
    setCurrentMenu(ui->Community_pushButton);
}


void MainWindow::on_Account_pushButton_clicked()
{
    setCurrentMenu(ui->Account_pushButton);
    centralLayout->setCurrentWidget(profile);
}


void MainWindow::on_Settings_pushButton_clicked()
{
    showInformationalWindow("Error", "Settings are not available in this version");
}


void MainWindow::on_Support_pushButton_clicked()
{
    setCurrentMenu(ui->Support_pushButton);
    centralLayout->setCurrentWidget(support);
}


void MainWindow::on_Friends_pushButton_clicked()
{
    setCurrentMenu(ui->Friends_pushButton);
    centralLayout->setCurrentWidget(community);
}


void MainWindow::on_Wallet_pushButton_clicked()
{
    setCurrentMenu(ui->Wallet_pushButton);
    centralLayout->setCurrentWidget(wallet);
}


void MainWindow::on_UserMenu_pushButton_clicked()
{
    userMenuActivated = !userMenuActivated;
    if(userMenuActivated)
    {
        ui->LogOut->show();
        ui->UserMenu_pushButton->setStyleSheet(userMenuActive_styleSheet());
        return;
    }
    else
    {
        ui->LogOut->hide();
        ui->UserMenu_pushButton->setStyleSheet(userMenuBase_styleSheet());
    }
}


void MainWindow::on_Notifications_clicked()
{
    notifications = !notifications;
    if(notifications)
        ui->Notifications->setIcon(QPixmap("ApplicationIcons/NotificationsOn.png"));
    else
        ui->Notifications->setIcon(QPixmap("ApplicationIcons/NotificationsOff.png"));
}

void MainWindow::on_Sounds_clicked()
{
    sounds = !sounds;
    if(sounds)
        ui->Sounds->setIcon(QPixmap("ApplicationIcons/SoundsOn.png"));
    else
        ui->Sounds->setIcon(QPixmap("ApplicationIcons/SoundsOff.png"));
}


void MainWindow::on_EnterThePromocode_clicked()
{
    showGiftsWindow();
}


void MainWindow::on_ManageDownloads_clicked()
{
    showDownloader();
}


void MainWindow::on_FriendsAndChat_clicked()
{
    centralLayout->setCurrentWidget(community);
    setCurrentMenu(nullptr);
}


void MainWindow::on_MaximizedNormal_pushButton_clicked()
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


void MainWindow::on_Minimized_pushButton_clicked()
{
    showMinimized();
}


void MainWindow::on_Close_pushButton_clicked()
{
    close();
}


void MainWindow::on_LogOut_clicked()
{
    emit logOutSignal();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    lastPressedMouseButton = event->button();

    if(lastPressedMouseButton == Qt::LeftButton)
    {
        prevMousePos = event->globalPosition();
        sizeGripActivated = false;
    }

    event->accept();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(lastPressedMouseButton != Qt::LeftButton)
        return;

    if(sizeGripActivated) //To correct sizeGrip work
        return;

    if(event->globalPosition().y() == 0)
    {
        showMaximized();
        return;
    }

    if(event->globalPosition().y() >= screenInfo->size().height() - 40) //40px is height of Windows bottom bar
        return;

    if( containsPoint(ui->Upper_frame, event->position().toPoint()) ||
        containsPoint(ui->Botom_frame, event->position().toPoint()))
    {

        QPointF delta = event->globalPosition() - prevMousePos;

        if(isMaximized())
        {
            showNormal();            
        }

        move(this->pos() + delta.toPoint());
    }

    prevMousePos = event->globalPosition().toPoint();
    event->accept();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    sizeGripActivated = true;
}


