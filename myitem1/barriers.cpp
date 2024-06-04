#include "barriers.h"
#include"myconfig.h"

barriers::barriers()
{

}
chicken::chicken(){
    img.load(CHICKEN_PATH);
    img = img.scaled(img.size() * 0.13);
    x = GAME_WIDTH;
    x += 22;
    y = 220;

    rect.setWidth(img.width());
    rect.setHeight(img.height());
    rect.moveTo(x,y);
}
void chicken::updatePosition(){
    x -= SCENE_SCROLL_SPEED;
    rect.moveTo(x,y);
}                                       //需要跟随场景一起移动
bool chicken::isOut(){
    return x < -img.width();
}
int chicken::collisionDetection(QRect r){
    if(rect.intersects(r)){              //是否与给定的矩形相交
        return 3;
    }
    else
        return 0;
}
QPixmap chicken::getImg(){
    return img;
}
barrier1::barrier1(){
    img.load(BARRIER1_PATH);
    img = img.scaled(img.size() * 0.3);
    x = GAME_WIDTH;
    y = 120;
    rect.setWidth(9);
    rect.setHeight(img.height());
    rect.moveTo(x+21,y);
}

void barrier1::updatePosition(){
    x -= SCENE_SCROLL_SPEED;
    rect.moveTo(x+21,y);
}
bool barrier1::isOut(){
    return x < -img.width();
}
int barrier1::collisionDetection(QRect r){
    if(rect.intersects(r)){
        return 1;
    }
    else
        return 0;
}
QPixmap barrier1::getImg(){
    return img;

}

barrier2::barrier2(){
    img.load(BARRIER2_PATH);
    img = img.scaled(img.size() * 0.3);
    x = GAME_WIDTH;
    y = 120;
    rect.setWidth(9);
    rect.setHeight(img.height());
    rect.moveTo(x+21,y);
}

void barrier2::updatePosition(){
    x -= SCENE_SCROLL_SPEED;
    rect.moveTo(x+21,y);
}
bool barrier2::isOut(){
    return x < -img.width();
}
int barrier2::collisionDetection(QRect r){
    if(rect.intersects(r)){
        return 1;
    }
    else
        return 0;
}
QPixmap barrier2::getImg(){
    return img;

}
barrier3::barrier3() //位于地面
{
    img.load(BARRIER3_PATH);
    img = img.scaled(img.size() * 0.4);
    x = GAME_WIDTH;
    y = 320;
    rect.setWidth(img.width() - 10);
    rect.setHeight(img.height() - 3);
    rect.moveTo(x+5,y+3);                       //移动碰撞框
}
void barrier3::updatePosition(){
    x -= SCENE_SCROLL_SPEED;
    rect.moveTo(x+5,y+3);
}
bool barrier3::isOut(){
    return x < -img.width();
}
int barrier3::collisionDetection(QRect r){
    if(rect.intersects(r)){
        return 1;
    }
    else
        return 0;
}
QPixmap barrier3::getImg(){

    return img;

}
