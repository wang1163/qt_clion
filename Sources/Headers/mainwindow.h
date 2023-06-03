//
// Created by Lenovo on 2023/6/2.
//

#ifndef QT_CLION_MAINWINDOW_H
#define QT_CLION_MAINWINDOW_H

#include <QWidget>
#include <QKeyEvent>
#include "QTimer"
#include "QPainter"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

//方向
enum Direct{
    UP,
    DOWN,
    LEFT,
    RIGHT
};
class MainWindow : public QWidget {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    //按键处理
    void keyPressEvent(QKeyEvent *event);
    //绘图渲染
    void paintEvent(QPaintEvent *event);

protected slots:
    void timeout();
protected:
    void addtop();
    void addbot();
    void addleft();
    void addright();
    void deleteLast();
    void addNewFood();

private:
    Ui::MainWindow *ui;
    int move_flag=UP;
    bool gameStart= false;
    //定时器
    QTimer *timer;
    //超时时间
    int overtime=100;
    //蛇
    QList <QRectF> snake;
    //食物
    QRectF foodNode;
    //小方块
    int snakeWidth=20;
    int snakeHeight=20;


};



#endif //QT_CLION_MAINWINDOW_H
