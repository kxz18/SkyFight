#ifndef ABSTRACTFLYER_H
#define ABSTRACTFLYER_H
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QtWidgets>
#include "global.h"

class AbstractFlyer : public QObject, public QGraphicsPixmapItem //QGraphicsPixmapItem is not a QObject,so it should inherit QObject, and mind the inheriting order
{
    Q_OBJECT
protected:
    qreal width,height,speed;
    QPointF position;

public:
    AbstractFlyer(qreal w,qreal h,qreal spd,QPointF pos,QPixmap pic,QGraphicsScene *scene);
    virtual ~AbstractFlyer();
    qreal getWidth() const;
    qreal getHeight() const;
    virtual QString name()=0;
    virtual int score()=0;
    virtual void checkCollide()=0;
    virtual void crashed()=0;//when has a collide, this function is called and will reduce blood and emit signals
    virtual bool checkPos(QString direction);
};

#endif // ABSTRACTFLYER_H
