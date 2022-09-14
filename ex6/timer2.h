#ifndef TIMER2_H
#define TIMER2_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class Timer2;
}

class Timer2 : public QWidget
{
    Q_OBJECT

public:
    explicit Timer2(QWidget *parent = nullptr);
    ~Timer2();

private:
    Ui::Timer2 *ui;
    QTimer *timer;

signals:
    void closeTimer();

protected:
    void closeEvent(QCloseEvent *event);

public slots:
    void startTimer();
    void timerAlarm();
};

#endif // TIMER2_H
