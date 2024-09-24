#ifndef SUPPORT_H
#define SUPPORT_H

#include <QWidget>

class MainApplication;
enum class SecretQuestionTypes;

namespace Ui {
class Support;
}

class Support : public QWidget
{
    Q_OBJECT

    MainApplication* mainApp;
    Ui::Support *ui;
public:
    explicit Support(MainApplication* _mainApp);
     ~Support();

    //Delegating to mainApp methods to get info from database
    int getIdByEmail(const QString& _email);
    int getIdByPhoneNumber(const QString& _phoneNumber);
    void getCountryAndSQ(int _id, SecretQuestionTypes& _type, QString& _answer, QString& _country);

    void showStoreMessage(const QString& _code, const QString& _action);//To show message with code and action description

    //Methods to update database
    void setNewPassword(int _id, const QString& _password);
    void setNewEmail(int _id, const QString& _email);
    void setNewSecretQuestion(int _id, SecretQuestionTypes _type, const QString& _answer);
    void setNewPhoneNumber(int _id, const QString& _phoneNumber);

signals:
    void showStoreMessageSignal(const QString& _code, const QString& _action);

private slots:
    void on_ForgotPasswor_pushButton_clicked();
    void on_ForgotSQ_pushButton_clicked();
    void on_ForgotEmail_pushButton_clicked();
    void on_ChangePhoneNumber_pushButton_clicked();
};

#endif // SUPPORT_H
