#include <QFileDialog>
#include <QSettings>
#include "mainwindow.h"
#include "ui_mainwindow.h"

QSettings settings("first_set.ini", QSettings::IniFormat);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // data group with form parameters
    settings.setValue("FormParams/widthF", 400);
    settings.setValue("FormParams/heightF", 400);

    connect(ui->btnOpenFile, SIGNAL(clicked()), this, SLOT(openFile()));
    connect(ui->btnPrintSettings, SIGNAL(clicked()), this, SLOT(printSettings()));
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text files (*.txt);; All files (*.*)"));
    QByteArray data;
    QFile txtFile(fileName);

    // filling textEdit with text from a file
    if(txtFile.open(QIODevice::ReadOnly)) {
        ui->fileName->setText(QFileInfo(txtFile).fileName());   // display filename without path
        data = txtFile.readAll();
        ui->textEdit->setText(data);
        txtFile.close();
    }
    // data group containing the path of the file and its contents
    settings.setValue("FileParams/path", fileName);
    settings.setValue("FileParams/content", data);
}

// output to console data from the settings file
void MainWindow::printSettings()
{
    qDebug() << "width: " << settings.value("FormParams/widthF");
    qDebug() << "height: " << settings.value("FormParams/heightF");
    qDebug() << "file path: " << settings.value("FileParams/path");
    qDebug() << "file content: " << settings.value("FileParams/content");
}

