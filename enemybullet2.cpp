#include "enemybullet2.h"

EnemyBullet2::EnemyBullet2(QPointF pos,QGraphicsScene *scene) :
    AbstractBullet(ENEMYBULLET2WIDTH,ENEMYBULLET2HEIGHT,ENEMYBULLET2SPEED,
                   pos,QPixmap(enemyBullet2Image),scene){}

EnemyBullet2::~EnemyBullet2(){}

QString EnemyBullet2::name()
{
    return "enemyBullet2";
}

void EnemyBullet2::advance(int)
{
    checkCollide();
    QPointF cur=this->scenePos();
    cur.ry()+=speed;
    this->setPos(cur);
}
