#ifndef ABSTRACTPLANE_H
#define ABSTRACTPLANE_H
#include "abstractflyer.h"

class AbstractPlane : public AbstractFlyer
{
    Q_OBJECT
protected:
    int blood,frames;
public:
    AbstractPlane(qreal w,qreal h,qreal spd,QPointF pos,QPixmap pic,QGraphicsScene *scene,int bld);
    virtual ~AbstractPlane() override;
    virtual QString name() override =0;
    virtual void checkCollide() override =0;
    virtual void crashed() override;
    virtual void crashWithPlane(AbstractPlane *object);//result of collide will be record by the one who has more blood to prevent player from colliding with one dying and not losing blood
    virtual int score() override =0;

signals:
    void planeCrashed(AbstractPlane* plane);//has a collide
    void planeDestroyed(AbstractPlane* plane);//K.O.
    void planeDisappear(AbstractPlane* plane);//out of the scene
    void bloodChange(int blood);
};

#endif // ABSTRACTPLANE_H
