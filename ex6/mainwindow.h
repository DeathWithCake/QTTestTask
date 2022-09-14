#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "timer1.h"
#include "timer2.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Timer1 *t1;
    Timer2 *t2;

private:
    Ui::MainWindow *ui;

protected:
    void closeTimer2();

public slots:
    void showTimer1();
    void closeTimer1();
    void showTimer2();
};
#endif // MAINWINDOW_H
