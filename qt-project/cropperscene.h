#ifndef CROPPERSCENE_H
#define CROPPERSCENE_H

#include <QGraphicsScene>

class QGraphicsPixmapItem;
class QGraphicsRectItem;

class CropperScene : public QGraphicsScene
{
    Q_OBJECT

    QGraphicsPixmapItem* currentImage;
    QGraphicsRectItem* cropRect;
    QPointF prevMousePos;
    Qt::MouseButton lastPressedMouseButton;
    bool rectSelected;

public:
    explicit CropperScene(QObject *parent, const QString& _imagePath);
    ~CropperScene();

    // QGraphicsScene interface

signals:
    void sendPreview(const QPixmap& _preview);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // CROPPERSCENE_H
