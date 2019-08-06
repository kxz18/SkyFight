#ifndef ENEMYBULLET1_H
#define ENEMYBULLET1_H
#include "abstractbullet.h"

class EnemyBullet1 : public AbstractBullet
{
    Q_OBJECT

protected:
    qreal deltaX,deltaY;//used to locate path between start point and target

public:
    EnemyBullet1(QPointF pos,QGraphicsScene *scene,QPointF tar=QPointF(0,0));
    virtual ~EnemyBullet1() override;
    virtual QString name()override;
    virtual void advance(int phase) override;
};

#endif // ENEMYBULLET1_H
