#ifndef CHARAC_H
#define CHARAC_H

#include <QPixmap>
#include <QTimer>
#include "myconfig.h"
class charac
{
public:
    charac();
    QPixmap getImg();
    void jump();                //跳跃
    void updatePositionY();     //更新Y轴坐标
public:
    QPixmap run_img[3];         //奔跑图片
    QPixmap jump_img;           //跳跃图片
    QTimer run_Timer;           //奔跑图片切换计时器
    QTimer jump_Timer;          //跳跃时间计时器
    int x = 100;                //角色坐标
    int y = ON_GROUNG_POS_Y;
    int current_run_img;        //奔跑图片下标
    double fall_speed;         //下落速度
    bool jump_once;            //已经跳跃一次
    bool jump_twice;           //已经跳跃两次

    QRect cxk_rect;            //角色边框  用于碰撞检测

};

#endif // CHARAC_H
