#ifndef RECORDER_NEW_H
#define RECORDER_NEW_H
#include <QObject>
#include <QList>
#include <fstream>
#include <QFileDialog>
#include "replayer_new.h"
#include "planefactory.h"
#include "bulletfactory.h"
#include "supplyfactory.h"
#include "global.h"

class recorder_new : public QObject
{
    Q_OBJECT
protected://#include "space.h"
    int frames;
    QString filePath;//record files' directory
    std::fstream file;
    QHash<QString,QHash<int,QList<QPointF>>> allFrames;//store all the image
    replayer_new *replayer;//media player
    PlaneFactory *planeFactory;
    BulletFactory *bulletFactory;
    SupplyFactory *supplyFactory;

    recorder_new() : frames(0),filePath(recordFilePath),allFrames(),
                     planeFactory(nullptr),bulletFactory(nullptr),
                     supplyFactory(nullptr)
    {
        qDebug()<<"initializing recorder_new";

        replayer=new replayer_new();
    }
    ~recorder_new(){
        delete replayer;
    }

public:
    recorder_new(const recorder_new&)=delete;
    recorder_new(recorder_new&&)=delete;
    static recorder_new& instance(){
        static recorder_new instance;
        return instance;
    }

    void setPlaneFactory(PlaneFactory *tmp)
    {
        planeFactory=tmp;
    }

    void setBulletFactory(BulletFactory *tmp)
    {
        bulletFactory=tmp;
    }

    void setSupplyFactory(SupplyFactory *tmp)
    {
        supplyFactory=tmp;
    }

    void setFilePath(const QString &name)
    {
        replayer->setFilePath(name);
    }

    void startRecord(QString file_path){
        this->filePath=file_path;
        allFrames.clear();
        frames=0;

        QDir dir;
        if(!dir.exists(file_path)) dir.mkdir(file_path);//create a record path

        QString fileName=filePath+QTime::currentTime().toString()+".record";
        file.open(fileName.toStdString(),std::ios::out);
    }
    void finishRecord(){
        file<<"###"<<std::endl;     //complete signal
        if(planeFactory->ifVictory())
            file<<"Win!!";
        else file<<"Lose!";
        file.close();
    }

    void replay(){
        replayer->start();
        replayer->exec();
    }

    void writePos(const QList<QPointF> &list){
        foreach(auto it,list){
            file<<"("<<it.x()<<","<<it.y()<<") ";
        }
        file<<"#"<<std::endl;
    }

private slots:
    void takeCapture(){
        frames++;
        file<<"[\n"<<frames<<std::endl;

        foreach(auto name, planeKeyWords){
            file<<name.toStdString()<<std::endl;
            writePos(planeFactory->allPos(name));
        }

        foreach(auto name, bulletKeyWords){
            file<<name.toStdString()<<std::endl;
            writePos(bulletFactory->allPos(name));
        }

        foreach(auto name, supplyKeyWords){
            file<<name.toStdString()<<std::endl;
            writePos(supplyFactory->allPos(name));
        }

        file<<"]"<<std::endl;
    }
};

#endif // RECORDER_NEW_H
