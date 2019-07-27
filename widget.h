#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "global.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

private:
    void resizeEvent(QResizeEvent *event);

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void launchMenu();//different signal functions with different parameters require slot functions with the same parameters so there are two launch menu slot functions
    void closeMenu();
    void launchFinishMenu(int score,bool finished);
    void on_updateInfo();
    void on_scoreChange(int score);
    void on_bloodChange(int blood);
    void on_close();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
