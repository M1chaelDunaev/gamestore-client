#ifndef SUPPORTHOLDER_H
#define SUPPORTHOLDER_H

#include <QWidget>

class Support;
class QVBoxLayout;
class MainApplication;

namespace Ui {
class SupportHolder;
}

class SupportHolder : public QWidget
{
    Q_OBJECT
    Ui::SupportHolder *ui;
    QVBoxLayout* mainLayout;
    MainApplication* mainApp;
    Support* support;

    QPointF prevMousePos;
    Qt::MouseButton lastPressedMouseButton;
    QScreen* screenInfo;

public:
    explicit SupportHolder(MainApplication* _mainApp);
    ~SupportHolder();

private slots:
    void on_Close_pushButton_clicked();

    void on_MaximizedNormal_pushButton_clicked();

    void on_Minimized_pushButton_clicked();

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // SUPPORTHOLDER_H
