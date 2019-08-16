#ifndef SENEMYPLANE_H
#define SENEMYPLANE_H
#include "abstractplane.h"

class sEnemyPlane : public AbstractPlane
{
    Q_OBJECT

public:
    sEnemyPlane(QGraphicsScene *scene, QPointF pos);
    virtual ~sEnemyPlane() override;
    virtual QString name() override;
    virtual int score() override;
    virtual void checkCollide() override;
    virtual void advance(int) override;

signals:
    void shoot();
};

#endif // SENEMYPLANE_H
