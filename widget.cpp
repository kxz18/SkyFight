#include "widget.h"
#include "ui_widget.h"
#include "startmenu.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->resize(WINDOWWIDTH,WINDOWHEIGHT);
    this->setWindowTitle("Sky Fight by kxz");
    this->setMinimumSize(WINDOWWIDTH,WINDOWHEIGHT);
    this->setWindowFlag(Qt::WindowCloseButtonHint,0);

    ui->view->setGeometry((width()-VIEWWIDTH)/2,(height()-VIEWHEIGHT)/2,VIEWWIDTH,VIEWHEIGHT);
    Recorder::instance().setWidget(this);
    Recorder::instance().setRect((width()-VIEWWIDTH)/2,(height()-VIEWHEIGHT)/2,VIEWWIDTH,VIEWHEIGHT);

    ui->lab_score->setGeometry((width()-VIEWWIDTH)/2,(height()+VIEWHEIGHT)/2,LABWIDTH,LABHEIGHT);
    ui->lab_score->setText("Score: 0");

    ui->lab_blood->setGeometry((width()-VIEWWIDTH)/2+LABWIDTH,(height()+VIEWHEIGHT)/2,LABWIDTH,LABHEIGHT);
    ui->lab_blood->setText("Blood: "+QString::asprintf("%d",PLAYERPLANEBLOOD));

    ui->info->setGeometry((width()-VIEWWIDTH)/2-INFOWIDTH,(height()-VIEWHEIGHT)/2,INFOWIDTH,INFOHEIGHT);
    ui->info->setText("");
    ui->info->setWordWrap(true);
    ui->info->setAlignment(Qt::AlignLeft);
    ui->info->setAlignment(Qt::AlignTop);
    QFont font;
    font.setWordSpacing(6);
    font.setPointSize(10);
    ui->info->setFont(font);

    launchMenu();

    connect(ui->view,SIGNAL(pause()),this,SLOT(launchMenu()));
    connect(ui->view,SIGNAL(go_on()),this,SLOT(closeMenu()));
    connect(ui->view,SIGNAL(gameFinished(int,bool)),this,SLOT(launchFinishMenu(int,bool)));
    connect(ui->view,SIGNAL(updateInfo()),this,SLOT(on_updateInfo()));
    connect(ui->view,SIGNAL(scoreChange(int)),this,SLOT(on_scoreChange(int)));
    connect(ui->view,SIGNAL(bloodChange(int)),this,SLOT(on_bloodChange(int)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::launchMenu()
{
    bool ifContinue=false;
    if(QObject::sender()!=nullptr)
        ifContinue=true;
    StartMenu *menu=new StartMenu(ifContinue);
    this->setLayout(menu);
    connect(menu,SIGNAL(startNewGame()),ui->view,SLOT(initGame()));
    connect(menu,SIGNAL(continueGame()),ui->view,SLOT(on_go_on()));
    connect(menu,SIGNAL(replayVideo()),ui->view,SLOT(on_replay()));
    connect(menu,SIGNAL(quitGame()),this,SLOT(on_close()));
    connect(menu,SIGNAL(keyPress()),this,SLOT(closeMenu()));
}

void Widget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    ui->view->setGeometry((width()-VIEWWIDTH)/2,(height()-VIEWHEIGHT)/2,VIEWWIDTH,VIEWHEIGHT);
    ui->info->setGeometry((width()-VIEWWIDTH)/2-INFOWIDTH,(height()-VIEWHEIGHT)/2,INFOWIDTH,INFOHEIGHT);
    ui->lab_score->setGeometry((width()-VIEWWIDTH)/2,(height()+VIEWHEIGHT)/2,LABWIDTH,LABHEIGHT);
    ui->lab_blood->setGeometry((width()-VIEWWIDTH)/2+LABWIDTH,(height()+VIEWHEIGHT)/2,LABWIDTH,LABHEIGHT);
    Recorder::instance().setRect((width()-VIEWWIDTH)/2,(height()-VIEWHEIGHT)/2,VIEWWIDTH,VIEWHEIGHT);
}

void Widget::closeMenu()
{
    delete this->layout();
}

void Widget::launchFinishMenu(int score,bool finished)
{
    qDebug()<<"entering Widget::launchFinishMenu(int score,bool finished)";

    StartMenu *menu=new StartMenu(false,score,finished);
    this->setLayout(menu);
    connect(menu,SIGNAL(startNewGame()),ui->view,SLOT(initGame()));
    connect(menu,SIGNAL(continueGame()),ui->view,SLOT(on_go_on()));
    connect(menu,SIGNAL(replayVideo()),ui->view,SLOT(on_replay()));
    connect(menu,SIGNAL(quitGame()),this,SLOT(on_close()));
    connect(menu,SIGNAL(keyPress()),this,SLOT(closeMenu()));

    qDebug()<<"ending Widget::launchFinishMenu(int score,bool finished)";
}


void Widget::on_updateInfo()
{
    QString tmp=ui->info->text();
    tmp=ui->view->getInfo()+"\n"+tmp;
    ui->info->setText(tmp);
}

void Widget::on_scoreChange(int score)
{
    ui->lab_score->setText("Score: "+QString::asprintf("%d",score));
}

void Widget::on_bloodChange(int blood)
{
    ui->lab_blood->setText("Blood: "+QString::asprintf("%d",blood));
}

void Widget::on_close()
{
    qDebug()<<"entering Widget::on_close()";

    //QDir dir(recordFilePath);
    if(ui->view->ifStarted()==true){//clean captures and failed replays
        QDir dir(recordFilePath);
        foreach(QFileInfo it,dir.entryInfoList()){
            if(it.suffix()=="avi")
                dir.remove(it.fileName());
        }
        dir.setPath(recordFilePath+"_cache");
        foreach(QFileInfo it,dir.entryInfoList()){
            if(it.suffix()=="jpg")
                dir.remove(it.fileName());
        }
    }
    this->close();

    qDebug()<<"ending Widget::on_close()";
}
