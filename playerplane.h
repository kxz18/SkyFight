#ifndef PLAYERPLANE_H
#define PLAYERPLANE_H
#include "abstractplane.h"
#include "abstractsupply.h"
#include "global.h"

class PlayerPlane : public AbstractPlane
{
    Q_OBJECT

    friend class Space;

protected:
    bool w,a,s,d,shooting,victory;//judge if it is moving or shooting
    int scores,level;          //frames means frames endured
public:
    PlayerPlane(QGraphicsScene *scene);
    PlayerPlane(QGraphicsScene *scene,QPointF pos);
    virtual ~PlayerPlane() override;
    virtual QString name() override;
    virtual int score() override;
    virtual void checkCollide() override;
    virtual void advance(int) override;
    void refresh();//all parameter changed to the default
    bool ifVictory();

    void up();//for API
    void down();
    void left();
    void right();
    void shoot();
    void stopMove();

signals:
    void shoot(QPointF pos);
    void phaseChange(int level);
    void killBoss(AbstractPlane *killer);
    void scoreChange(int score);

private slots:
    void getScore(AbstractPlane* enemy);//scores from killing enemy
    void getScoreFromSupply(AbstractSupply* supply);
};

#endif // PLAYERPLANE_H
