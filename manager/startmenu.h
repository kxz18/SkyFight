#ifndef STARTMENU_H
#define STARTMENU_H
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QDir>
#include "global.h"

class StartMenu : public QVBoxLayout
{
    Q_OBJECT

protected:
    QLabel *labScore,*labFinished;
    QPushButton *btnStart,*btnContinue,*btnExit,*btnReplay;

public:
    StartMenu(bool ifContinue=false,int score=-1,bool finished=false);
    ~StartMenu();

private slots:
    void btnStartPress();
    void btnContinuePress();
    void btnExitPress();
    void btnReplayPress();

signals:
    void startNewGame();
    void continueGame();
    void replayVideo();
    void quitGame();
    void keyPress();
};

#endif // STARTMENU_H
