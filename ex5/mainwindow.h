#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "formwithline.h"
#include "formwithtable.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    FormWithLine *f1;
    FormWithTable *f2;

private:
    Ui::MainWindow *ui;

public slots:
    void showLineForm();
    void closeLineForm();
    void showTableForm();
    void closeTableForm();
};
#endif // MAINWINDOW_H
