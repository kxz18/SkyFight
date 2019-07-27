#include "space.h"

Space::Space(QWidget *parent) : QGraphicsView(parent),hasStarted(false),running(false),victory(false)
{
    keys=
    {
        Qt::Key_W, Qt::Key_S, Qt::Key_A, Qt::Key_D, Qt::Key_J, Qt::Key_P
    };

    scene=new QGraphicsScene(QRectF(0,0,SCENEWIDTH,SCENEHEIGHT));//cordination and bounding rectangle of the scene

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setOptimizationFlags(QGraphicsView::DontClipPainter | QGraphicsView::DontSavePainterState);
    setRenderHint(QPainter::Antialiasing);

    QPixmap origin(backgroud);
    QPixmap revised=origin.scaled(SCENEWIDTH,SCENEHEIGHT,Qt::IgnoreAspectRatio);
    scene->setBackgroundBrush(revised);
    this->setScene(scene);

    rollBG=nullptr;//initialize when game has started
    planeFactory=new PlaneFactory(scene);
    bulletFactory=new BulletFactory(scene);
    supplyFactory=new SupplyFactory(scene);
    timer=new QTimer;//initialize timer but not start

    player=new PlayerPlane(scene);
    player->setZValue(10);
    scene->removeItem(player);//at this time player shouldn't be on the screen

    connect(player,SIGNAL(shoot(QPointF)),bulletFactory,SLOT(createPB(QPointF)));//remember it must be here because from here player is initialized
    connect(planeFactory,SIGNAL(killEnemy(AbstractPlane*)),player,SLOT(getScore(AbstractPlane*)));
    connect(planeFactory,SIGNAL(killEnemy(AbstractPlane*)),supplyFactory,SLOT(fore_createStar(AbstractPlane*)));
    connect(planeFactory,SIGNAL(shootEB1(AbstractPlane*)),this,SLOT(on_shootEB1(AbstractPlane*)));
    connect(planeFactory,SIGNAL(shootEB2(AbstractPlane*)),bulletFactory,SLOT(createEB2(AbstractPlane*)));
    connect(this,SIGNAL(shootEB1(AbstractPlane*,QPointF)),bulletFactory,SLOT(createEB1(AbstractPlane*,QPointF)));
    connect(player,SIGNAL(phaseChange(int)),this,SLOT(on_phaseChange(int)));
    connect(player,SIGNAL(planeDestroyed(AbstractPlane*)),this,SLOT(gameOver(AbstractPlane*)));
    connect(player,SIGNAL(killBoss(AbstractPlane*)),this,SLOT(gameOver(AbstractPlane*)));
    connect(player,SIGNAL(scoreChange(int)),this,SLOT(sendScore(int)));
    connect(player,SIGNAL(bloodChange(int)),this,SLOT(sendBlood(int)));

    connect(this,SIGNAL(keyPress(int)),this,SLOT(on_keyPress(int)));
    connect(this,SIGNAL(keyRelease(int)),this,SLOT(on_keyRelease(int)));
    connect(this,SIGNAL(mousePress(Qt::MouseButton)),this,SLOT(on_mousePress(Qt::MouseButton)));
    connect(this,SIGNAL(mouseRelease(Qt::MouseButton)),this,SLOT(on_mouseRelease(Qt::MouseButton)));
    connect(this,SIGNAL(pause()),this,SLOT(on_pause()));
    connect(this,SIGNAL(go_on()),this,SLOT(on_go_on()));
#ifdef AI
    connect(timer,SIGNAL(timeout()),&API::game(),SLOT(AI_control()));
#endif
    connect(timer,SIGNAL(timeout()),scene,SLOT(advance()));
    connect(timer,SIGNAL(timeout()),&(Recorder::instance()),SLOT(takeCapture()));
    connect(timer,SIGNAL(timeout()),planeFactory,SLOT(createEnemy()));
}

Space::~Space(){
    delete scene;
    delete rollBG;
    delete timer;
    delete player;
    delete planeFactory;
    delete bulletFactory;
    delete supplyFactory;
}

QString Space::getInfo()
{
    QString info="";
    info+=QString::asprintf("%d",player->score());
    if(player->w)
        info+=" Up Move,";
    if(player->s)
        info+=" Down Move,";
    if(player->a)
        info+=" Left Move,";
    if(player->d)
        info+=" Right Move,";
    if(player->shooting)
        info+=" Shoot";
    if(info[info.length()-1]==",")
        info.remove(info.length()-1,1);
    return info;
}

bool Space::ifStarted()
{
    return hasStarted;
}

