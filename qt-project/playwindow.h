#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H

#include <QDialog>

namespace Ui {
class PlayWindow;
}

class PlayWindow : public QDialog
{
    Q_OBJECT
    Ui::PlayWindow *ui;

public:
    explicit PlayWindow(const QString& _gameName, const QString& _iconPath);
    ~PlayWindow();
};

#endif // PLAYWINDOW_H
