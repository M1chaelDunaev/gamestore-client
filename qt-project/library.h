#ifndef LIBRARY_H
#define LIBRARY_H

#include <QWidget>
#include <QStackedLayout>

class MainWindow;
class UserAccount;
enum class Games;
class ItemEldenRing;
class ItemGodOfWar;
class ItemStray;
class ItemHorizon;
class ItemPlagueTale;
class ItemLastOfUs;
class ItemCuphead;
class ItemDyingLight;
class ItemWarhammer;

namespace Ui {
class Library;
}

class Library : public QWidget
{
    Q_OBJECT
    Ui::Library *ui;

    MainWindow* mainWindow;
    UserAccount* currentAccount;
    QStackedLayout* centralLayout;

    //Windows
    ItemEldenRing* eldenRing;
    ItemGodOfWar* godOfWar;
    ItemStray* stray;
    ItemHorizon* horizon;
    ItemPlagueTale* plagueTale;
    ItemLastOfUs* lastOfUs;
    ItemCuphead* cuphead;
    ItemDyingLight* dyingLight;
    ItemWarhammer* warhammer;

    void initWindows(); //Set all windows pointers as nullptr
    void deleteWindows();

    void init(); //Set start window
    void setGameList(); //Create menu that contain only bought games
    void setIcons();
    void setCurrentGame(Games _game);

    //StyleSheets
    QString currentGame_styleSheet();
    QString baseGame_styleSheet();

public:
    explicit Library(MainWindow* _mainWindow, UserAccount* _currentAccount);
    ~Library();

    // QWidget interface
protected:
    virtual void showEvent(QShowEvent *event) override;
private slots:
    void on_ER_pushButton_clicked();
    void on_GOW_button_clicked();
    void on_Str_button_clicked();
    void on_PT_button_clicked();
    void on_HWF_button_clicked();
    void on_LOU_button_clicked();
    void on_Cup_button_clicked();
    void on_DL_button_clicked();
    void on_War_button_clicked();
    void on_toStore_pushButton_clicked();
};

#endif // LIBRARY_H
