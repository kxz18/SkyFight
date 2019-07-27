#include "abstractplane.h"

AbstractPlane::AbstractPlane(qreal w,qreal h,qreal spd,QPointF pos,QPixmap pic,QGraphicsScene *scene,int bld)
    : AbstractFlyer(w,h,spd,pos,pic,scene),blood(bld),frames(0){}

AbstractPlane::~AbstractPlane(){}

void AbstractPlane::crashed()
{
    qDebug()<<this->name()<<"crashed";

    blood--;
    emit bloodChange(blood);
    if(blood==0)
        emit planeDestroyed(this);
    emit planeCrashed(this);
}

void AbstractPlane::crashWithPlane(AbstractPlane* object)
{
    object->crashed();
    this->crashed();
}
