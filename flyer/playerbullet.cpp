#include "playerbullet.h"

PlayerBullet::PlayerBullet(QPointF pos,QGraphicsScene *scene) :
    AbstractBullet(PLAYERBULLETWIDTH,PLAYERBULLETHEIGHT,PLAYERBULLETSPEED,
                   pos,QPixmap(playerBulletImage),scene){}

PlayerBullet::~PlayerBullet(){}

QString PlayerBullet::name()
{
    return "playerBullet";
}

void PlayerBullet::advance(int)
{
    checkCollide();
    QPointF cur=this->scenePos();
    cur.ry()-=speed;
    this->setPos(cur);
}
