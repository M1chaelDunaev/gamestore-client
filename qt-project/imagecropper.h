#ifndef IMAGECROPPER_H
#define IMAGECROPPER_H

#include <QDialog>
class MainWindow;
class CropperScene;

namespace Ui {
class ImageCropper;
}

class ImageCropper : public QDialog
{
    Q_OBJECT

    Ui::ImageCropper *ui;

    Qt::MouseButton lastPressedMouseButton;
    QPointF prevMousePos;
    QScreen* screenInfo;

    MainWindow* mainWindow;
    CropperScene* cropperScene;
    bool validAvatar;

public:
    explicit ImageCropper(MainWindow* _mainWindow, const QString& _imagePath);
    ~ImageCropper();


    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
private slots:
    void on_Close_button_clicked();
    void setPreview(const QPixmap& _preview);
    void on_ApplyButton_clicked();
};

#endif // IMAGECROPPER_H
