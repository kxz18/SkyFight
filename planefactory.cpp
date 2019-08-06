#include "planefactory.h"

PlaneFactory::PlaneFactory(QGraphicsScene *scn) :
    scene(scn),sEnemyPlanes(),mEnemyPlanes(),bossPlanes(),
    player(nullptr),frames(0),level(1){}

PlaneFactory::~PlaneFactory()//scene is not in the control of plane factory
{
    qDeleteAll(sEnemyPlanes);
    qDeleteAll(mEnemyPlanes);
    qDeleteAll(bossPlanes);
}

void PlaneFactory::setLevel(int lev)
{
    level=lev;
}

void PlaneFactory::setPlayer(PlayerPlane *plyr)
{
    player=plyr;
}

QList<sEnemyPlane*>* PlaneFactory::SEList()
{
    return &(this->sEnemyPlanes);
}

QList<mEnemyPlane*>* PlaneFactory::MEList(){
    return &(this->mEnemyPlanes);
}

QList<BossPlane*>* PlaneFactory::BossList()
{
    return &(this->bossPlanes);
}

QList<QPointF> PlaneFactory::allPos(const QString &type)
{
    QList<QPointF> tmp;
    if(type=="SEP"){
        foreach(auto it,sEnemyPlanes)
            tmp.append(it->scenePos());
    }else if(type=="MEP"){
        foreach(auto it,mEnemyPlanes)
            tmp.append(it->scenePos());
    }else if(type=="BP"){
        foreach(auto it,bossPlanes)
            tmp.append(it->scenePos());
    }else if(type=="PP"){
        tmp.append(player->scenePos());
    }
    return tmp;
}

bool PlaneFactory::ifVictory()
{
    return player->ifVictory();
}

void PlaneFactory::clear(){
    qDebug()<<"sEnemyPlanes"<<sEnemyPlanes.count();
    foreach(auto it,sEnemyPlanes){
        scene->removeItem(it);
        it->deleteLater();
    }
    sEnemyPlanes.clear();

    qDebug()<<"bossPlanes"<<bossPlanes.count();
    foreach(auto it,bossPlanes){
        scene->removeItem(it);
        it->deleteLater();
    }
    bossPlanes.clear();

    qDebug()<<"mEnemyPlanes"<<mEnemyPlanes.count();
    foreach(auto it,mEnemyPlanes){
        scene->removeItem(it);
        it->deleteLater();
    }
    mEnemyPlanes.clear();
}

void PlaneFactory::invisible(){
    foreach(auto it, sEnemyPlanes) it->setVisible(false);
    foreach(auto it, mEnemyPlanes) it->setVisible(false);
    foreach(auto it, bossPlanes) it->setVisible(false);
}

void PlaneFactory::deleteFromList(AbstractPlane* plane){
    if(plane->name()=="sEnemyPlane")
        delTemp<sEnemyPlane>(sEnemyPlanes,plane);
    else if(plane->name()=="mEnemyPlane")
        delTemp<mEnemyPlane>(mEnemyPlanes,plane);
    else if(plane->name()=="bossPlane")
        delTemp<BossPlane>(bossPlanes,plane);
}

template<class T>
void PlaneFactory::delTemp(QList<T*> &list,AbstractPlane *plane){
    foreach(T* it,list)
    {
        if(it==plane){
            list.removeOne(it);
            break;
        }
    }
}

sEnemyPlane* PlaneFactory::createSE(int num)
{
    sEnemyPlane *tmp=nullptr;
    if(this->bossPlanes.count()==0&&this->sEnemyPlanes.count()<=6){//control numbers or the scene will be too crowded
        for(int i=0;i<num;i++){
            bool routeClean=true;//judge if it will collide with others
            int posX=Randomer::RndInt(VIEWWIDTH-SENEMYPLANEWIDTH+1); //random x coordination
            int posY=-SENEMYPLANEHEIGHT;
            tmp=new sEnemyPlane(scene,QPointF(posX,posY));
            for(int j=0;j<100;j++){//set highest trial number
                routeClean=true;
                if(tmp->collidingItems().count()==0){
                    break;
                }else{
                    routeClean=false;
                    posX=Randomer::RndInt(VIEWWIDTH-SENEMYPLANEWIDTH+1);
                    tmp->setX(posX);
                }
            }
            if(routeClean){
                tmp->setZValue(2);
                this->sEnemyPlanes.append(tmp);
                connect(tmp,SIGNAL(planeDestroyed(AbstractPlane*)),this,SLOT(on_planeDestroyed(AbstractPlane*)));
                connect(tmp,SIGNAL(planeDisappear(AbstractPlane*)),this,SLOT(on_planeDisappear(AbstractPlane*)));
                connect(tmp,SIGNAL(shoot()),this,SLOT(on_shootEB1()));
                break;
            }else{
                qDebug()<<"too crowded and failed to create a small enemy plane";

                scene->removeItem(tmp);
                delete tmp;
                tmp=nullptr;
            }
        }
    }
    return tmp;
}

