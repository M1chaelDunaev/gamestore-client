#ifndef PROMOCODEWINDOW_H
#define PROMOCODEWINDOW_H

#include <QDialog>

namespace Ui {
class PromocodeWindow;
}

class PromocodeWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PromocodeWindow(const QString& _promocode);
    ~PromocodeWindow();

private slots:
    void on_Copy_clicked();

    void on_Close_button_clicked();

private:
    Ui::PromocodeWindow *ui;
};

#endif // PROMOCODEWINDOW_H
