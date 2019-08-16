#include "abstractflyer.h"

AbstractFlyer::AbstractFlyer(qreal w,qreal h,qreal spd,QPointF pos,QPixmap pic,QGraphicsScene *scene) :
    width(w),height(h),speed(spd),position(pos)
{
    QPixmap revised=pic.scaled(int(width),int(height),Qt::KeepAspectRatio);
    this->setPixmap(revised);
    this->setPos(pos);
    scene->addItem(this);
}

AbstractFlyer::~AbstractFlyer(){}

qreal AbstractFlyer::getWidth() const
{
    return width;
}

qreal AbstractFlyer::getHeight() const
{
    return height;
}

bool AbstractFlyer::checkPos(QString direction)
{
    bool in=true;
    if(direction=="up"&&this->scenePos().ry()<=0)
        in=false;
    else if(direction=="down"&&this->scenePos().ry()>=SCENEHEIGHT-height)
        in=false;
    else if(direction=="left"&&this->scenePos().rx()<=0)
        in=false;
    else if(direction=="right"&&this->scenePos().rx()>=SCENEWIDTH-width)
        in=false;
    return in;
}
