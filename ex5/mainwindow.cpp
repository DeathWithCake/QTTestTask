#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnOpenSecForm, SIGNAL(clicked()), this, SLOT(showLineForm()));
    connect(ui->btnOpenThirdForm, SIGNAL(clicked()), this, SLOT(showTableForm()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showLineForm()
{
    f1 = new FormWithLine;
    hide();
    f1->show();
    connect(f1, SIGNAL(closeChild()), this, SLOT(closeLineForm()));
}

void MainWindow::closeLineForm()
{
    f1->close();
    show();
    qDebug() << "Дочерняя форма закрыта";
}

void MainWindow::showTableForm()
{
    f2 = new FormWithTable;
    hide();
    f2->show();
    connect(f2, SIGNAL(closeChild()), this, SLOT(closeTableForm()));
}

void MainWindow::closeTableForm()
{
    f2->close();
    show();
    qDebug() << "Дочерняя форма закрыта";
}
