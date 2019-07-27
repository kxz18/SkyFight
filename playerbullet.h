#ifndef PLAYERBULLET_H
#define PLAYERBULLET_H
#include "abstractbullet.h"
#include "global.h"

class PlayerBullet : public AbstractBullet
{
    Q_OBJECT
public:
    PlayerBullet(QPointF pos,QGraphicsScene *scene);
    virtual ~PlayerBullet() override;
    virtual QString name()override;
    virtual void advance(int phase) override;
};

#endif // PLAYERBULLET_H
