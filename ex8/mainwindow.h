#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ctime>
#include <QDir>
#include <QStandardItemModel>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QKeyEvent>

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

    void keyPressEvent(QKeyEvent * event);

    void viewToClipboard();
    void widgetToClipboard();

    void clipboardToView();
    void clipboardToWidget();

private slots:
    void clearView();
    void clearWidget();
};
#endif // MAINWINDOW_H
