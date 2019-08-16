#ifndef PLANEFACTORY_H
#define PLANEFACTORY_H
#include <QObject>
#include "senemyplane.h"
#include "menemyplane.h"
#include "bossplane.h"
#include "global.h"
#include "randomer.h"
#include "playerplane.h"
#include "bulletfactory.h"

class PlaneFactory : public QObject
{
    Q_OBJECT

protected:
    QGraphicsScene *scene;
    QList<sEnemyPlane*> sEnemyPlanes;
    QList<mEnemyPlane*> mEnemyPlanes;
    QList<BossPlane*> bossPlanes;
    PlayerPlane *player;
    int frames,level;

public:
    PlaneFactory(QGraphicsScene *scene);
    ~PlaneFactory();
    void setLevel(int lev);
    void setPlayer(PlayerPlane *plyr);
    void deleteFromList(AbstractPlane *plane);
    template<class T>
    void delTemp(QList<T*> &list,AbstractPlane *plane);
    QList<sEnemyPlane*>* SEList();
    QList<mEnemyPlane*>* MEList();
    QList<BossPlane*>* BossList();
    QList<QPointF> allPos(const QString &type);
    bool ifVictory();
    void clear();
    void invisible();

signals:
    void killEnemy(AbstractPlane *enemy);
    void shootEB1(AbstractPlane *plane);
    void shootEB2(AbstractPlane *plane);

private slots:
    sEnemyPlane* createSE(int num=1);//create small enemy plane, "num" means the number of planes
    mEnemyPlane* createME(int num=1);//create middle enemy plane
    BossPlane* createBoss(int num=1);//create boss
    void createEnemy();//the console for create normal kind enemy plane
    void on_planeDestroyed(AbstractPlane* plane);
    void on_planeDisappear(AbstractPlane* plane);//out of scene
    void on_shootEB1();
    void on_shootEB2();
};


#endif // PLANEFACTORY_H
