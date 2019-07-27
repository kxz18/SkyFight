#include "star.h"

Star::Star(QGraphicsScene *scene, QPointF pos) :
    AbstractSupply(STARWIDTH,STARHEIGHT,BGMOVESPEED,
                  pos,QPixmap(starImage),scene){}

Star::~Star(){
    qDebug()<<"star deleted";
}

QString Star::name(){
    return "star";
}

int Star::score(){
    return 2;
}

void Star::advance(int)
{
    QPointF cur=this->scenePos();
    cur.ry()+=speed;
    this->setPos(cur);
}
