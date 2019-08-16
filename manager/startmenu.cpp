#include "startmenu.h"

StartMenu::StartMenu(bool ifContinue,int score,bool finished) :
    labScore(new QLabel),labFinished(new QLabel),
    btnStart(new QPushButton),btnContinue(new QPushButton),
    btnExit(new QPushButton),btnReplay(new QPushButton)
{
    qDebug()<<"entering StartMenu::StartMenu(bool ifContinue,int score,bool finished)";

    QFont font;
    font.setBold(true);
    font.setPointSize(20);
    QPalette pal;
    pal.setColor(QPalette::WindowText,Qt::white);
    labScore->setFont(font);
    labScore->setPalette(pal);
    labScore->setAlignment(Qt::AlignCenter);
    labFinished->setFont(font);
    labFinished->setPalette(pal);
    labFinished->setAlignment(Qt::AlignCenter);

    labScore->setText("Your score\n"+QString::asprintf("%d",score));
    if(finished)
        labFinished->setText("Mission Completed");
    else
        labFinished->setText("Mission Failed");

    int w=VIEWWIDTH/3,h=VIEWHEIGHT/12;
    btnStart->setText("New Start");
    btnStart->setFixedSize(w,h);
    btnContinue->setText("Continue");
    btnContinue->setFixedSize(w,h);
    if(!ifContinue) btnContinue->setEnabled(false);
    btnExit->setText("Exit");
    btnExit->setFixedSize(w,h);
    btnReplay->setText("Replay");
    btnReplay->setFixedSize(w,h);

    btnReplay->setEnabled(false);
    QDir dir(recordFilePath);
    foreach (auto it, dir.entryInfoList()) {
        if(it.suffix()=="record") btnReplay->setEnabled(true);
    }
    //if(!dir.exists("record.avi")) btnReplay->setEnabled(false);

    this->addStretch();
    if(score!=-1){
        this->addWidget(labScore,0,Qt::AlignCenter);
        this->addWidget(labFinished,0,Qt::AlignCenter);
    }
    this->addWidget(btnContinue,0,Qt::AlignCenter);
    this->addWidget(btnStart,0,Qt::AlignCenter);
    this->addWidget(btnReplay,0,Qt::AlignCenter);
    this->addWidget(btnExit,0,Qt::AlignCenter);
    this->addStretch();
    this->setSpacing(20);

    connect(btnStart,SIGNAL(clicked()),this,SLOT(btnStartPress()));
    connect(btnContinue,SIGNAL(clicked()),this,SLOT(btnContinuePress()));
    connect(btnReplay,SIGNAL(clicked()),this,SLOT(btnReplayPress()));
    connect(btnExit,SIGNAL(clicked()),this,SLOT(btnExitPress()));

    qDebug()<<"ending StartMenu::StartMenu(bool ifContinue,int score,bool finished)";
}

StartMenu::~StartMenu()
{
    delete labScore;
    delete labFinished;
    delete btnStart;
    delete btnContinue;
    delete btnExit;
    delete btnReplay;
}

void StartMenu::btnStartPress()
{
    emit startNewGame();
    emit keyPress();
}

void StartMenu::btnContinuePress()
{
    emit continueGame();
    emit keyPress();
}

void StartMenu::btnReplayPress()
{
    emit replayVideo();//do not emit keyPress() to keep the menu on
}

void StartMenu::btnExitPress()
{
    emit quitGame();
    emit keyPress();
}
