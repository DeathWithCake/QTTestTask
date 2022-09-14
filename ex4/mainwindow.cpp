#include "mainwindow.h"
#include "ui_mainwindow.h"

// structure for values ​​from the database
struct ForTable {
    QString textValue;
    int numValue;
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString path = "learn.db";
    QStringList newList;    // list of string values
    QList<ForTable> tableList;  // structure list
    int rows=0, cols=2; // number of required rows and columns for a tableModel

    textModel=new QStringListModel(this);   // model for qcombobox

    dbManager db(path); // db connection

    if(db.isOpen()) {
        QSqlQuery query("SELECT text_string, num_field FROM my_table"); // select all fields from table
        if(!query.exec())
            qDebug() << "failed: " << query.lastError();
        while (query.next()) {
            newList.append(query.value(0).toString());  // completing the string model

            // completing list for tableModel
            ForTable tableValues = {query.value(0).toString(), query.value(1).toInt()};
            tableList.append(tableValues);
        }

    }

    rows=tableList.size();  // number of rows for tableModel
    tableModel=new QStandardItemModel(rows, cols,this);
    int i=0;
    foreach(ForTable value, tableList) {    // model filling
        QModelIndex indexFirst = tableModel->index(i,0,QModelIndex());
        tableModel->setData(indexFirst, value.textValue);

        QModelIndex indexSecond = tableModel->index(i,1,QModelIndex());
        tableModel->setData(indexSecond, value.numValue);
        i++;
    }

    // text model display
    textModel->setStringList(newList);
    ui->comboBox->setModel(textModel);

    // table model display
    ui->tableView->setModel(tableModel);
    ui->tableView->resizeColumnsToContents();
}

MainWindow::~MainWindow()
{
    delete ui;
}
