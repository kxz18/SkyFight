#ifndef BULLETFACTORY_H
#define BULLETFACTORY_H
#include <QObject>
#include "playerbullet.h"
#include "enemybullet1.h"
#include "enemybullet2.h"
#include "abstractplane.h"
#include "global.h"

class BulletFactory : public QObject
{
    Q_OBJECT

protected:
    QGraphicsScene *scene;
    QList<PlayerBullet*> playerBullets;
    QList<EnemyBullet1*> enemyBullet1s;
    QList<EnemyBullet2*> enemyBullet2s;

public:
    BulletFactory(QGraphicsScene *scn);
    ~BulletFactory();
    void deleteFromList(AbstractBullet* bullet);            //delete disappeared bullet from list
    template<class T>
    void delTemp(QList<T*> &list,AbstractBullet* bullet);   //used in deleteFromList
    QList<PlayerBullet*>* PBList();                         //return list of player's bullet
    QList<EnemyBullet1*>* EB1List();                        //return list of enemy's bullet 1
    QList<EnemyBullet2*>* EB2List();                        //return list of enemy's bullet 2
    void clear();

private slots:
    PlayerBullet* createPB(QPointF pos);//must know where the player is
    EnemyBullet1* createEB1(AbstractPlane *shooter,QPointF tar);
    EnemyBullet2* createEB2(AbstractPlane *shooter);
    void on_bulletCrashed(AbstractBullet *bullet);
};


#endif // BULLETFACTORY_H
