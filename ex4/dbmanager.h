#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QSqlDatabase>
#include <QSqlQuery>

class dbManager
{
public:
    dbManager(const QString& path);
    ~dbManager();
    bool isOpen();
private:
    QSqlDatabase dbase;
};

#endif // DBMANAGER_H
