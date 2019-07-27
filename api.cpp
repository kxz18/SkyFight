#include "api.h"

bool operator< (const Point& a,const Point& b){
    return a.x<b.x;
}

API::API() : playerPlane(nullptr), planeFactory(nullptr),
    bulletFactory(nullptr),supplyFactory(nullptr){}

API::~API(){}

void API::setup(PlayerPlane *plane, PlaneFactory *pf, BulletFactory *bf, SupplyFactory *sf){
    playerPlane=plane;
    planeFactory=pf;
    bulletFactory=bf;
    supplyFactory=sf;
}

API& API::game(){
    static API instance;
    return instance;
}

Point API::player_position(){
    Point pos;
    QPointF tmp=playerPlane->scenePos();
    pos.x=int(tmp.x()+PLAYERPLANEWIDTH/2);
    pos.y=int(tmp.y()+PLAYERPLANEHEIGHT/2);
    return pos;
}

template<class T>
std::set<Point> API::positions(){
    std::set<Point> list;
    return list;
}

template<>
std::set<Point> API::positions<SEP>(){
    std::set<Point> list;
    foreach(SEP* it,*(planeFactory->SEList())){
        Point pos;
        QPointF tmp=it->scenePos();
        pos.x=int(tmp.x()+SENEMYPLANEWIDTH/2);
        pos.y=int(tmp.y()+SENEMYPLANEHEIGHT/2);
        list.insert(pos);
    }
    return list;
}

template<>
std::set<Point> API::positions<MEP>(){
    std::set<Point> list;
    foreach(MEP* it,*(planeFactory->MEList())){
        Point pos;
        QPointF tmp=it->scenePos();
        pos.x=int(tmp.x()+MENEMYPLANEWIDTH/2);
        pos.y=int(tmp.y()+MENEMYPLANEHEIGHT/2);
        list.insert(pos);
    }
    return list;
}

template<>
std::set<Point> API::positions<BP>(){
    std::set<Point> list;
    foreach(BP* it,*(planeFactory->BossList())){
        Point pos;
        QPointF tmp=it->scenePos();
        pos.x=int(tmp.x()+BOSSPLANEWIDTH/2);
        pos.y=int(tmp.y()+BOSSPLANEHEIGHT/2);
        list.insert(pos);
    }
    return list;
}

template<>
std::set<Point> API::positions<EB1>(){
    std::set<Point> list;
    foreach(EB1* it,*(bulletFactory->EB1List())){
        Point pos;
        QPointF tmp=it->scenePos();
        pos.x=int(tmp.x()+ENEMYBULLET1WIDTH/2);
        pos.y=int(tmp.y()+ENEMYBULLET1HEIGHT/2);
        list.insert(pos);
    }
    return list;
}

template<>
std::set<Point> API::positions<EB2>(){
    std::set<Point> list;
    foreach(EB2* it,*(bulletFactory->EB2List())){
        Point pos;
        QPointF tmp=it->scenePos();
        pos.x=int(tmp.x()+ENEMYBULLET2WIDTH/2);
        pos.y=int(tmp.y()+ENEMYBULLET2HEIGHT/2);
        list.insert(pos);
    }
    return list;
}

template<>
std::set<Point> API::positions<PB>(){
    std::set<Point> list;
    foreach(PB* it,*(bulletFactory->PBList())){
        Point pos;
        QPointF tmp=it->scenePos();
        pos.x=int(tmp.x()+PLAYERBULLETWIDTH/2);
        pos.y=int(tmp.y()+PLAYERBULLETHEIGHT/2);
        list.insert(pos);
    }
    return list;
}

template<>
std::set<Point> API::positions<Star>(){
    std::set<Point> list;
    foreach(Star* it,*(supplyFactory->StarList())){
        Point pos;
        QPointF tmp=it->scenePos();
        pos.x=int(tmp.x()+STARWIDTH/2);
        pos.y=int(tmp.y()+STARHEIGHT/2);
        list.insert(pos);
    }
    return list;
}

void API::player_up(){
    playerPlane->up();
}

void API::player_down(){
    playerPlane->down();
}

void API::player_left(){
    playerPlane->left();
}

void API::player_right(){
    playerPlane->right();
}

void API::player_shoot(){
    playerPlane->shoot();
}

void API::AI_control(){
    playerPlane->stopMove();
    your_control_per_frame();
}
