#ifndef SPACE_H
#define SPACE_H

#include <QGraphicsView>
#include <QTimer>
#include <QKeyEvent>
#include <QMouseEvent>
#include "global.h"
#include "rollingbackgroud.h"
#include "startmenu.h"
#include "playerplane.h"
#include "planefactory.h"
#include "bulletfactory.h"
#include "supplyfactory.h"
#include "recorder.h"
#include "api.h"
#include "if_ai.h"

class Space : public QGraphicsView
{
    Q_OBJECT
public:
    Space(QWidget *parent=0);
    virtual ~Space();
    QString getInfo();
    bool ifStarted();

private:
    QGraphicsScene *scene;
    QTimer *timer;
    PlayerPlane *player;
    PlaneFactory *planeFactory;
    BulletFactory *bulletFactory;
    SupplyFactory *supplyFactory;
    RollingBackgroud *rollBG;
    bool hasStarted,running,victory;//check if it is paused/check if the boss is defeated
    QList<int> keys;    //valid keys

    void keyPressEvent(QKeyEvent *event);//just to send a signal
    void keyReleaseEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

signals:
    void updateInfo();
    void keyPress(int key);//signal the key pressed
    void keyRelease(int key);//signal the key released
    void pause();
    void go_on();
    void mousePress(Qt::MouseButton button);
    void mouseRelease(Qt::MouseButton button);
    void shootEB1(AbstractPlane* shooter,QPointF target);
    void gameFinished(int score,bool finished);
    void scoreChange(int score);
    void bloodChange(int blood);

private slots:
    void initGame();
    void on_phaseChange(int level);
    void on_pause();
    void on_go_on();
    void on_replay();
    void on_keyPress(int key);
    void on_keyRelease(int key);
    void on_mousePress(Qt::MouseButton button);
    void on_mouseRelease(Qt::MouseButton button);
    void on_shootEB1(AbstractPlane* shooter);
    void gameOver(AbstractPlane* player);

    void sendScore(int score);
    void sendBlood(int blood);
};

#endif // SPACE_H
