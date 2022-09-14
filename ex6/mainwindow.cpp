#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnT1, &QPushButton::clicked, this, &MainWindow::showTimer1);
    connect(ui->btnT2, &QPushButton::clicked, this, &MainWindow::showTimer2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showTimer1()
{
    t1 = new Timer1;
    hide();
    t1->show();
    connect(t1, &Timer1::closeTimer, this, &MainWindow::closeTimer1);
}

void MainWindow::closeTimer1()
{
    delete t1;
    show();
}

void MainWindow::showTimer2()
{
    t2 = new Timer2;
    hide();
    t2->show();
    connect(t2, &Timer2::closeTimer, this, &MainWindow::closeTimer2);
}

void MainWindow::closeTimer2()
{
    delete t2;
    show();
}
