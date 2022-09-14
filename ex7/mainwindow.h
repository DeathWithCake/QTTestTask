#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileInfo>
#include <QDir>
#include <QStandardItemModel>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QStandardItemModel *tableModel;

private:
    Ui::MainWindow *ui;
    void fillTView();
    void fillTWidget();
    void saveTable(QString,QString);

private slots:
    void fileExist();
    void saveTView();
    void saveTWidget();
};
#endif // MAINWINDOW_H
