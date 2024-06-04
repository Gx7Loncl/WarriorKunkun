#include "ground.h"
#include"myconfig.h"

ground::ground()
{
    pixmap.load(GROUND_PATH);
    pixmap = pixmap.scaled(pixmap.size() * 0.4);
    positx = -31;
    ground_scroll_speed = SCENE_SCROLL_SPEED;
}
void ground::calculateposition(){
    positx -= ground_scroll_speed;           //按速度移动

}

grounds::grounds(){
    for(int i=0;i<20;i++){
        mygrounds[i].positx += 70*i;        // -31, 101, 233, ... 调整间距用的
}}

void grounds::calculatepositions(){
    for(int i=0;i<20;i++){
        mygrounds[i].calculateposition(); // 开始向左滚动，总宽度为1000
        if(mygrounds[i].positx <= -mygrounds[i].pixmap.width()){ //如果滚出地图外
            mygrounds[i].positx += 132*9; // 1188
        }
    }
}


