#include "information.h"
#include "ui_information.h"
#include<QMovie>
#include<QPixmap>
#include<QPainter>

information::information(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::information)
{
    ui->setupUi(this);
    this -> setWindowTitle("游戏说明");                      //设置名字
    QPalette pe, pe1;
    //设置黑底红字
//    pe.setColor(QPalette::Background,Qt::black);
    pe.setColor(QPalette::WindowText,Qt::blue);
    pe1.setColor(QPalette::WindowText,Qt::red);
    ui -> label_2 -> setPalette(pe);
    ui -> label_3 -> setPalette(pe1);

    QMovie *mov = new QMovie("D:\\Qt-projects\\myitem1\\res\\icon1.gif");
    mov -> start();
    ui -> icon1 -> setMovie(mov);
    ui -> icon1 -> setScaledContents(true);
    ui -> icon2 -> setMovie(mov);
    ui -> icon2 -> setScaledContents(true);

    background.load("D:\\Qt-projects\\myitem1\\res\\background.png");

}
void information::paintEvent(QPaintEvent *event){                                  ////////paintEvent             //////////Event
    QPainter painter(this);                                 //指定当前窗口为绘图设备
    painter.drawPixmap(0, 0, width(), height(), background);}

information::~information()
{
    delete ui;
}

void information::on_backbtn_clicked()
{
    this -> close();
}

