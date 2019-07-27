#ifndef ABSTRACTSUPPLY_H
#define ABSTRACTSUPPLY_H
#include "abstractflyer.h"

class AbstractSupply : public AbstractFlyer
{
    Q_OBJECT

public:
    AbstractSupply(qreal w,qreal h,qreal spd,QPointF pos,QPixmap pic,QGraphicsScene *scene) :
        AbstractFlyer(w,h,spd,pos,pic,scene){}
    ~AbstractSupply(){}
    virtual QString name()=0;
    virtual int score()=0;
    virtual void checkCollide()//supply don't do check, or it will not disappear upon destroy a plane
    {
        if(!(checkPos("up")&&checkPos("down")&&
             checkPos("left")&&checkPos("right")))
            this->crashed();
    }
    virtual void crashed()
    {
        emit supplyCrashed(this);
    }

signals:
    void supplyCrashed(AbstractSupply *supply);
};

#endif // ABSTRACTSUPPLY_H
