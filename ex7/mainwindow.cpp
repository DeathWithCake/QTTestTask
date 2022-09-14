#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    fillTView();    // fill tableView
    fillTWidget();  // fill tableWidget

    connect(ui->btnCheckExist, &QPushButton::clicked, this, &MainWindow::fileExist);

    connect(ui->btnSaveTView, &QPushButton::clicked, this, &MainWindow::saveTView);
    connect(ui->btnSaveTWidget, &QPushButton::clicked, this, &MainWindow::saveTWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// checking for the existence of a file, the path to which the user specifies
void MainWindow::fileExist()
{
    QString path = ui->fileName->text();
    QFileInfo checkFile(path);
    if(checkFile.exists())
        ui->existCheckResult->setText("Существует");
    else
        ui->existCheckResult->setText("Не существует");
}

// tableView is filled with pseudo-random real numbers
void MainWindow::fillTView()
{
    tableModel=new QStandardItemModel(5, 5,this);
    srand(time(NULL));

    for(int row = 0; row < 5; row++)
        {
            for(int col = 0; col < 5; col++)
            {
                QModelIndex index  = tableModel->index(row,col,QModelIndex());
                float num = -100.0 + (rand() / (RAND_MAX / (200.0)));
                tableModel->setData(index,QString::number(num, 'G', 4));
            }
        }

    ui->tableView->setModel(tableModel);
}

// tableWidget is complited from a string list
void MainWindow::fillTWidget()
{
    QStringList listForTable = { "Lorem","ipsum","dolor","sit","amet",
                                 "consectetur","adipiscing","elit","sed","do",
                               "eiusmod","tempor","incididunt","ut","labore"};
    int i=0, j=0;
    ui->tableWidget->setRowCount(3);
    ui->tableWidget->setColumnCount(5);
    foreach(QString value, listForTable) {
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setText(value);
            ui->tableWidget->setItem(i,j,item);
            j++;
            if(j%5==0){
                i++;
                j=0;
            }
        }
}

void MainWindow::saveTable(QString tableType,QString tableName)
{
    // пусть к файлу + имя
    QString fullName = QCoreApplication::applicationDirPath() +"/"+tableName;
    QFileInfo checkFile(fullName);
    if(checkFile.exists())
        QFile(fullName).remove();

    {
    // создание соединения
    QSqlDatabase dbExcel = QSqlDatabase::addDatabase("QODBC","xls_connection");
    // название драйвера в ODBC-менеджере, имя и путь для создаваемого файла
    dbExcel.setDatabaseName("DRIVER={Microsoft Excel Driver (*.xls, *.xlsx, *.xlsm, *.xlsb)}; READONLY=FALSE; FIL={MS Excel};DBQ="+fullName);
    if (!dbExcel.open()) {
        qDebug() << dbExcel.lastError().text();
        return;
    }

    // создание таблицы
    QSqlQuery dbQuery(dbExcel);
    QString queryCreate;
    if(tableType=="View")
        queryCreate = "CREATE TABLE ["+tableName+"] ([num1] FLOAT, [num2] FLOAT, [num3] FLOAT, [num4] FLOAT, [num5] FLOAT)";
    else
        queryCreate = "CREATE TABLE ["+tableName+"] ([str1] STRING, [str2] STRING, [str3] STRING, [str4] STRING, [str5] STRING)";

    if(!dbQuery.exec(queryCreate))
        qDebug() << dbQuery.lastError();
    else {
        qDebug()<< "table created. inserting values...";
        dbQuery.clear();

        int rows = 0, columns = 0;

        // заполнение таблицы
        if(tableType=="View") {
            rows = ui->tableView->model()->rowCount();
            columns = ui->tableView->model()->columnCount();

            QTableView *myTable = ui->tableView;
            QModelIndex myIndex;

            for(int i=0; i < rows; i++) {
                QString queryInsert = "INSERT INTO "+tableName+"([num1],[num2],[num3],[num4],[num5]) VALUES(";
                for(int j=0; j < columns; j++) {
                    myIndex = myTable->model()->index(i, j, QModelIndex());
                    queryInsert +=(myTable->model()->data(myIndex)).toString();
                    if(j<columns-1)
                        queryInsert+=+",";
                }
                queryInsert+=");";
                if(!dbQuery.exec(queryInsert))
                    qDebug() << dbQuery.lastError();
                else
                    qDebug() << i << "row was inserted";
            }
        }

        else {
            rows = ui->tableWidget->rowCount();
            columns = ui->tableWidget->columnCount();

            QTableWidget *myTable = ui->tableWidget;

            for(int i=0; i < rows; i++) {
                QString queryInsert = "INSERT INTO "+tableName+"([str1], [str2], [str3], [str4], [str5]) VALUES('";
                for(int j=0; j < columns; j++) {
                    queryInsert +=(myTable->item(i, j))->text();
                    if(j<columns-1)
                        queryInsert+=+"','";
                }
                queryInsert+="');";
                qDebug() << queryInsert;
                if(!dbQuery.exec(queryInsert))
                    qDebug() << dbQuery.lastError();
                else
                    qDebug() << i << "row was inserted";
            }
        }

    }
    dbExcel.close();
    }

    QSqlDatabase::removeDatabase("xls_connection");
}

void MainWindow::saveTView()
{
    QString tableName = ui->tViewName->text()+"View";
    ui->tViewSaveResult->setText("Файл сохранен под названием: " + tableName);
    saveTable("View", tableName);
}

void MainWindow::saveTWidget()
{
    QString tableName = ui->tWidgetName->text() +"Widget";
    ui->tWidgetSaveResult->setText("Файл сохранен под названием: " + tableName);
    saveTable("Widget", tableName);
}
