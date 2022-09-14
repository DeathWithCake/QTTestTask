#include "formwithline.h"
#include "ui_formwithline.h"

FormWithLine::FormWithLine(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormWithLine)
{
    ui->setupUi(this);

    connect(ui->btnSend, SIGNAL(clicked()), this, SLOT(printLine()));
}

FormWithLine::~FormWithLine()
{
    delete ui;
}

void FormWithLine::printLine()
{
    qDebug() << ui->lineEdit->text();
}

void FormWithLine::closeEvent(QCloseEvent *event)
{
    emit closeChild();
}
