#include "widget.h"
#include "ui_widget.h"
#include "myconfig.h"
#include"ground.h"
#include"barriers.h"
#include"information.h"

#include <QIcon>
#include <QKeyEvent>
#include <ctime>
#include <QFontDatabase>
#include <QString>
#include <QSound>
#include <QMediaPlayer>
#include<QSoundEffect>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{

//    QFont ft;
//    ft.setPointSize(20);
//    ft.setWeight(QFont::Bold);
//    ui -> score -> setFont(ft);
    ui -> setupUi(this);

    //播放音频
     QSoundEffect *music = new QSoundEffect();
     music -> setSource(QUrl::fromLocalFile("D:\\Qt-projects\\myitem1\\res\\bgm.wav"));
     music -> setLoopCount(QSoundEffect::Infinite);                //设置无限循环
     music -> setVolume(0.5f);                                     //设置音量，在0到1之间
     music -> play();

    ui -> startbtn ->setStyleSheet("color: rgb(45, 215, 15); background-color: rgb(145, 155, 112);");
    ui -> infobtn ->setStyleSheet("color: rgb(45, 225, 15); background-color: rgb(155, 155, 112);");
//    ui -> groupBox -> setStyleSheet("background-color:rgba(0,0,0,0); border-image: url(D:\\Qt-projects\\myitem1\\res\\background.png);color:rgb(81,192,223);");
    QImage *img = new QImage;
    img -> load("D:\\Qt-projects\\myitem1\\res\\logo.png");
    // 获取 QLabel 的大小
    QSize labelSize = ui -> logo -> size();

    // 将图像缩放到 QLabel 的大小
    QImage scaledImage = img -> scaled(labelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui -> logo -> setPixmap(QPixmap::fromImage(scaledImage));      //Image到QPixmap的格式转换

    initWidget();

}
void Widget::initWidget(){
    this -> setFixedSize(GAME_WIDTH,GAME_HEIGHT);                 //大小
    this -> setWindowTitle(GAME_TITLE);                           //标题
    this -> setWindowIcon(QIcon(GAME_ICON));                      //图标
    background.load(BACKGROUND_PATH);                             //加载背景
    update();  

    ui -> startbtn -> setFocusPolicy(Qt::NoFocus);                //按键可能会冲突
    ui -> infobtn -> setFocusPolicy(Qt::NoFocus);
    ui-> againbtn ->setFocusPolicy(Qt::NoFocus);
    ui -> groupBox -> hide();

    m_Timer.setInterval(GAME_RATE);                                 //主定时器设置
    sprint_Timer.setInterval(SPRINT_DURATION);                      //冲刺定时器设置
    sprint_Timer.setSingleShot(true);                               //单次点击后即终止
    sprint_interval_Timer.setInterval(SPRINT_INTERVAL);             //冲刺冷却定时器设置
    sprint_interval_Timer.setSingleShot(true);
    add_Barrier_interval_Timer.setInterval(ADD_BARRIER_INTERVAL);   //障碍物计时器设置
    protected_Timer.setInterval(PROTECTED_DURATION);
    protected_Timer.setSingleShot(true);
    cxk.y = ON_GROUNG_POS_Y;
    connect(&m_Timer,&QTimer::timeout,[=](){
        updatePosition();                                           //更新坐标
        collisionDetection();                                       //碰撞检测
        ui -> score -> setText("Score: "+QString::number(score));   //更新分数
        update();                                                   //刷新屏幕
    });
    connect(&add_Barrier_interval_Timer,&QTimer::timeout,[=](){
        addBarrier();
    });
    score = 0;
    ui -> score -> hide();
    sprint_once = false;
    sprint_twice = false;
}



Widget::~Widget()
{
    delete ui;
}


void Widget::on_startbtn_clicked()
{
    ui -> startbtn -> hide();
    ui -> label_2 -> hide();
    ui -> logo -> hide();
    ui -> infobtn -> hide();
    ui -> score -> show();

    playgame();
}
void Widget::on_infobtn_clicked()
{
    information *info = new information;
    info -> show();
}


void Widget::playgame(){
    score = 0;
    cxk.current_run_img = 0;
    m_Timer.start();                                          //启动计时器
    cxk.run_Timer.start();
    add_Barrier_interval_Timer.start();
}

