#include "enemybullet1.h"

EnemyBullet1::EnemyBullet1(QPointF pos,QGraphicsScene *scene,QPointF tar) :
    AbstractBullet(ENEMYBULLET1WIDTH,ENEMYBULLET1HEIGHT,ENEMYBULLET1SPEED,
                   pos,QPixmap(enemyBullet1Image),scene,tar)
{
    deltaX=tar.rx()-pos.rx();
    deltaY=tar.ry()-pos.ry();
}

EnemyBullet1::~EnemyBullet1(){}

QString EnemyBullet1::name()
{
    return "enemyBullet1";
}

void EnemyBullet1::advance(int)
{
    checkCollide();
    QPointF cur=this->scenePos();
    qreal hypo=sqrt(pow(deltaX,2)+pow(deltaY,2));
    cur.rx()+=speed/hypo*deltaX;
    cur.ry()+=speed/hypo*deltaY;
    this->setPos(cur);
}
