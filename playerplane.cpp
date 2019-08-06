#include "playerplane.h"
PlayerPlane::PlayerPlane(QGraphicsScene *scene) :
    AbstractPlane(PLAYERPLANEWIDTH,PLAYERPLANEHEIGHT,PLAYERPLANESPEED,
                  QPointF(scene->width()/2-PLAYERPLANEWIDTH/2,scene->height()-PLAYERPLANEHEIGHT),
                  QPixmap(playerPlaneImage),scene,PLAYERPLANEBLOOD),//the origin is on the left-top
    w(false),a(false),s(false),d(false),shooting(false),victory(false),scores(0),level(1)
{
    qDebug("Player plane created @ %p",static_cast<void*>(this));
}

PlayerPlane::PlayerPlane(QGraphicsScene *scene,QPointF pos) :
    AbstractPlane(PLAYERPLANEWIDTH,PLAYERPLANEHEIGHT,PLAYERPLANESPEED,
                  QPointF(scene->width()/2-PLAYERPLANEWIDTH/2,scene->height()-PLAYERPLANEHEIGHT),
                  QPixmap(playerPlaneImage),scene,PLAYERPLANEBLOOD),//the origin is on the left-top
    w(false),a(false),s(false),d(false),shooting(false),victory(false),scores(0),level(1)
{
    qDebug("Player plane created @ %p",static_cast<void*>(this));
    this->setPos(pos);
}

PlayerPlane::~PlayerPlane(){
    qDebug("player plane deleted @ %p",static_cast<void*>(this));
}

QString PlayerPlane::name(){
    return "player_plane";
}

int PlayerPlane::score()
{
    return scores;
}

void PlayerPlane::checkCollide(){
    foreach(QGraphicsItem *it, this->collidingItems())
    {
        AbstractFlyer *flyer=static_cast<AbstractFlyer*>(it);
        if(flyer->name().contains("Plane")){
            AbstractPlane *plane=static_cast<AbstractPlane*> (flyer);
            this->crashWithPlane(plane);
        }else if(flyer->name().contains("enemyBullet")){
            if(this->blood>1)flyer->crashed();
            this->crashed();
        }else if(flyer->name()=="star"){
            AbstractSupply *supply=static_cast<AbstractSupply*>(flyer);
            getScoreFromSupply(supply);
            flyer->crashed();
        }
    }
}

void PlayerPlane::advance(int){
    frames++;
    if(w&&checkPos("up")){
        QPointF cur=this->scenePos();
        cur.ry()-=speed;
        this->setPos(cur);
    }
    if(s&&checkPos("down")){
        QPointF cur=this->scenePos();
        cur.ry()+=speed;
        this->setPos(cur);
    }
    if(a&&checkPos("left")){
        QPointF cur=this->scenePos();
        cur.rx()-=speed;
        this->setPos(cur);
    }
    if(d&&checkPos("right")){
        QPointF cur=this->scenePos();
        cur.rx()+=speed;
        this->setPos(cur);
    }
    if(shooting&&(frames*UPDATEFREQUENCY)%PBFREQUENCY==0) //frames*updatefrequency is the time the plane has endured
        emit shoot(this->scenePos());
    checkCollide();
}

void PlayerPlane::refresh()
{
    qDebug()<<"Player plane refreshed";

    w=false;a=false;
    s=false;d=false;
    shooting=false;victory=false;
    scores=0;level=1;blood=PLAYERPLANEBLOOD;
    this->setPos(this->scene()->width()/2-PLAYERPLANEWIDTH/2,
                 this->scene()->height()-PLAYERPLANEHEIGHT);
}

bool PlayerPlane::ifVictory()
{
    return victory;
}

void PlayerPlane::getScore(AbstractPlane* enemy)
{
    scores+=enemy->score();
    emit scoreChange(scores);
    if(scores/DIFFICULTYUP==level)         //increase difficulty level when scores gets higher
        emit phaseChange(++level);
    if(enemy->name()=="bossPlane")
    {
        victory=true;
        emit killBoss(this);
    }
}

void PlayerPlane::getScoreFromSupply(AbstractSupply* supply)//these two functions are the result of my mistake thinking
{
    scores+=supply->score();
    emit scoreChange(scores);
    if(scores/DIFFICULTYUP==level)
        emit phaseChange(++level);
    if(supply->name()=="bossPlane")
    {
        victory=true;
        emit killBoss(this);
    }
}

void PlayerPlane::up()
{
    w=true;
}

void PlayerPlane::down()
{
    s=true;
}

void PlayerPlane::left()
{
    a=true;
}

void PlayerPlane::right()
{
    d=true;
}

void PlayerPlane::shoot()
{
    shooting=true;
}

void PlayerPlane::stopMove(){
    w=false;
    s=false;
    a=false;
    d=false;
    shooting=false;
}
