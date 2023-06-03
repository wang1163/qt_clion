//
// Created by Lenovo on 2023/6/2.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "Headers/mainwindow.h"
#include "Forms/ui_MainWindow.h"


MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    //使用定时器
    timer=new QTimer();
    //信号槽
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
    resize(1080,810);
    //初始化蛇
    QRectF rectF(300,300,snakeWidth,snakeHeight);
    snake.append(rectF);
    addtop();
    addtop();
    //初始化奖品
    addNewFood();
}

MainWindow::~MainWindow() {
    delete ui;
}

//方向控制
void MainWindow::keyPressEvent(QKeyEvent *event) {
    switch(event->key()){
        case Qt::Key_Up:
            if(move_flag!=DOWN)
                move_flag=UP;
            break;
        case Qt::Key_Down:
            if(move_flag!=UP)
                move_flag=DOWN;
            break;
        case Qt::Key_Left:
            if(move_flag!=RIGHT)
                move_flag=LEFT;
            break;
        case Qt::Key_Right:
            if(move_flag!=LEFT)
                move_flag=RIGHT;
            break;
            //暂停键
        case Qt::Key_Space:
            if(!gameStart){
                gameStart=true;
                timer->start(overtime);
            }

            else{
                gameStart=false;
                timer->stop();
                update();
            }
            break;
        default:
            break;
    }
}

void MainWindow::timeout() {
    int count=1;
    //判断蛇吃到食物
    if(snake[0].intersects(foodNode)){
        count++;
        addNewFood();
    }
    while(count--){
        switch(move_flag){
            case UP:
                addtop();
                break;
            case DOWN:
                addbot();
                break;
            case LEFT:
                addleft();
                break;
            case RIGHT:
                addright();
                break;
            default:
                break;
        }
    }
    deleteLast();
    update();
}

//绘图
void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPen pen;
    QBrush brush;
    //背景图片
    QPixmap pix;
    pix.load(R"(G:\qt_clion\Sources\picture\background.jpg)");
    painter.drawPixmap(0,0,1080,810,pix);
    //暂停
    if(!gameStart){
        QPixmap pix2;
        pix2.load(R"(G:\qt_clion\Sources\picture\pause.png)");
        painter.drawPixmap(400,200,300,300,pix2);
    }else{
        //snake
        pen.setColor(Qt::black);
        brush.setColor(Qt::darkGreen);
        brush.setStyle(Qt::SolidPattern);
        painter.setPen(pen);
        painter.setBrush(brush);
        for (const auto & i : snake) {
            painter.drawRect(i);
        }
        //food
        pen.setColor(Qt::black);
        brush.setColor(Qt::darkBlue);
        brush.setStyle(Qt::SolidPattern);
        painter.setPen(pen);
        painter.setBrush(brush);
        painter.drawEllipse(foodNode);
    }
}

void MainWindow::addtop() {
    QPointF leftTop;
    QPointF rightBot;
    if((snake[0].y()-snakeHeight)>=0){
        leftTop=QPointF(snake[0].x(),snake[0].y()-snakeHeight);
        rightBot=snake[0].topRight();
    }else{
        leftTop=QPointF(snake[0].x(),this->height()-snakeHeight);
        rightBot=QPointF(snake[0].x()+snakeWidth,this->height());
    }
    snake.insert(0,QRectF(leftTop,rightBot));
}

void MainWindow::addbot() {
    QPointF leftTop;
    QPointF rightBot;
    if((snake[0].y()+2*snakeHeight)>this->height()){
        leftTop=QPointF(snake[0].x(),0);
        rightBot=QPointF(snake[0].x()+snakeWidth,snakeHeight);
    }else{
        leftTop=snake[0].bottomLeft();
        rightBot=snake[0].bottomRight()+QPointF(0,snakeHeight);
    }
    snake.insert(0,QRectF(leftTop,rightBot));
}

void MainWindow::addleft() {
    QPointF leftTop;
    QPointF rightBot;
    if((snake[0].x()-snakeWidth)<0){
        leftTop=QPointF(this->width()-snakeWidth,snake[0].y());
    }else{
        leftTop=snake[0].topLeft()-QPointF(snakeWidth,0);
    }
    rightBot=leftTop+QPointF(snakeWidth,snakeHeight);
    snake.insert(0,QRectF(leftTop,rightBot));

}

void MainWindow::addright() {
    QPointF leftTop;
    QPointF rightBot;
    if((snake[0].x()-snakeWidth)> this->width()){
        leftTop=QPointF(0,snake[0].y());
    }else{
        leftTop=snake[0].topRight();
    }
    rightBot=leftTop+QPointF(snakeWidth,snakeHeight);
    snake.insert(0,QRectF(leftTop,rightBot));
}

void MainWindow::deleteLast() {
    snake.removeLast();
}

void MainWindow::addNewFood() {
    foodNode=QRectF(qrand()%(this->width()/20)*20,qrand()%(this->height()/30)*30,snakeWidth,snakeHeight);
}
