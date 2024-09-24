#ifndef EDITPROFILE_H
#define EDITPROFILE_H
#include <QWidget>
#include <QImage>

class MainWindow;
class UserAccount;

namespace Ui {
class EditProfile;
}

class EditProfile : public QWidget
{
    Q_OBJECT
    Ui::EditProfile *ui;

    MainWindow* mainWindow;
    UserAccount* currentAccount;

    void setLineEdits();
    bool isCorrectProfileName(const QString& _profileName);
    bool isCorrectName(const QString& _name);

    void restoreLineEdits();
    void updateWindow();

    QString lineEdit_StyleSheet();
    QString lineEditError_StyleSheet();

public:
    explicit EditProfile(MainWindow* _mainWindow, UserAccount* _currentAccount);
    ~EditProfile();
private slots:
    void on_UploadAvatar_pushButton_clicked();
    void on_Save_pushButton_clicked();

    // QWidget interface
    void on_Account_pushButton_clicked();

protected:
    virtual void showEvent(QShowEvent *event) override {updateWindow();};
};

#endif // EDITPROFILE_H
