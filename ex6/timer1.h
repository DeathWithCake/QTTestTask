#ifndef TIMER1_H
#define TIMER1_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class Timer1;
}

class Timer1 : public QWidget
{
    Q_OBJECT

public:
    explicit Timer1(QWidget *parent = nullptr);
    ~Timer1();

private:
    Ui::Timer1 *ui;
    QTimer *timer;

signals:
    void closeTimer();

protected:
    void closeEvent(QCloseEvent *event);

public slots:
    void startTimer();
    void timerAlarm();
};

#endif // TIMER1_H
