#include <QDebug>
#include <QSqlError>
#include "dbmanager.h"
#include "ui_mainwindow.h"

dbManager::dbManager(const QString &path)
{
    dbase = QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName(path);
    if (!dbase.open())
        qDebug() << "Error: does not open";
    else
        qDebug() << "open!";
}

bool dbManager::isOpen()
{
    return dbase.isOpen();
}

dbManager::~dbManager()
{
    if(dbase.isOpen())
        dbase.close();
}
