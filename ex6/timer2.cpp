#include "timer2.h"
#include "ui_timer2.h"

Timer2::Timer2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Timer2)
{
    ui->setupUi(this);

    connect(ui->btnStart, &QPushButton::clicked, this, &Timer2::startTimer);
}

Timer2::~Timer2()
{
    delete ui;
}

void Timer2::startTimer()
{
    timer = new QTimer();
    // this timer signaling every 30 seconds
    connect(timer, &QTimer::timeout, this, &Timer2::timerAlarm);
    timer->start(30000);
    qDebug() << "...";
}

void Timer2::timerAlarm()
{
    qDebug() << "Баста, карапузики, кончилися танцы";
}

void Timer2::closeEvent(QCloseEvent *event)
{
    emit closeTimer();
}
