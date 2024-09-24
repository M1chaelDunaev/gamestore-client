#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QWidget>

class MainWindow;
class UserAccount;
enum class Games;
class QLabel;
class QProgressBar;
class QPushButton;
class Downloader;

void executeDownload(Games _game, Downloader* _downloader);
int generateSpeed();

int calculateProcents(int _current, int _total);

namespace Ui {
class Downloader;
}

class Downloader : public QWidget
{
    Q_OBJECT

    Ui::Downloader *ui;
    MainWindow* mainWindow;
    UserAccount* currentAccount;

    bool active[9];
    bool paused[9];
    int downloaded[9];

    int calc(QString _str);

    void resumeDownload(Games _game);
    void update();
    void setIcons();

    void setPauseStyle(QPushButton* _button, QLabel* _label);
    void setActiveStyle(QPushButton* _button, QLabel* _label);

public:
    explicit Downloader(MainWindow* _mainWindow, UserAccount* _currentAccount);
    ~Downloader();

    void startDownload(Games _game);
    void downloadComleted(Games _game);

    void setSpeed(Games _game, int _value);
    void setDownloadedValue(Games _game, int _value);
    void setProcents(Games _game, int _value);
    void setValues(Games _game, int _speed, int _downloadedValue, int _procents);

    bool isActive(Games _game);
    bool isPaused(Games _game);

    int getGameSize(Games _game);
    int getDownloadedValue(Games _game);

signals:
    void completeSignal(Games _game);
    void setValuesSignal(Games _game, int _speed, int _downloadedValue, int _procents);

private slots:

    void completeSlot(Games _game);
    void setValuesSlot(Games _game, int _speed, int _downloadedValue, int _procents);

    void on_ER_button_clicked();
    void on_ER_cancel_clicked();


    void on_GOW_button_clicked();

    void on_Str_button_clicked();

    void on_HFW_button_clicked();

    void on_PT_button_clicked();

    void on_LOU_button_clicked();

    void on_Cup_button_clicked();

    void on_DL_button_clicked();

    void on_War_button_clicked();

    void on_GOW_cancel_clicked();

    void on_Str_cancel_clicked();

    void on_HFW_cancel_clicked();

    void on_PT_cancel_clicked();

    void on_LOU_cancel_clicked();

    void on_Cup_cancel_clicked();

    void on_DL_cancel_clicked();

    void on_War_cancel_clicked();


    void on_Library_pushButton_clicked();
};

#endif // DOWNLOADER_H
