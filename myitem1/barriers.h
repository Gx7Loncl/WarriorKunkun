#ifndef BARRIERS_H
#define BARRIERS_H

#include<QPixmap>

class barriers
{
public:
    barriers();
    virtual void updatePosition()=0;
    virtual void updatePiaofulingPosY()=0;
    virtual bool isOut()=0;
    virtual int collisionDetection(QRect)=0;      //碰撞检测情况处理超过两种，定义返回值为int
    virtual QPixmap getImg()=0;
public:
    int x,y;
    QPixmap img;
    QRect rect;
};

class chicken: public barriers{
public:
    chicken();
    void updatePosition();
    void updatePiaofulingPosY(){}
    bool isOut();
    int collisionDetection(QRect);
    QPixmap getImg();
};

class barrier1:public barriers
{
public:
    barrier1();
    void updatePosition();
    void updatePiaofulingPosY(){}
    bool isOut();
    int collisionDetection(QRect);
    QPixmap getImg();
public:
    QPixmap img2;
};

class barrier2:public barriers
{
public:
    barrier2();
    void updatePosition();
    void updatePiaofulingPosY(){}
    bool isOut();
    int collisionDetection(QRect);
    QPixmap getImg();
public:
    QPixmap img2;
};

class barrier3:public barriers
{
public:
    barrier3();
    void updatePosition();
    void updatePiaofulingPosY(){}
    bool isOut();
    int collisionDetection(QRect);
    QPixmap getImg();
public:
    QPixmap img2;
};

#endif // BARRIERS_H
