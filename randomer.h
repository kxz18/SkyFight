#ifndef RANDOMER_H
#define RANDOMER_H
#include <QObject>
#include <ctime>

class Randomer : public QObject //create random value
{
    Q_OBJECT

protected:
    Randomer(){
        qsrand(time(NULL));     //initialize seed using current time
    }
    ~Randomer(){}

public:
    Randomer(const Randomer&)=delete;
    Randomer(Randomer&&)=delete;
    static int RndInt(int max)
    {
        static Randomer instance;   //singleton, make sure everygame only initialize seed once. since a regular time gauge to initialize seed will make regular random int series
        return qrand()%max;
    }
};

#endif // RANDOMER_H
