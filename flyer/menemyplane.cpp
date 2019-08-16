#include "menemyplane.h"

mEnemyPlane::mEnemyPlane(QGraphicsScene *scene, QPointF pos) :
    AbstractPlane(MENEMYPLANEWIDTH,MENEMYPLANEHEIGHT,MENEMYPLANESPEED,
                  pos,QPixmap(mEnemyPlaneImage),scene,MENEMYPLANEBLOOD){
    qDebug("A middle enemy plane created @ %p",static_cast<void*>(this));
}

mEnemyPlane::~mEnemyPlane(){
    qDebug("A middle enemy plane deleted @ %p",static_cast<void*>(this));
}

QString mEnemyPlane::name()
{
    return "mEnemyPlane";
}

int mEnemyPlane::score()
{
    return 2;
}

void mEnemyPlane::checkCollide()
{
    foreach(QGraphicsItem *it, this->collidingItems())
    {
        AbstractFlyer *flyer=static_cast<AbstractFlyer*>(it);
        if(flyer->name()=="playerBullet"){
            this->crashed();
            flyer->crashed();//crash the bullet as well
        }
    }
    if(this->scenePos().y()>=SCENEHEIGHT)
        emit planeDisappear(this);
}

void mEnemyPlane::advance(int)
{
    frames++;
    QPointF cur=this->scenePos();
    cur.ry()+=speed;
    this->setPos(cur);
    if((frames*UPDATEFREQUENCY)%MEBFREQUENCY==0)
        emit shoot();
    if(cur.y()>0)
        checkCollide();
}

