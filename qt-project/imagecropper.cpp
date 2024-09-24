#include "imagecropper.h"
#include "ui_imagecropper.h"
#include <QMouseEvent>
#include <QWidget>
#include "functions.h"
#include "mainwindow.h"
#include "cropperscene.h"

ImageCropper::ImageCropper(MainWindow* _mainWindow, const QString& _imagePath) :
    QDialog(nullptr), ui(new Ui::ImageCropper), mainWindow(_mainWindow)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);
    setWindowTitle("Image cropper");
    setWindowIcon(QPixmap("ApplicationIcons/Logotype.png"));
    ui->Close_button->setIcon(QPixmap("ApplicationIcons/CloseCross.png"));  
    screenInfo = QApplication::primaryScreen();

    cropperScene = new CropperScene(ui->graphicsView, _imagePath);
    ui->graphicsView->setScene(cropperScene);
    validAvatar = false;

    connect(cropperScene, &CropperScene::sendPreview, this, &ImageCropper::setPreview);
}

ImageCropper::~ImageCropper()
{
    delete ui;
    delete cropperScene;
}

void ImageCropper::mousePressEvent(QMouseEvent *event)
{
    lastPressedMouseButton = event->button();
    if(lastPressedMouseButton == Qt::LeftButton)
    {
        prevMousePos = event->globalPosition();
    }

    event->accept();
}

void ImageCropper::mouseMoveEvent(QMouseEvent *event)
{

    if(lastPressedMouseButton != Qt::LeftButton)
        return;

    if(event->globalPosition().y() == 0)
        return;

    if(event->globalPosition().y() >= screenInfo->size().height() - 40) //40px is height of Windows bottom bar
        return;

    if(containsPoint(ui->UpperFrame, event->pos()))
    {
        QPointF delta = event->globalPosition() - prevMousePos;
        move(this->pos() + delta.toPoint());
    }

    prevMousePos = event->globalPosition();

    event->accept();
}

void ImageCropper::on_Close_button_clicked()
{
    close();
}

void ImageCropper::setPreview(const QPixmap &_preview)
{
    ui->Preview->setPixmap(_preview);

    if(!validAvatar)
        validAvatar = true;
}


void ImageCropper::on_ApplyButton_clicked()
{
    if(!validAvatar)
    {
        mainWindow->showInformationalWindow("Error", "Image is not cropped");
        return;
    }

    mainWindow->setAvatar(ui->Preview->pixmap());

    mainWindow->showInformationalWindow("Success", "Avatar has been successfully changed");
    close();

}

