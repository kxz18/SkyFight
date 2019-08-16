#include "senemyplane.h"

sEnemyPlane::sEnemyPlane(QGraphicsScene *scene, QPointF pos) :
    AbstractPlane(SENEMYPLANEWIDTH,SENEMYPLANEHEIGHT,SENEMYPLANESPEED,
                  pos,QPixmap(sEnemyPlaneImage),scene,SENEMYPLANEBLOOD){
    qDebug("A small enemy plane created @ %p",static_cast<void*>(this));
}

sEnemyPlane::~sEnemyPlane(){
    qDebug("A small enemy plane deleted @ %p",static_cast<void*>(this));
}

QString sEnemyPlane::name()
{
    return "sEnemyPlane";
}

int sEnemyPlane::score()
{
    return 1;
}

void sEnemyPlane::checkCollide()
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

void sEnemyPlane::advance(int)
{
    frames++;
    QPointF cur=this->scenePos();
    cur.ry()+=SENEMYPLANESPEED;
    this->setPos(cur);
    if((frames*UPDATEFREQUENCY)%SEBFREQUENCY==0)
        emit shoot();
    checkCollide();
}

