#ifndef INFORMATIONALWINDOW_H
#define INFORMATIONALWINDOW_H

#include <QDialog>

namespace Ui {
class InformationalWindow;
}

class InformationalWindow : public QDialog
{
    Q_OBJECT

public:
    explicit InformationalWindow(const QString& _tittle, const QString& _text);
    ~InformationalWindow();

private slots:
    void on_Close_button_clicked();

private:
    Ui::InformationalWindow *ui;
};

#endif // INFORMATIONALWINDOW_H