void Space::hide()
{
    planeFactory->invisible();
    bulletFactory->invisible();
    supplyFactory->invisible();
}

void Space::initGame()
{
    qDebug()<<"entering Space::initGame()";

    planeFactory->clear();
    bulletFactory->clear();
    supplyFactory->clear();
    scene->clear();
    rollBG=new RollingBackgroud(scene);
    scene->addItem(player);
    player->refresh();
    sendScore(player->score());//refresh score board and blood board
    sendBlood(player->blood);
    on_phaseChange(player->level);
    this->setFocus();
    timer->start(UPDATEFREQUENCY);
    hasStarted=true;
    running=true;

    Recorder::instance().startRecord(recordFilePath);

#ifdef AI
    API::game().setup(this->player,this->planeFactory,
               this->bulletFactory,this->supplyFactory);
#endif
    qDebug()<<"ending Space::initGame()";
}

void Space::on_phaseChange(int level)
{

    qDebug()<<"level up to "<<level;

    planeFactory->setLevel(level);
}

void Space::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_P&&running)
       emit pause();
    else if(event->key()==Qt::Key_P&&!running&&hasStarted)
       emit go_on();
    else if(keys.contains(event->key())){
        if(running){
            emit keyPress(event->key());
            if(!event->isAutoRepeat())
                emit updateInfo();//only first press and first release will call updateInfo()

        }
    }
    QGraphicsView::keyPressEvent(event);//let the base class deal with the event
}

void Space::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key()!=Qt::Key_P&&
       keys.contains(event->key())&&running){
        emit keyRelease(event->key());
        if(!event->isAutoRepeat())
            emit updateInfo();
    }
    QGraphicsView::keyReleaseEvent(event);
}

void Space::mousePressEvent(QMouseEvent *event)
{
    if(running){
        emit mousePress(event->button());//only emit when running, otherwise the program will crash if you click mouse at a place out of startmenu
        emit updateInfo();
    }
    QGraphicsView::mousePressEvent(event);
}

void Space::mouseReleaseEvent(QMouseEvent *event)
{
    if(running){
        emit mouseRelease(event->button());
        emit updateInfo();
    }
    QGraphicsView::mouseReleaseEvent(event);
}

void Space::on_pause()
{
    if(running){
        timer->stop();
        running=false;
    }
}

void Space::on_go_on()
{
    if(!running){
        timer->start();
        running=true;
    }
}

void Space::on_replay()
{
    Recorder::instance().replay();
}

void Space::on_keyPress(int key)
{
    switch(key){
    case Qt::Key_W: player->w=true;break;
    case Qt::Key_S: player->s=true;break;
    case Qt::Key_A: player->a=true;break;
    case Qt::Key_D: player->d=true;break;
    case Qt::Key_J: player->shooting=true;break;
    default: break;
    }
}

void Space::on_keyRelease(int key)
{
    switch(key){
    case Qt::Key_W: player->w=false;break;
    case Qt::Key_S: player->s=false;break;
    case Qt::Key_A: player->a=false;break;
    case Qt::Key_D: player->d=false;break;
    case Qt::Key_J: player->shooting=false;break;
    default: break;
    }
}

void Space::on_mousePress(Qt::MouseButton button)
{
    if(button==Qt::LeftButton) player->shooting=true;
    else if(button==Qt::RightButton){}
}

void Space::on_mouseRelease(Qt::MouseButton button)
{
    if(button==Qt::LeftButton) player->shooting=false;
}

void Space::on_shootEB1(AbstractPlane* shooter)
{
    QPointF target=player->scenePos();
    target.rx()+=PLAYERPLANEWIDTH/2;
    target.ry()+=PLAYERPLANEHEIGHT/2;
    emit shootEB1(shooter,target);
}

void Space::gameOver(AbstractPlane* player)
{
    qDebug()<<"entering Space::gameOver(AbstractPlane* player)";

    timer->stop();
    planeFactory->setLevel(1);//in case it create another boss plane
    Recorder::instance().finishRecord();
    hasStarted=false;
    running=false;
    scene->removeItem(player);//can't just clear scene since it will delete the objects instantly
    scene->removeItem(rollBG);
    emit gameFinished(this->player->score(),this->player->ifVictory());//ifVictory() is defined in class PlayerPlane so this-> is necessary
    //planeFactory->invisible();
    //bulletFactory->invisible();
    //upplyFactory->invisible();
    rollBG->deleteLater();

    qDebug()<<"ending Space::gameOver(AbstractPlane* player)";
}

void Space::sendScore(int score)
{
    emit scoreChange(score);
}

void Space::sendBlood(int score)
{
    emit bloodChange(score);
}
