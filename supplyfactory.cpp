#include "supplyfactory.h"

SupplyFactory::SupplyFactory(QGraphicsScene *scn) :
    scene(scn), stars(){}

SupplyFactory::~SupplyFactory()
{
    qDeleteAll(stars);
}

QList<Star*>* SupplyFactory::StarList()
{
    return &(this->stars);
}

void SupplyFactory::clear()
{
    qDebug()<<"stars"<<stars.count();
    foreach(auto it, stars){
        scene->removeItem(it);
        it->deleteLater();
    }
    stars.clear();
}

void SupplyFactory::deleteFromList(AbstractSupply *supply)
{
    if(supply->name()=="star") delTemp<Star>(stars,supply);
}

template <class T>
void SupplyFactory::delTemp(QList<T*> &list,AbstractSupply *supply)
{
    foreach(T* it,list){
        if(it==supply){
            list.removeOne(it);
            break;
        }
    }
}

void SupplyFactory::fore_createStar(AbstractPlane* plane){
    if(Randomer::RndInt(100)<100*STARBASICDROP){
        QPointF pos=plane->scenePos();
        pos.rx()+=plane->getWidth()/2; //revise pos so that star comes from middle of plane
        pos.ry()+=plane->getHeight()/2;
        createStar(pos);
    }
}

Star* SupplyFactory::createStar(QPointF pos)
{
    pos.rx()-=STARWIDTH/2;
    pos.ry()-=STARHEIGHT/2;
    Star *tmp=new Star(scene,pos);
    this->stars.append(tmp);
    connect(tmp,SIGNAL(supplyCrashed(AbstractSupply*)),this,SLOT(on_supplyCrashed(AbstractSupply*)));
    return tmp;
}


void SupplyFactory::on_supplyCrashed(AbstractSupply *supply)
{
    scene->removeItem(supply);
    deleteFromList(supply);
    supply->deleteLater();
}
