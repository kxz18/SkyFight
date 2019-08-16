#ifndef MENEMYPLANE_H
#define MENEMYPLANE_H
#include "abstractplane.h"

class mEnemyPlane : public AbstractPlane
{
    Q_OBJECT
public:
    mEnemyPlane(QGraphicsScene *scene, QPointF pos);
    virtual ~mEnemyPlane() override;
    virtual QString name() override;
    virtual int score() override;
    virtual void checkCollide() override;
    virtual void advance(int) override;

signals:
    void shoot();
};


#endif // MENEMYPLANE_H
