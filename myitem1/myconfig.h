#ifndef MYCONFIG_H
#define MYCONFIG_H

#define GAME_WIDTH 1000 //宽度
#define GAME_HEIGHT 524 //高度
#define GAME_TITLE "战斗吧！坤坤勇士" //游戏名称

#define GAME_ICON "D:/Qt-projects/myitem1/res/icon.png"           //游戏图标
#define BACKGROUND_PATH "D:/Qt-projects/myitem1/res/background.png"   //背景图片路径
#define GROUND_PATH "D:/Qt-projects/myitem1/res/ground.png"           //地面图片路径
#define JUMP_PATH "D:/Qt-projects/myitem1/res/fly.png"                //跳跃图片路径
#define BARRIER1_PATH "D:/Qt-projects/myitem1/res/barrier1.png"
#define BARRIER2_PATH "D:/Qt-projects/myitem1/res/barrier2.png"
#define BARRIER3_PATH "D:/Qt-projects/myitem1/res/barrier3.png"
#define CHICKEN_PATH "D:/Qt-projects/myitem1/res/chicken.png"

#define SCENE_SCROLL_SPEED 5     //场景移动速度
#define GAME_RATE 8              //屏幕刷新间隔
#define RUN_INTERVAL 2000          //奔跑图片刷新间隔
#define INIT_FALL_SPEED 5        //初始下落速度
#define ON_GROUNG_POS_Y 361   //角色位于地面上的Y轴坐标

#define JUMP_DURATION 380           //跳跃持续时间
#define SPRINT_DURATION 250         //冲刺持续时间
#define SPRINT_INTERVAL 1600        //冲刺间隔时间
#define ADD_BARRIER_INTERVAL 1300   //生成障碍物间隔时间
#define PROTECTED_DURATION 5000     //无敌时间

#endif // MYCONFIG_H
