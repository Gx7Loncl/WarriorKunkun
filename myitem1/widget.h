#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QTimer>
#include <QMouseEvent>
#include <vector>
#include<QSound>

#include "ground.h"
#include "charac.h"
#include "barriers.h"
#include"information.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void initWidget();                         //初始化窗口
    void paintEvent(QPaintEvent *event);       //绘图事件
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void playgame();                           //开始游戏
    void gameover();                           //游戏结束
    void updatePosition();                     //更新坐标
    void collisionDetection();                 //碰撞检测
    void sprint();                             //角色冲刺 => 场景所有对象加速
    void addBarrier();                         //添加障碍物

    std::vector<barriers*>mybarriers;          //管理屏幕中的障碍物
    std::vector<barriers*>::iterator it;

    QPixmap background;
    QTimer m_Timer;                            //刷新屏幕计时器
    QTimer sprint_Timer;                       //冲刺持续时间计时器
    QTimer sprint_interval_Timer;              //冲刺间隔时间计时器
    QTimer add_Barrier_interval_Timer;         //生成障碍物计时器
    QTimer protected_Timer;                    //无敌时间
    bool sprint_once;                          //是否已经冲刺一次
    bool sprint_twice;                         //是否已经冲刺两次
    int i;                                     //障碍物类型
    int score;                                 //得分

    grounds grounds;                           //地面对象
    charac cxk;                                //人物角色对象

private slots:
    void on_startbtn_clicked();

    void on_infobtn_clicked();

    void on_againbtn_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
