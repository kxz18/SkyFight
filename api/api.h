#ifndef API_H
#define API_H
#include <QObject>
#include <set>
#include "playerplane.h"
#include "planefactory.h"
#include "bulletfactory.h"
#include "supplyfactory.h"
#include "global.h"

class Space;

struct Point{
    int x=0;
    int y=0;
};

typedef sEnemyPlane SEP;
typedef mEnemyPlane MEP;
typedef BossPlane BP;
typedef EnemyBullet1 EB1;
typedef EnemyBullet2 EB2;
typedef PlayerBullet PB;

class API : public QObject
{
    Q_OBJECT

private:
    PlayerPlane* playerPlane;
    PlaneFactory* planeFactory;
    BulletFactory* bulletFactory;
    SupplyFactory* supplyFactory;

    API();
    ~API();

public:
    API(const API&)=delete;
    API(API&&)=delete;
    API& operator= (const API&)=delete;
    API& operator= (API&&)=delete;

    void setup(PlayerPlane* plane,PlaneFactory* pf,BulletFactory* bf,SupplyFactory* sf);

    static API& game();
    Point player_position();
    template<class T>
    std::set<Point> positions();
    void player_up();
    void player_down();
    void player_left();
    void player_right();
    void player_shoot();
    void your_control_per_frame();

private slots:
    void AI_control();
};

#endif // API_H
