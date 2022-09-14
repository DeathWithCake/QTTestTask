#include "formwithtable.h"
#include "ui_formwithtable.h"

FormWithTable::FormWithTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormWithTable)
{
    ui->setupUi(this);

    tableModel=new QStandardItemModel(8, 3,this);
    srand(time(NULL));

    for(int row = 0; row < 8; row++)
        {
            for(int col = 0; col < 3; col++)
            {
                QModelIndex index  = tableModel->index(row,col,QModelIndex());
                float num = -100.0 + (rand() / (RAND_MAX / (200.0)));
                tableModel->setData(index,num);
            }
        }

    ui->tableView->setModel(tableModel);
}

FormWithTable::~FormWithTable()
{
    delete ui;
}

void FormWithTable::closeEvent(QCloseEvent *event)
{
    emit closeChild();
}
