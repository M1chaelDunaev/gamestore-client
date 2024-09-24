#include "cropperscene.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMoveEvent>
#include <QRect>

CropperScene::CropperScene(QObject *parent, const QString& _imagePath)
    : QGraphicsScene{parent}
{
    currentImage = new QGraphicsPixmapItem();
    currentImage->setPixmap(QPixmap(_imagePath));
    cropRect = nullptr;
    setSceneRect(currentImage->boundingRect());
    addItem(currentImage);
}

CropperScene::~CropperScene()
{
    delete currentImage;
    delete cropRect;
}

void CropperScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    lastPressedMouseButton = event->button();

    if(lastPressedMouseButton != Qt::MouseButton::LeftButton)
        return;

    prevMousePos = event->scenePos();

    if(cropRect && cropRect->contains(prevMousePos))
    {
        rectSelected = true;
    }
    else
    {
        if(cropRect)
        {
            removeItem(cropRect);
            delete cropRect;
        }

        cropRect = new QGraphicsRectItem();
        cropRect->setRect(prevMousePos.x(), prevMousePos.y(), 0, 0);
        cropRect->setBrush(QBrush(QColor(158,182,255,96)));
        cropRect->setPen(QPen(QColor(158,182,255,200),1));
        addItem(cropRect);
    }

    QGraphicsScene::mousePressEvent(event);
}

void CropperScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(lastPressedMouseButton != Qt::LeftButton)
       return;

    QPointF delta = event->scenePos() - prevMousePos;
    QRect currentRect = cropRect->boundingRect().toRect();


    if(rectSelected)
    {
        if(currentRect.x() + delta.x() <= 1 ||
            currentRect.x() + currentRect.width() + delta.x() >= currentImage->boundingRect().width() - 1 ||
            currentRect.y() + delta.y() <= 1 ||
            currentRect.y() + currentRect.height() + delta.y() >= currentImage->boundingRect().height() - 1)
        {
            return;
        }

        cropRect->setRect(currentRect.x() + delta.x(), currentRect.y() + delta.y(), cropRect->rect().width(), cropRect->rect().height());
        prevMousePos = event->scenePos();
    }
    else
    {
       int maxSizeDelta = qMax( qAbs(delta.x()), qAbs(delta.y()) );
       cropRect->setRect(currentRect.x(), currentRect.y(), maxSizeDelta, maxSizeDelta);
    }

    QGraphicsScene::mouseMoveEvent(event);
}

void CropperScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    rectSelected = false;
    QRectF previewRect = cropRect->boundingRect();
    emit sendPreview(currentImage->pixmap().copy(previewRect.toRect()));

    QGraphicsScene::mouseReleaseEvent(event);
}
