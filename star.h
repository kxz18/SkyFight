#ifndef STAR_H
#define STAR_H
#include "abstractsupply.h"

class Star : public AbstractSupply
{
    Q_OBJECT

public:
    Star(QGraphicsScene *scene, QPointF pos);
    virtual ~Star() override;
    virtual QString name() override;
    virtual int score() override;
    virtual void advance(int) override;
};

#endif // STAR_H
