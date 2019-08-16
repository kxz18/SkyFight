#ifndef ABSTRACTBULLET_H
#define ABSTRACTBULLET_H
#include "abstractflyer.h"

class AbstractBullet : public AbstractFlyer
{
    Q_OBJECT

protected:
    QPointF target;//destination

public:
    AbstractBullet(qreal w,qreal h,qreal spd,QPointF pos,QPixmap pic,QGraphicsScene *scene,QPointF tar=QPointF(0,0)) :
        AbstractFlyer(w,h,spd,pos,pic,scene),target(tar){}
    virtual ~AbstractBullet() override{}
    virtual QString name() override =0;
    virtual int score() override{
        return 0;
    }
    virtual void checkCollide() override//bullet don't do check, or it will not disappear upon destroy a plane
    {
        if(!(checkPos("up")&&checkPos("down")&&
             checkPos("left")&&checkPos("right")))
            this->crashed();
    }
    virtual void crashed() override
    {
        emit bulletCrashed(this);
    }

signals:
    void bulletCrashed(AbstractBullet *bullet);
};



#endif // ABSTRACTBULLET_H
