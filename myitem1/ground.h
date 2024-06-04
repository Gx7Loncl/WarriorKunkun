#ifndef GROUND_H
#define GROUND_H

#include<QPixmap>

class ground
{
public:
    ground();
    void calculateposition();
public:
    QPixmap pixmap;
    int positx;
    int ground_scroll_speed;
};

class grounds{
public:
    grounds();
    void calculatepositions();
public:
    ground mygrounds[20];

};


#endif // GROUND_H
