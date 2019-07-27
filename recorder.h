#ifndef RECORDER_H
#define RECORDER_H
#include <QObject>
#include <QScreen>
#include <QApplication>
#include <QPixmap>
#include <QDesktopWidget>
#include <QBuffer>
#include <QDir>
#include "global.h"
#include "replayer.h"
#include "avilib.h"

class Recorder : public QObject
{
    Q_OBJECT

protected:
    int frames;
    QRect rect;//print screen area
    QWidget* object;//printed object
    QString filePath;//record files' directory
    avi_t* file;//avi file path and name
    QHash<QString,QPixmap> allFrames;//store all the image
    Replayer *replayer;//media player

    Recorder(QWidget *obj=nullptr) : frames(0),
        rect(0,0,-1,-1),object(obj),filePath("./record/"),
        file(nullptr),allFrames(){

        qDebug()<<"initializing recorder";

        QDir dir(filePath+"_cache/");
        if(dir.exists()){
            foreach(QFileInfo it,dir.entryInfoList()){
                if(it.suffix()=="jpg")
                    allFrames[it.fileName()]=QPixmap(it.filePath());
            }
        }

        replayer=new Replayer(&allFrames);
    }
    ~Recorder(){
        delete file;
        delete replayer;
    }

public:
    Recorder(const Recorder&)=delete;
    Recorder(Recorder&&)=delete;
    static Recorder& instance(){
        static Recorder instance;
        return instance;
    }
    void setWidget(QWidget *obj){
        this->object=obj;
    }
    void setRect(int x,int y,int width,int height)
    {
        this->rect=QRect(x,y,width,height);
    }
    void startRecord(QString file_path){
        this->filePath=file_path;
        allFrames.clear();
        frames=0;

        QDir dir;
        if(!dir.exists(file_path)) dir.mkdir(file_path);
        if(!dir.exists(file_path+"_cache/"))
            dir.mkdir(file_path+"_cache/");
        else{
            QDir dir(file_path+"_cache/");//clean directory
            foreach(QFileInfo it,dir.entryInfoList()){
                    if(it.suffix()=="jpg")
                        dir.remove(it.fileName());
            }
        }

        file_path+="record.avi";
        char* file_path_and_name_c;
        QByteArray ba=file_path.toLatin1();
        file_path_and_name_c=ba.data();
        this->file=AVI_open_output_file(file_path_and_name_c);//创建一个操作输出文件的对象

        QString format="mjpg";
        char* format_c;
        ba=format.toLatin1();
        format_c=ba.data();

        AVI_set_video(this->file, VIEWWIDTH, VIEWHEIGHT, 1000/UPDATEFREQUENCY, format_c);//设置视频文件的分辨率， 多少帧一秒， 编码方式
    }
    void finishRecord(){
        AVI_close(file);//关闭文件
        frames=0;
    }

    void replay(){
        replayer->start();
        replayer->exec();
    }
private slots:
    void takeCapture(){
        frames++;
        if(object!=nullptr){
            QScreen* screen=QApplication::primaryScreen();//use grab screen instead of grabWidget will not call paintEvent, so there will be no ghost image
            QPixmap map=screen->grabWindow(object->winId(),rect.x(),rect.y(),rect.width(),rect.height());
            QString name=filePath+"_cache/"+QString::asprintf("frame%d.jpg",frames);
            map.save(name,"jpg",20);
            allFrames[QString::asprintf("frame%d.jpg",frames)]=map;

            QByteArray ba;
            QBuffer bf(&ba);
            map.save(&bf, "jpg", 20);//write in data flow

            AVI_write_frame(file, ba.data(), ba.size(), 1); //保存一帧图像, keyframe表示是否为关键帧(即是否完整的一帧图像数据， jpg每张都是完整的)
        }
    }
};

#endif // RECORDER_H
