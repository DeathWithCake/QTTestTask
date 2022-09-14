#include "timer1.h"
#include "ui_timer1.h"

Timer1::Timer1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Timer1)
{
    ui->setupUi(this);

    connect(ui->btnStart, &QPushButton::clicked, this, &Timer1::startTimer);
}

Timer1::~Timer1()
{
    delete ui;
}

void Timer1::startTimer()
{
    ui->isOver->setText("...");
    int min=ui->minutes->text().toInt();
    int sec=ui->seconds->text().toInt();
    int time = (min*60 + sec) * 1000;

    timer = new QTimer();
    // this timer will go off once in <time> milliseconds
    timer->singleShot(time, this, &Timer1::timerAlarm);
}

void Timer1::timerAlarm()
{
    ui->isOver->setText("Время прошло!");
}

void Timer1::closeEvent(QCloseEvent *event)
{
    emit closeTimer();
}
