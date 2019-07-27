#ifndef SUPPLYFACTORY_H
#define SUPPLYFACTORY_H
#include <QObject>
#include <QGraphicsScene>
#include "star.h"
#include "abstractplane.h"
#include "randomer.h"

class SupplyFactory : public QObject
{
    Q_OBJECT

protected:
    QGraphicsScene *scene;
    QList<Star*> stars;

public:
    SupplyFactory(QGraphicsScene *scn);
    ~SupplyFactory();
    void deleteFromList(AbstractSupply* supply);            //delete disappeared supply from list
    template<class T>
    void delTemp(QList<T*> &list,AbstractSupply* supply);   //used in deleteFromList
    QList<Star*>* StarList();
    void clear();

private slots:
    void fore_createStar(AbstractPlane* plane);//who to drop a star
    Star* createStar(QPointF pos);
    void on_supplyCrashed(AbstractSupply *supply);
};

#endif // SUPPLYFACTORY_H