void Widget::gameover(){
    m_Timer.stop();
    sprint_Timer.stop();
    sprint_interval_Timer.stop();
    add_Barrier_interval_Timer.stop();
    cxk.run_Timer.stop();
    protected_Timer.stop();
    ui -> groupBox -> setGeometry(340, 80, ui -> groupBox -> width(), ui -> groupBox -> height());
    //相对于父容器的x和y的坐标，以及groupbox的本身的高度和宽度
    ui -> finalscore -> setText("Score: "+QString::number(score));
    ui -> groupBox -> show();
}
void Widget::keyPressEvent(QKeyEvent *event){                                 /////////keyPressEvent
    QKeyEvent *key = (QKeyEvent*) event;
    QMediaPlayer *player = new QMediaPlayer;
    if(key -> key() == Qt::Key_Space){                        //空格键跳跃
        player -> setMedia(QUrl::fromLocalFile("D://Qt-projects//myitem1//res//jump.wav"));
        player -> setVolume(50);                              // 设置音量（可选）
        player -> play();
        cxk.jump();
    }
    if(key -> key() == Qt::Key_Shift){                        //shift键冲刺
        player->setMedia(QUrl::fromLocalFile("D://Qt-projects//myitem1//res//shift.wav"));
        player->setVolume(50);                                // 设置音量（可选）
        player->play();
        sprint();
    }
}
void Widget::mousePressEvent(QMouseEvent *event){                             /////////mousePressEvent
    if(event->button() == Qt::RightButton){
        sprint();
    }
}
void Widget::paintEvent(QPaintEvent *event){                                  ////////paintEvent             //////////Event
    QPainter painter(this);                                  //指定当前窗口为绘图设备
    painter.drawPixmap(0,0,width(),height(),background);     //绘制背景 是一个Qpixmap对象
    for(int i=0; i<20; i++){                                 //绘制地面高度
        painter.drawPixmap(grounds.mygrounds[i].positx,420,grounds.mygrounds[i].pixmap);
    }
    painter.drawPixmap(cxk.x,cxk.y,cxk.getImg());
    for(auto& barr:mybarriers)                               //绘制障碍物
    {

        painter.drawPixmap(barr->x,barr->y,barr->getImg());
    }

}
void Widget::addBarrier(){                        //生成障碍物
    srand((unsigned int)time(NULL)); //设置随机数生成器的种子,可以得到不同的随机数序列
    i = rand()%5;
    switch (i) {
    case 0:
        mybarriers.emplace_back(new barrier3);
        mybarriers.emplace_back(new chicken);
        break;
    case 1:
        mybarriers.emplace_back(new chicken);
        break;
    case 2:
        mybarriers.emplace_back(new barrier1);
        mybarriers.emplace_back(new chicken());
        break;
    case 3:
        mybarriers.emplace_back(new chicken());
        break;
    case 4:
        mybarriers.emplace_back(new barrier2);
        break;
    default:
        break;
    }
}


void Widget::updatePosition(){           //更新对象坐标
    grounds.calculatepositions();
    for(it = mybarriers.begin(); it != mybarriers.end();){
        if((*it) -> isOut()){
            it = mybarriers.erase(it);
        }
        else{
            (*it) -> updatePosition();
            it++;
        }
    }
    cxk.updatePositionY();
    if(this -> sprint_Timer.isActive()){                  //激活滑翔，实现滑翔
        grounds.calculatepositions();
        grounds.calculatepositions();
        for(auto& barr:mybarriers)
        {
            barr->updatePosition();
            barr->updatePosition();
        }
    }
}
void Widget::collisionDetection(){
    QMediaPlayer *player = new QMediaPlayer;
    int i = 0;
    for(it = mybarriers.begin();it != mybarriers.end();){
        i = (*it) -> collisionDetection(cxk.cxk_rect);     //障碍物rect是否与角色rect相交
        switch (i) {
        case 0:                       //无碰撞
            it++;
            break;
        case 1:{                      //障碍物123
            it++;
            if(!protected_Timer.isActive() && !sprint_Timer.isActive()){
                player->setMedia(QUrl::fromLocalFile("D://Qt-projects//myitem1//res//defeat.wav"));
                player->setVolume(50);  // 设置音量（可选）
                player->play();
                gameover();
            }
            break;
        }
        case 3:{                      //苹果
            score += 2;
            it = mybarriers.erase(it);

            player->setMedia(QUrl::fromLocalFile("D://Qt-projects//myitem1//res//success.wav"));
            player->setVolume(50);  // 设置音量（可选）
            player->play();
            break;
        }
        default:
            break;
        }
    }
}

void Widget::sprint(){
    if(!sprint_interval_Timer.isActive()){
        sprint_once=false;
        sprint_twice=false;
    }
    if(sprint_twice||(sprint_Timer.remainingTime()>90&&sprint_Timer.isActive())){
        //允许在一段冲刺的持续时间内进行二段冲刺
        return;
    }
    if(!sprint_once){
        sprint_once=true;
        sprint_Timer.start();
        sprint_interval_Timer.start();
    }
    else if(!sprint_twice){
        sprint_twice=true;
        sprint_Timer.start();
    }
}

void Widget::on_againbtn_clicked()
{
    ui -> groupBox -> hide();
    mybarriers.clear();
    cxk.y = ON_GROUNG_POS_Y;
    playgame();
}