mEnemyPlane* PlaneFactory::createME(int num){//if a bunch of middle enemy planes are created, it will be like a grid
   mEnemyPlane* tmp=nullptr;
   for(int i=0;i<num;i++){
       bool routeClean=true;
       int posX=Randomer::RndInt(VIEWWIDTH-MENEMYPLANEWIDTH+1); //random x coordination
       int posY=-MENEMYPLANEHEIGHT;
       tmp=new mEnemyPlane(scene,QPointF(posX,posY));
       for(int j=0;j<100;j++){//set highest trial number
           routeClean=true;
           foreach(auto it,sEnemyPlanes){//if it will be stopped by small enemy planes
               if(it->scenePos().x()-posX<MENEMYPLANEWIDTH&&
                  it->scenePos().x()-posX>-SENEMYPLANEWIDTH)
                   routeClean=false;
               else continue;
           }
           if(tmp->collidingItems().count()!=0)
               routeClean=false;
           if(!routeClean){
               posX=Randomer::RndInt(VIEWWIDTH-MENEMYPLANEWIDTH+1);
               tmp->setX(posX);
           }
           else break;
       }

       if(routeClean){
           tmp->setZValue(2);
           this->mEnemyPlanes.append(tmp);
           connect(tmp,SIGNAL(planeDestroyed(AbstractPlane*)),this,SLOT(on_planeDestroyed(AbstractPlane*)));
           connect(tmp,SIGNAL(planeDisappear(AbstractPlane*)),this,SLOT(on_planeDisappear(AbstractPlane*)));
           connect(tmp,SIGNAL(shoot()),this,SLOT(on_shootEB2()));
       }else{
           qDebug()<<"too crowded and fail to create a middle enemy plane";

           scene->removeItem(tmp);
           delete tmp;
           tmp=nullptr;
       }
   }
   return tmp;
}

BossPlane* PlaneFactory::createBoss(int num)
{
    BossPlane *tmp=nullptr;
    for(int i=0;i<num;i++){
        tmp=new BossPlane(scene);
        tmp->setZValue(3);
        this->bossPlanes.append(tmp);
        connect(tmp,SIGNAL(planeDestroyed(AbstractPlane*)),this,SLOT(on_planeDestroyed(AbstractPlane*)));
        connect(tmp,SIGNAL(shootEB1()),this,SLOT(on_shootEB1()));
        connect(tmp,SIGNAL(shootEB2()),this,SLOT(on_shootEB2()));
    }
    return tmp;
}

void PlaneFactory::on_planeDestroyed(AbstractPlane *plane)
{
    scene->removeItem(plane);
    deleteFromList(plane);
    emit killEnemy(plane);
    plane->deleteLater();       //if delete here, the game will crash and I don't know why
}

void PlaneFactory::on_planeDisappear(AbstractPlane *plane)
{
    scene->removeItem(plane);
    deleteFromList(plane);
    plane->deleteLater();
}

void PlaneFactory::createEnemy(){
    frames++;                        //advance
    int time=frames*UPDATEFREQUENCY;
    if(level%BOSSCOME==0&&BossList()->count()==0)
        createBoss();
    if((time*level)%SETIMEGAUGE==0&&BossList()->count()==0)
        createSE();
    if((time*level)%METIMEGAUGE==0&&BossList()->count()==0)
        createME();
}

void PlaneFactory::on_shootEB1()
{
    AbstractPlane *sender=static_cast<AbstractPlane*>(QObject::sender());
    emit shootEB1(sender);
}

void PlaneFactory::on_shootEB2()
{
    AbstractPlane *sender=static_cast<AbstractPlane*>(QObject::sender());
    emit shootEB2(sender);
}
