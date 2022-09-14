#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QClipboard>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // скопировать значение из qTableView в буфер обмена. вставить в *.xlsx
    // скопировать значение из qTableWidget в буфер обмена. вставить в *.xlsx
    // скопировать значение из таблицы файла *.xlsx, заполнить таблицу qTableView
    // скопировать значение из таблицы файла *.xlsx, заполнить таблицу qTableWidget
    fillTView();
    fillTWidget();

    connect(ui->btnClearView, &QPushButton::clicked, this, &MainWindow::clearView);
    connect(ui->btnClearWidget, &QPushButton::clicked, this, &MainWindow::clearWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fillTView()
{
    tableModel=new QStandardItemModel(5, 3,this);
    srand(time(NULL));

    for(int row = 0; row < 5; row++)
        {
            for(int col = 0; col < 3; col++)
            {
                QModelIndex index  = tableModel->index(row,col,QModelIndex());
                int num = rand() % 101;
                tableModel->setData(index,num);
            }
        }

    ui->tableView->setModel(tableModel);
}

void MainWindow::fillTWidget()
{
    QStringList listForTable = { "Lorem","ipsum","dolor",
                                 "sit","amet", "consectetur",
                                 "adipiscing","elit","sed",
                                 "do", "eiusmod","tempor",
                                 "incididunt","ut","labore"};
    int i=0, j=0;
    ui->tableWidget->setRowCount(5);
    ui->tableWidget->setColumnCount(3);
    foreach(QString value, listForTable) {
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setText(value);
            ui->tableWidget->setItem(i,j,item);
            j++;
            if(j%3==0){
                i++;
                j=0;
            }
        }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->matches(QKeySequence::Copy))  // ctrl+c
    {
        if(ui->tableView->hasFocus())   // focused on the tableView
            viewToClipboard();
        else if(ui->tableWidget->hasFocus())    // focused on the tableWidget
            widgetToClipboard();
        else
            return;
    }
    else if(event->matches(QKeySequence::Paste))    // ctrl+v
    {
        if(ui->tableView->hasFocus())   // focused on the tableView
            clipboardToView();
        else if(ui->tableWidget->hasFocus())    // focused on the tableWidget
            clipboardToWidget();
        else
            return;
    }
    else
        return;
}

void MainWindow::viewToClipboard()  // copy tableView data to clipboard
{
    QAbstractItemModel *myModel = ui->tableView->model();
    QItemSelectionModel *model = ui->tableView->selectionModel();
    QModelIndexList indexList = model->selectedIndexes();   // list of indexes of selected cells
    if(indexList.size() < 1)
        return;

    QString copyTable;  // the string to be stored in the clipboard
    QModelIndex previous = indexList.first();   // need two indexes to separate the next row

    for(int i = 1; i < indexList.size(); i++) {
        QModelIndex index = indexList.at(i);    // current index

        copyTable.append(myModel->data(previous).toString());

        if(index.row() != previous.row())
            copyTable.append('\n'); // next row
        else
            copyTable.append('\t'); //next column
        previous = index;
    }

    copyTable.append(myModel->data(indexList.last()).toString());
    copyTable.append('\n');

    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(copyTable);
}

void MainWindow::widgetToClipboard()    // copy tableWidget data to clipboard
{
    QTableWidget *myTable = ui->tableWidget;
    QList<QTableWidgetItem*> items = myTable->selectedItems();
    int num = items.count();
    if(num<1)
        return;

    QString copyTable;  // the string to be stored in the clipboard
    QModelIndex previous = myTable->indexFromItem(items.first());

    for(int i=1; i<num; i++) {
        QModelIndex index = myTable->indexFromItem(items.at(i));

        copyTable.append(myTable->itemFromIndex(previous)->text());

        if(index.row() != previous.row())
            copyTable.append('\n'); // next row
        else
            copyTable.append('\t'); //next column
        previous = index;

    }

    copyTable.append(myTable->selectedItems().last()->text());
    copyTable.append('\n');

    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(copyTable);
}

void MainWindow::clearView()
{
    while(ui->tableView->model()->rowCount() >0)
        ui->tableView->model()->removeRow(0);
}

void MainWindow::clearWidget()
{
    ui->tableWidget->clear();
}

void MainWindow::clipboardToView()
{
    QClipboard *clipboard = QApplication::clipboard();
    QString copyTable = clipboard->text();  // get data from clipboard
    if(copyTable.isEmpty())
        return;

    int rows = 0, columns=0;    // number of rows and columns to create a model
    QString::const_iterator it = copyTable.begin();
    for (it; it != copyTable.end(); ++it) {
       if (*it == '\n')
         ++rows;
       if(rows==0 && *it == '\t')
           ++columns;
    }
    columns++;
    tableModel=new QStandardItemModel(rows, columns,this);  // model for new data

    int row=0, col=0;
    QString str;    // to write the value of one cell
    for(int i=0; i<copyTable.size(); i++) {
        if(copyTable.at(i) == '\t') {
            QModelIndex index  = tableModel->index(row,col,QModelIndex());
            tableModel->setData(index,str);
            str.clear();
            col++;
        }
        else if(copyTable.at(i) == '\n') {
            QModelIndex index  = tableModel->index(row,col,QModelIndex());
            tableModel->setData(index,str);
            str.clear();
            col=0;
            row++;
        }
        else
            str.append(copyTable.at(i));
    }
    ui->tableView->setModel(tableModel);
}

void MainWindow::clipboardToWidget()
{
    QClipboard *clipboard = QApplication::clipboard();
    QString copyTable = clipboard->text();  // get data from clipboard
    if(copyTable.isEmpty())
        return;

    int rows = 0, columns=0;    // number of rows and columns for tableWidget
    QString::const_iterator it = copyTable.begin();
    for (it; it != copyTable.end(); ++it) {
       if (*it == '\n')
         ++rows;
       if(rows==0 && *it == '\t')
           ++columns;
    }
    columns++;

    ui->tableWidget->setRowCount(rows);
    ui->tableWidget->setColumnCount(columns);

    int row=0, col=0;
    QString str;
    for(int i=0; i<copyTable.size(); i++) {
        if(copyTable.at(i) == '\t') {
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setText(str);
            ui->tableWidget->setItem(row,col,item);
            str.clear();
            col++;
        }
        else if(copyTable.at(i) == '\n') {
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setText(str);
            ui->tableWidget->setItem(row,col,item);
            str.clear();
            col=0;
            row++;
        }
        else
            str.append(copyTable.at(i));
    }
}
