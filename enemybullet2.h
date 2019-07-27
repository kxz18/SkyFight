#ifndef ENEMYBULLET2_H
#define ENEMYBULLET2_H
#include "abstractbullet.h"

class EnemyBullet2 : public AbstractBullet
{
    Q_OBJECT

public:
    EnemyBullet2(QPointF pos,QGraphicsScene *scene);
    virtual ~EnemyBullet2() override;
    virtual QString name()override;
    virtual void advance(int phase) override;
};

#endif // ENEMYBULLET2_H
