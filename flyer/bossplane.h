#ifndef BOSSPLANE_H
#define BOSSPLANE_H
#include "abstractplane.h"
#include "randomer.h"

class BossPlane : public AbstractPlane
{
    Q_OBJECT

protected:
    bool w,a,s,d;//move direction
public:
    BossPlane(QGraphicsScene *scene,QPointF pos=QPointF(SCENEWIDTH/2-BOSSPLANEWIDTH/2,-BOSSPLANEHEIGHT));//default appear in the up middle
    virtual ~BossPlane() override;
    virtual QString name() override;
    virtual int score() override;
    virtual void checkCollide() override;
    virtual bool checkPos(QString direction) override;//boss can only access up 2/3 of the scene
    virtual void advance(int) override;

signals:
    void shootEB1();
    void shootEB2();
};

#endif // BOSSPLANE_H
