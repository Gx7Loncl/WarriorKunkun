#include "charac.h"
#include<QRgb>
#include<QBitmap>

charac::charac()
{
    QPixmap myrun_img1("D:/Qt-projects/myitem1/res/01.png"  );
    QPixmap myrun_img2("D:/Qt-projects/myitem1/res/02.png"  );
    QPixmap myrun_img3("D:/Qt-projects/myitem1/res/03.png"  );
    QPixmap myjump_img("D:/Qt-projects/myitem1/res/04.png"  );
//    // 设置要替换的背景颜色
//    QRgb bgColor = qRgb(136, 179, 232); // 蓝色背景

//    // 创建蒙版，将背景色替换为透明
//    myrun_img.setMask(myrun_img.createMaskFromColor(bgColor, Qt::MaskOutColor));

    // 设置缩放比例
    float scale = 0.15;                                      // 缩放比例为 50%

    // 对人物图片进行缩放
    run_img[0] = myrun_img3.scaled(myrun_img3.size() * scale);
    run_img[1] = myrun_img2.scaled(myrun_img2.size() * scale);
    run_img[2] = myrun_img1.scaled(myrun_img1.size() * scale);
    jump_img = myjump_img.scaled(myjump_img.size() * scale);

    current_run_img = 0;
    run_Timer.setInterval(RUN_INTERVAL);
    QObject::connect(&run_Timer,&QTimer::timeout,[this]()    //谁发出信号，发出什么信号
    {
        current_run_img = (++current_run_img) % 3;           //0, 1, 2
    });

    jump_Timer.setInterval(JUMP_DURATION);
    jump_Timer.setSingleShot(true);                          //只触发一次

    fall_speed = INIT_FALL_SPEED;
    jump_once = false;
    jump_twice = false;
    cxk_rect.setWidth(51);                                   //初始化角色边框
    cxk_rect.setHeight(102);
    cxk_rect.moveTo(x+17,y+8);

}
QPixmap charac::getImg(){                                    //根据位置获取角色状态图片
    if(y>=ON_GROUNG_POS_Y){
        return run_img[current_run_img];
    }
    else return jump_img;
}
void charac::jump(){ //是否可以跳
    if(y == ON_GROUNG_POS_Y){ //我还在地面上
        jump_once = false;
        jump_twice = false;
        fall_speed = INIT_FALL_SPEED;
    }
    if(jump_twice||(jump_Timer.remainingTime()>200 && jump_Timer.isActive())){
        return;
    }
    if(y==ON_GROUNG_POS_Y){                                 //我还在地面上
        jump_Timer.start();
        jump_once = true;
    }
    if(y < ON_GROUNG_POS_Y && !jump_twice){                 //二段跳
        jump_Timer.start();
        jump_twice = true;
    }
}

void charac::updatePositionY(){                 //模拟上升运动,这里具体完成跳跃的高度变化
    if(jump_Timer.isActive()){
        y -= jump_Timer.remainingTime()/45;
    }
    else{
        fall_speed += 0.03;                                  //下落加速度
        y += fall_speed;
    }
    if(y >= ON_GROUNG_POS_Y){                                //如果到地面了，就保持位置
        y = ON_GROUNG_POS_Y;
    }
    cxk_rect.moveTo(x+17,y+8);
}
