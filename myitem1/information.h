#ifndef INFORMATION_H
#define INFORMATION_H

#include <QWidget>

namespace Ui {
class information;
}

class information : public QWidget
{
    Q_OBJECT

public:
    explicit information(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    QPixmap background;
    ~information();

private slots:
    void on_backbtn_clicked();


private:
    Ui::information *ui;

};

#endif // INFORMATION_H
