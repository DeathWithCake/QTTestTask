#ifndef FORMWITHLINE_H
#define FORMWITHLINE_H

#include <QWidget>

namespace Ui {
class FormWithLine;
}

class FormWithLine : public QWidget
{
    Q_OBJECT

public:
    explicit FormWithLine(QWidget *parent = nullptr);
    ~FormWithLine();

private:
    Ui::FormWithLine *ui;

signals:
    void closeChild();

protected:
    void closeEvent(QCloseEvent *event);

public slots:
    void printLine();
};

#endif // FORMWITHLINE_H
