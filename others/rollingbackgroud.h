#ifndef ROLLINGBACKGROUD_H
#define ROLLINGBACKGROUD_H
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QObject>
#include "global.h"

class RollingBackgroud : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

protected:
    QGraphicsScene *scene;
    qreal width,height;

public:
    RollingBackgroud(QGraphicsScene *scn,QPixmap pic=QPixmap(rollingBackgroud)){
        scene=scn;
        width=scene->width();
        height=width/pic.width()*pic.height();
        QPixmap revised=pic.scaled(int(width),int(height),
                            Qt::IgnoreAspectRatio);
        this->setPixmap(revised);
        this->setZValue(-2);
        this->setPos(0,-(this->height-scene->height()));
        scene->addItem(this);
    }
    virtual QPainterPath shape() const override{//when call collideItems(), this function is auto-called, so a rect of 0,0,0,0 means this will never collide with others
        QPainterPath path;
        path.addRect(QRectF(0,0,0,0));
        return path;
    }
    virtual ~RollingBackgroud() override{}
    virtual void advance(int) override
    {
        QPointF cur=this->scenePos();
        if(cur.ry()>=0)
            cur.ry()=-(this->height-scene->height());
        else cur.ry()+=BGMOVESPEED;
        this->setPos(cur);
    }
};

#endif // ROLLINGBACKGROUD_H
