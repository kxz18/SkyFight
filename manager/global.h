#ifndef GLOBAL_H
#define GLOBAL_H

#include <QString>
#include <QDebug>

#include<sys/types.h>
#ifdef WIN32
#define SCALE 1.5//overall size adjustment parameter
#else
#define SCALE 1
#endif

//sizes of settings
#define WINDOWWIDTH 700*SCALE
#define WINDOWHEIGHT 700*SCALE
#define VIEWWIDTH 365*SCALE
#define VIEWHEIGHT 545*SCALE
#define SCENEWIDTH 360*SCALE
#define SCENEHEIGHT 540*SCALE
#define INFOWIDTH 150*SCALE   //info bar
#define INFOHEIGHT VIEWHEIGHT
#define LABWIDTH 80*SCALE     //blood board and score board
#define LABHEIGHT 20*SCALE
#define BGMOVESPEED 0.5*SCALE

//update frequency (every ** ms)
#define UPDATEFREQUENCY 25

//parameters of player plane
#define PLAYERPLANEWIDTH 50*SCALE
#define PLAYERPLANEHEIGHT PLAYERPLANEWIDTH/400.0*518
#define PLAYERPLANESPEED 3*SCALE
#define PLAYERPLANEBLOOD 5
//parameters of small enemy plane
#define SENEMYPLANEWIDTH 80*SCALE
#define SENEMYPLANEHEIGHT SENEMYPLANEWIDTH/178.0*133
#define SENEMYPLANESPEED 1*SCALE
#define SENEMYPLANEBLOOD 2
//parameters of middle enemy plane
#define MENEMYPLANEWIDTH 40*SCALE
#define MENEMYPLANEHEIGHT MENEMYPLANEWIDTH/370.0*590
#define MENEMYPLANESPEED 2*SCALE
#define MENEMYPLANEBLOOD 3
//parameters of boss enemy plane
#define BOSSPLANEWIDTH 150*SCALE
#define BOSSPLANEHEIGHT BOSSPLANEWIDTH/259.0*196
#define BOSSPLANESPEED 0.5*SCALE
#define BOSSPLANEBLOOD 50
//parameters of player bullet
#define PLAYERBULLETWIDTH 15*SCALE
#define PLAYERBULLETHEIGHT 15*SCALE
#define PLAYERBULLETSPEED 5*SCALE
//parameters of enemy bullet 1
#define ENEMYBULLET1WIDTH 20*SCALE
#define ENEMYBULLET1HEIGHT 20*SCALE
#define ENEMYBULLET1SPEED 3*SCALE
//parameters of enemy bullet 2
#define ENEMYBULLET2WIDTH 15*SCALE
#define ENEMYBULLET2HEIGHT 15*SCALE
#define ENEMYBULLET2SPEED 5*SCALE
//parameters of stars
#define STARWIDTH 30*SCALE
#define STARHEIGHT 30*SCALE
#define STARBASICDROP 0.4 //basic drop possibility

//frequency of bullets (one per *** ms)
#define PBFREQUENCY 500    //player's bullets
#define SEBFREQUENCY 2500   //small enemy plane bullets (1)
#define MEBFREQUENCY 1500   //middle enemy plane bullets (2)
#define BEB1FREQUENCY 750  //boss enemy bullet 1
#define BEB2FREQUENCY 1250  //boss enemy bullet 2

//score how many to reach the next difficulty level
#define DIFFICULTYUP 10
//at which level the boss will come
#define BOSSCOME 4
//under base difficulty level, every 5 second(5000 ms) a small enenmy plane is created
#define SETIMEGAUGE 2500
#define METIMEGAUGE 5000

const QString backgroud=":/images/backgroud/backgroud.jpeg";
const QString rollingBackgroud=":/images/backgroud/rollingBackgroud.jpg";
const QString playerPlaneImage=":/images/planes/playerPlane.png";
const QString sEnemyPlaneImage=":/images/planes/sEnemyPlane.png";
const QString mEnemyPlaneImage=":/images/planes/mEnemyPlane.png";
const QString bossPlaneImage=":/images/planes/bossPlane.png";
const QString playerBulletImage=":/images/bullets/playerBullet.png";
const QString enemyBullet1Image=":/images/bullets/enemyBullet1.png";
const QString enemyBullet2Image=":/images/bullets/enemyBullet2.png";
const QString starImage=":/images/supplies/star.png";

const QString replayIcon=":/images/icon/replay.png";
const QString icon=":/images/icon/icon.png";
const QString recordFilePath="./record/";

const QList<QString> planeKeyWords=
{
  "PP", "SEP", "MEP", "BP"
};

const QList<QString> bulletKeyWords=
{
  "PB", "EB1", "EB2"
};

const QList<QString> supplyKeyWords=
{
  "Star"
};

const QList<int> keys=
{
    Qt::Key_W, Qt::Key_S, Qt::Key_A, Qt::Key_D, Qt::Key_J, Qt::Key_P
};
#endif // GLOBAL_H
