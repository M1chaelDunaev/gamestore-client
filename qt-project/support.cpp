#include "support.h"
#include "ui_support.h"
#include "mainapplication.h"
#include "informationalwindow.h"
#include "useraccount.h"
#include "restorepassword.h"
#include "restoreemail.h"
#include "restoresqanswer.h"
#include "restorephonenumber.h"
#include "functions.h"
#include <thread>



Support::Support(MainApplication* _mainApp) :
    QWidget(nullptr), ui(new Ui::Support), mainApp(_mainApp)
{
    ui->setupUi(this);
    connect(this, SIGNAL(showStoreMessageSignal(QString,QString)), mainApp, SLOT(showStoreMessageSlot(QString,QString)));
}

Support::~Support()
{
    delete ui;
}


int Support::getIdByEmail(const QString &_email)
{
    return mainApp->getIdByEmail(_email);
}

int Support::getIdByPhoneNumber(const QString &_phoneNumber)
{
    return mainApp->getIdByPhoneNumber(_phoneNumber);
}

void Support::getCountryAndSQ(int _id, SecretQuestionTypes &_type, QString &_answer, QString &_country)
{
    mainApp->getCountryAndSQ(_id, _type, _answer, _country);
}

void Support::showStoreMessage(const QString &_code, const QString &_action)
{
    auto func = [=]()
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(getRandomValue(700, 3500)));
        emit showStoreMessageSignal(_code, _action);
    };

    std::thread th(func);
    th.detach();
}



void Support::setNewPassword(int _id, const QString &_password)
{
    mainApp->updateUserAccount(_id, "Password", mainApp->getHash(_password));
    InformationalWindow* iw = new InformationalWindow("Success", "Password has been successfully changed");
    iw->exec();
    delete iw;
}

void Support::setNewEmail(int _id, const QString &_email)
{
    mainApp->updateUserAccount(_id, "Email", _email);
    InformationalWindow* iw = new InformationalWindow("Success", "Email has been successfully changed");
    iw->exec();
    delete iw;
}

void Support::setNewPhoneNumber(int _id, const QString &_phoneNumber)
{
    mainApp->updateUserAccount(_id, "PhoneNumber", _phoneNumber);
    InformationalWindow* iw = new InformationalWindow("Success", "Phone number has been\nsuccessfully changed");
    iw->exec();
    delete iw;
}

void Support::setNewSecretQuestion(int _id, SecretQuestionTypes _type, const QString &_answer)
{
    mainApp->updateUserAccount(_id, "SecretQuestionType", QString::number((int)_type));
    mainApp->updateUserAccount(_id, "SecretQuestionAnswer", _answer);
    InformationalWindow* iw = new InformationalWindow("Success", "Secret question has been\nsuccessfully changed");
    iw->exec();
    delete iw;
}


void Support::on_ForgotPasswor_pushButton_clicked()
{
    RestorePassword* rp = new RestorePassword(this);
    rp->setWindowTitle("Restore password");
    rp->setWindowIcon(QPixmap("ApplicationIcons/Logotype.png"));
    rp->exec();
    delete rp;
}

void Support::on_ForgotSQ_pushButton_clicked()
{
    RestoreSQAnswer* rsq = new RestoreSQAnswer(this);
    rsq->setWindowTitle("Restore secret question");
    rsq->setWindowIcon(QPixmap("ApplicationIcons/Logotype.png"));
    rsq->exec();
    delete rsq;
}

void Support::on_ForgotEmail_pushButton_clicked()
{
    RestoreEmail* re = new RestoreEmail(this);
    re->setWindowTitle("Restore email");
    re->setWindowIcon(QPixmap("ApplicationIcons/Logotype.png"));
    re->exec();
    delete re;
}

void Support::on_ChangePhoneNumber_pushButton_clicked()
{
    RestorePhoneNumber* rpn = new RestorePhoneNumber(this);
    rpn->setWindowTitle("Restore phone number");
    rpn->setWindowIcon(QPixmap("ApplicationIcons/Logotype.png"));
    rpn->exec();
    delete rpn;
}

