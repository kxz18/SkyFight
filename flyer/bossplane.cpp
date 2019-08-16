#include "bossplane.h"

BossPlane::BossPlane(QGraphicsScene *scene,QPointF pos) :
    AbstractPlane(BOSSPLANEWIDTH,BOSSPLANEHEIGHT,BOSSPLANESPEED,
                  pos,QPixmap(bossPlaneImage),scene,BOSSPLANEBLOOD),
    w(false),a(false),s(false),d(false){
    qDebug("A boss plane created @ %p",static_cast<void*>(this));
}

BossPlane::~BossPlane(){
    qDebug("A boss plane deleted @ %p",static_cast<void*>(this));
}

QString BossPlane::name()
{
    return "bossPlane";
}

int BossPlane::score()
{
    return 20;
}

void BossPlane::checkCollide()
{
    foreach(QGraphicsItem *it, this->collidingItems())
    {
        AbstractFlyer *flyer=static_cast<AbstractFlyer*>(it);
        if(flyer->name()=="player_plane")
            crashWithPlane(static_cast<AbstractPlane*>(flyer));
        else if(flyer->name()=="playerBullet"){
            this->crashed();
            flyer->crashed();//crash the bullet as well
        }
    }
}

bool BossPlane::checkPos(QString direction)
{
    bool in=true;
    if(direction=="up"&&this->scenePos().ry()<=0)
        in=false;
    else if(direction=="down"&&this->scenePos().ry()>=SCENEHEIGHT/2-height)
        in=false;
    else if(direction=="left"&&this->scenePos().rx()<=0)
        in=false;
    else if(direction=="right"&&this->scenePos().rx()>=SCENEWIDTH-width)
        in=false;
    return in;
}

void BossPlane::advance(int)
{
    frames++;
    checkCollide();
    if((frames*UPDATEFREQUENCY)%10000==0)//random a direction, 0,1,2,3 means different direction,4 means halting
    {
        w=false;a=false;s=false;d=false;
        int ranDirct=Randomer::RndInt(4);
        switch (ranDirct) {
        case 0: w=true;break;
        case 1: s=true;break;
        case 2: a=true;break;
        case 3: d=true;break;
        default:break;
        }
        if(!checkPos("up"))//prevent boss from not coming out
        {
            s=true;
            w=false;
        }
    }
    QPointF cur=this->scenePos();
    if(w||!checkPos("down"))//up
        cur.ry()-=BOSSPLANESPEED;
    if(s||!checkPos("up"))//down
        cur.ry()+=BOSSPLANESPEED;
    if(a||!checkPos("right"))//left
        cur.rx()-=BOSSPLANESPEED;
    if(d||!checkPos("left"))//right
        cur.rx()+=BOSSPLANESPEED;
    this->setPos(cur);
    if((frames*UPDATEFREQUENCY)%BEB1FREQUENCY==0)
        emit shootEB1();
    if((frames*UPDATEFREQUENCY)%BEB2FREQUENCY==0)
        emit shootEB2();
}
