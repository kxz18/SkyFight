#include "bulletfactory.h"

BulletFactory::BulletFactory(QGraphicsScene *scn) :
    scene(scn), playerBullets(),enemyBullet1s(),enemyBullet2s(){}

BulletFactory::~BulletFactory()
{
    qDeleteAll(playerBullets);
    qDeleteAll(enemyBullet1s);
    qDeleteAll(enemyBullet2s);
}

QList<PlayerBullet*>* BulletFactory::PBList()
{
    return &(this->playerBullets);
}

QList<EnemyBullet1*>* BulletFactory::EB1List()
{
    return &(this->enemyBullet1s);
}

QList<EnemyBullet2*>* BulletFactory::EB2List()
{
    return &(this->enemyBullet2s);
}

void BulletFactory::clear(){

    qDebug()<<"playerBullets"<<playerBullets.count();
    foreach(auto it, playerBullets){
        scene->removeItem(it);
        it->deleteLater();
    }
    playerBullets.clear();

    qDebug()<<"enemyBullet1s"<<enemyBullet1s.count();
    foreach(auto it, enemyBullet1s){
        scene->removeItem(it);
        it->deleteLater();
    }
    enemyBullet1s.clear();

    qDebug()<<"enemyBullet2s"<<enemyBullet2s.count();
    foreach(auto it, enemyBullet2s){
        scene->removeItem(it);
        it->deleteLater();
    }
    enemyBullet2s.clear();
}

void BulletFactory::invisible(){
    foreach(auto it, playerBullets) it->setVisible(false);
    foreach(auto it, enemyBullet1s) it->setVisible(false);
    foreach(auto it, enemyBullet2s) it->setVisible(false);
}

void BulletFactory::deleteFromList(AbstractBullet *bullet)
{
    if(bullet->name()=="playerBullet") delTemp<PlayerBullet>(playerBullets,bullet);
    else if(bullet->name()=="enemyBullet1") delTemp<EnemyBullet1>(enemyBullet1s,bullet);
    else if(bullet->name()=="enemyBullet2") delTemp<EnemyBullet2>(enemyBullet2s,bullet);
}

template <class T>
void BulletFactory::delTemp(QList<T*> &list,AbstractBullet *bullet)
{
    foreach(T* it,list){
        if(it==bullet){
            list.removeOne(it);
            break;
        }
    }
}

PlayerBullet* BulletFactory::createPB(QPointF pos)
{
    pos.rx()+=(PLAYERPLANEWIDTH-PLAYERBULLETWIDTH)/2; //revise pos so that bullet comes from middle of plane
    pos.ry()-=PLAYERBULLETHEIGHT;
    PlayerBullet *tmp=new PlayerBullet(pos,scene);
    tmp->setZValue(1);
    this->playerBullets.append(tmp);
    connect(tmp,SIGNAL(bulletCrashed(AbstractBullet*)),this,SLOT(on_bulletCrashed(AbstractBullet*)));
    return tmp;
}

EnemyBullet1* BulletFactory::createEB1(AbstractPlane *shooter,QPointF tar)
{
    QPointF pos=shooter->scenePos();
    pos.rx()+=(shooter->getWidth()-ENEMYBULLET1WIDTH)/2; //revise pos so that bullet comes from middle of plane
    pos.ry()+=shooter->getHeight();
    EnemyBullet1 *tmp=new EnemyBullet1(pos,scene,tar);
    tmp->setZValue(1);
    this->enemyBullet1s.append(tmp);
    connect(tmp,SIGNAL(bulletCrashed(AbstractBullet*)),this,SLOT(on_bulletCrashed(AbstractBullet*)));
    return tmp;
}

EnemyBullet2* BulletFactory::createEB2(AbstractPlane *shooter){
    QPointF pos=shooter->scenePos();
    pos.rx()+=(shooter->getWidth()-ENEMYBULLET2WIDTH)/2; //revise pos so that bullet comes from middle of plane
    pos.ry()+=shooter->getHeight();
    EnemyBullet2 *tmp=new EnemyBullet2(pos,scene);
    tmp->setZValue(1);
    this->enemyBullet2s.append(tmp);
    connect(tmp,SIGNAL(bulletCrashed(AbstractBullet*)),this,SLOT(on_bulletCrashed(AbstractBullet*)));
    return tmp;
}

void BulletFactory::on_bulletCrashed(AbstractBullet *bullet)
{
    scene->removeItem(bullet);
    deleteFromList(bullet);
    bullet->deleteLater();
}
