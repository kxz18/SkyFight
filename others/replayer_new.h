#ifndef REPLAYER_NEW_H
#define REPLAYER_NEW_H
#include <QDialog>
#include <QTimeLine>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <fstream>
#include "rollingbackgroud.h"
#include "planefactory.h"
#include "bulletfactory.h"
#include "supplyfactory.h"
#include "global.h"

class replayer_new : public QDialog
{
    Q_OBJECT
protected:
    QTimer *timer;
    QGraphicsView *view;
    QGraphicsScene *scene;
    QGraphicsTextItem *text;
    RollingBackgroud *back;
    QList<AbstractFlyer*> all;
    QString filePath;
    std::fstream file;

    QPointF toPos(std::string &str){
        int comma=str.find(",");
        QPointF pos(std::stod(str.substr(1,comma-1)),std::stod(str.substr(comma+1,str.size()-comma-2)));
        return pos;
    }

public:
    replayer_new() :
                timer(new QTimer),view(new QGraphicsView),
                scene(new QGraphicsScene),text(new QGraphicsTextItem),
                all()
    {
        this->setGeometry(0,0,VIEWWIDTH+50,VIEWHEIGHT+50); //some margin
        this->setFixedSize(VIEWWIDTH+50,VIEWHEIGHT+50);
        this->setWindowTitle("Replay");
        this->setWindowIcon(QIcon(replayIcon));

        view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        view->setCacheMode(QGraphicsView::CacheBackground);
        view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
        view->setOptimizationFlags(QGraphicsView::DontClipPainter | QGraphicsView::DontSavePainterState);
        view->setRenderHint(QPainter::Antialiasing);

        view->setGeometry((width()-VIEWWIDTH)/2,(height()-VIEWHEIGHT)/2,VIEWWIDTH,VIEWHEIGHT);
        scene->setSceneRect(QRect(0,0,VIEWWIDTH,VIEWHEIGHT));
        view->setScene(scene);

        QVBoxLayout *layout=new QVBoxLayout;
        layout->setGeometry(QRect((width()-VIEWWIDTH)/2,(height()-VIEWHEIGHT)/2,VIEWWIDTH,VIEWHEIGHT));
        layout->setSizeConstraint(QLayout::SetFixedSize);
        layout->addWidget(view);
        this->setLayout(layout);

        QFont font;
        font.setPointSize(30);
        font.setBold(true);
        text->setFont(font);
        text->setDefaultTextColor(Qt::white);
        text->setPlainText("Lose!");
        qreal w=text->boundingRect().width();
        qreal h=text->boundingRect().height();
        text->setPos((SCENEWIDTH-w)/2,(SCENEHEIGHT-h)/2);
        scene->addItem(text);
        back=new RollingBackgroud(scene);
        scene->removeItem(back);

        connect(timer,SIGNAL(timeout()),this,SLOT(on_frameChanged()));
        connect(timer,SIGNAL(timeout()),scene,SLOT(advance()));
    }
    ~replayer_new(){
        delete timer;
        delete view;
        delete text;
    }

    void setFilePath(const QString &name)
    {
        filePath=name;
    }

    void start(){

        qDebug()<<"replayer timeline has started";

        file.open(filePath.toStdString());
        timer->start(UPDATEFREQUENCY);
        scene->removeItem(text);
        scene->addItem(back);
    }

private slots:
    void setFile(QString file_path)
    {
        filePath=file_path;
    }

    void on_frameChanged(){//以下内容因为太累了所以开始瞎写
        foreach(auto it,all){
            delete it;
        }
        all.clear();

        std::string tmp="";
        do{
            file>>tmp;
            if(tmp=="PP"){
                do{
                    file>>tmp;
                    if(tmp=="#") break;
                    else all.append(new PlayerPlane(scene,toPos(tmp)));
                }while(true);
            }else if(tmp=="SEP"){
                do{
                    file>>tmp;
                    if(tmp=="#") break;
                    else all.append(new sEnemyPlane(scene,toPos(tmp)));
                }while(true);
            }else if(tmp=="MEP"){
                do{
                    file>>tmp;
                    if(tmp=="#") break;
                    else all.append(new mEnemyPlane(scene,toPos(tmp)));
                }while(true);
            }else if(tmp=="BP"){
                do{
                    file>>tmp;
                    if(tmp=="#") break;
                    else all.append(new BossPlane(scene,toPos(tmp)));
                }while(true);
            }else if(tmp=="PB"){
                do{
                    file>>tmp;
                    if(tmp=="#") break;
                    else all.append(new PlayerBullet(toPos(tmp),scene));
                }while(true);
            }else if(tmp=="EB1"){
                do{
                    file>>tmp;
                    if(tmp=="#") break;
                    else all.append(new EnemyBullet1(toPos(tmp),scene));
                }while(true);
            }else if(tmp=="EB2"){
                do{
                    file>>tmp;
                    if(tmp=="#") break;
                    else all.append(new EnemyBullet2(toPos(tmp),scene));
                }while(true);
            }else if(tmp=="Star"){
                do{
                    file>>tmp;
                    if(tmp=="#") break;
                    else all.append(new Star(scene,toPos(tmp)));
                }while(true);
            }
        }while(tmp!="]");

        file>>tmp;
        if(tmp=="###"){
            timer->stop();
            file>>tmp;
            text->setPlainText(QString::fromStdString(tmp));
            on_finished();
        }
    }

    void on_finished(){

        qDebug()<<"replay finished\n";

        foreach(auto it,all){
            delete it;
        }
        all.clear();

        QPixmap tmp(backgroud);
        QPixmap revised=tmp.scaled(SCENEWIDTH,SCENEHEIGHT,Qt::KeepAspectRatioByExpanding);
        scene->setBackgroundBrush(revised);
        scene->removeItem(back);
        scene->addItem(text);
    }
};


#endif // REPLAYER_NEW_H
