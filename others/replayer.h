#ifndef REPLAYER_H
#define REPLAYER_H
#include <QDialog>
#include <QVBoxLayout>
#include <QTimeLine>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QDir>
#include <QIcon>
#include "global.h"

class Replayer : public QDialog
{
    Q_OBJECT

protected:
    QTimeLine *timeLine;
    QGraphicsView *view;
    QGraphicsScene *scene;
    QGraphicsTextItem *text;
    QHash<QString,QPixmap>* allFrames;

public:
    Replayer(QHash<QString,QPixmap>* list) : timeLine(new QTimeLine),view(new QGraphicsView),
                scene(new QGraphicsScene),text(new QGraphicsTextItem),allFrames(list){
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
        text->setPlainText("Finished!");
        qreal w=text->boundingRect().width();
        qreal h=text->boundingRect().height();
        text->setPos((SCENEWIDTH-w)/2,(SCENEHEIGHT-h)/2);
        scene->addItem(text);

        connect(timeLine,SIGNAL(frameChanged(int)),this,SLOT(on_frameChanged(int)));
        connect(timeLine,SIGNAL(finished()),this,SLOT(on_finished()));
    }
    ~Replayer(){
        delete timeLine;
        delete view;
        delete scene;
        delete text;
    }
    void start(){

        qDebug()<<"replayer timeline has started";

        timeLine->setDuration(UPDATEFREQUENCY*allFrames->count());
        timeLine->setFrameRange(0,allFrames->count());
        timeLine->setCurveShape(QTimeLine::LinearCurve);
        timeLine->start();
        scene->removeItem(text);
    }

private slots:
    void on_frameChanged(int num){
        QPixmap tmp(allFrames->value(QString::asprintf("frame%d.jpg",num)));
        QPixmap revised=tmp.scaled(VIEWWIDTH,VIEWHEIGHT,Qt::KeepAspectRatioByExpanding);
        scene->setBackgroundBrush(revised);
    }

    void on_finished(){

        qDebug()<<"replay finished\ntotal "<<allFrames->count()<<" frames";

        QPixmap tmp(backgroud);
        QPixmap revised=tmp.scaled(SCENEWIDTH,SCENEHEIGHT,Qt::KeepAspectRatioByExpanding);
        scene->setBackgroundBrush(revised);
        scene->addItem(text);
    }
};

#endif // REPLAYER_H
