### AI 接口

---

```
//变量说明
struct Point{	//x为x坐标，y为y坐标，每个坐标代表的都是物体中心店点的位置
	int x;
	int y;
}
```

---

| 提供坐标的类 | 解释 |
| --------- | ---- |
| class SEP | small enemy plane |
|class MEP| middle enemy plane |
|class BP|boss plane|
|class EB1| enemy bullet 1 (红色) |
|class EB2|enemy bullet 2 (绿色)|
|class PB|player bullet (蓝色)|

---


| 函数                                                 | 作用                                           |
| ---------------------------------------------------- | ---------------------------------------------- |
| Point player_position()                              | 返回当前玩家飞机所在坐标                       |
| template<class T> <br /> std::set<Point> positions() | 根据模板参数的不同返回场景中所有该类物体的坐标 |
| void player_up()                                     | 该帧使玩家飞机上行                             |
| void player_down()                                   | 该帧使玩家飞机下行                             |
| void player_left()                                   | 该帧使玩家飞机左行                             |
| void player_right()                                  | 该帧使玩家飞机右行                             |
| void player_shoot()                                  | 该帧使玩家飞机持续射击状态                     |

---

### 接入方式

1. 将`if_ai.h`头文件中`#define AI`一句取消注释
2. 编写`yourcontrol.cpp`文件中的函数（该函数每帧调用一次）

```
//yourcontrol.cpp基本模板
#include "api.h"
void API::your_control_per_frame(){
}
```

3. 把这两个文件放入工程后重新编译即可

---



### 游戏架构

1. 飞行物

* 纯虚类

| 类名             | 解释                                          |
| ---------------- | --------------------------------------------- |
| `AbstractFlyer`  | 所有飞行物的基类，纯虚                        |
| `AbstractPlane`  | 派生自`AbstractFlyer`，所有飞机类的基类，纯虚 |
| `AbstractBullet` | 派生自`AbstractFlyer`，所有子弹类的基类，纯虚 |
| `AbstractSupply` | 派生自`AbstractFlyer`，所有补给类的基类，纯虚 |

* 飞机类（继承自`AbstractPlane`）

| 类名 | 解释 |
| ---- | ---- |
| `PlayerPlane`    | 玩家飞机 |
| `sEnemyPlane`    | small enemy plane |
| `mEnemyPlane`    | middle enemy plane |
| `BossPlane` | boss plane |

* 子弹类（继承自`AbstractBullet`）

| 类名           | 解释                                     |
| -------------- | ---------------------------------------- |
| `PlayerBullet` | 玩家子弹                                 |
| `EnemyBullet1` | 第一种敌方子弹，红色，向玩家所在方位发射 |
|`EnemyBullet2`|第二种敌方子弹，绿色，行进速度更快，但是只向前方发射|

* 补给类

| 类名   | 解释                     |
| ------ | ------------------------ |
| `Star` | 随机掉落星星，吃星星得分 |

2. 工厂类

| 类名           | 解释                                     |
| -------------- | ---------------------------------------- |
| `PlaneFactory` | 控制除了玩家飞机之外所有飞机的制造和删除 |
|`BulletFactory`|控制所有子弹的制造和删除|
|`SupplyFactory`|控制所有补给的制造和删除|

3. 游戏控制

| 类名 | 解释 |
| ---- | ---- |
|      `Space`|继承自`QGraphicsView`，控制游戏的开始、结束以及工厂、玩家飞机间的通信      |

4. 其他

| 类名       | 解释                                                         |
| ---------- | ------------------------------------------------------------ |
| `Randomer` | 随机数产生器，单例。通过`Randomer：：RndInt（int max）`产生大于等于0，小于`max`的随机整数 （用于敌机坐标的生成）|
|`Replayer`|用于重播的类，重播原理是把图片按帧切换|
|`Recorder`|用于记录的类，记录原理是保存每帧截图，并使用`Github`开源项目中的方法把图片合成`.avi`视频文件。包含成员`Replayer`用于在游戏内重播|
|`recorder_new`|后来重新写的记录类，把每帧所有飞行物的位置全部记录在文本文件中，减小记录文件的大小|
|`replayer_new`|后来重新写的用于重播的类，每帧从文件中读取所有坐标并在场景中重新绘制所有飞行物|
|`RollingBackgroud`|移动背景，实质是一个没有碰撞体积的`QGraphicsPixmapItem`，按一定速度向下移动，到头后重新定位到最初的位置，因此背景图片最后和最前面需要保证是一样的。|
|`StartMenu`|继承自`QVboxLayout`，是开始菜单、暂停菜单以及游戏结束的菜单。每次使用完成后会自动销毁|
|`API`|AI接口类|

#### 补充

* 子弹碰撞检测交给飞机，子弹不做碰撞检测
* 飞机和飞机碰撞时由血量多的一方进行碰撞检测的结算，若一样多则各自结算自己的
* 飞机工厂和子弹工厂之间通过`QGraphicsView（Space）`作为中介; 对于需要玩家位置的`EnemyBullet1`，飞机工厂把含飞机信息的signal发出，space接收后把shooter信息加上player的位置信息作为signal发给子弹工厂。其他子弹种类直接由子弹工厂接收飞机工厂的signal
* WINDOWS下如果界面太小，可以将`global.h`下的SCALE宏的值改成合适的数值（例如2）