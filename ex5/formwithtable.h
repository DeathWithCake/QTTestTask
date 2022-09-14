#ifndef FORMWITHTABLE_H
#define FORMWITHTABLE_H

#include <QWidget>
#include <QStandardItemModel>

namespace Ui {
class FormWithTable;
}

class FormWithTable : public QWidget
{
    Q_OBJECT

public:
    explicit FormWithTable(QWidget *parent = nullptr);
    ~FormWithTable();

    QStandardItemModel *tableModel;

signals:
    void closeChild();

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::FormWithTable *ui;
};

#endif // FORMWITHTABLE_H
