#ifndef MYTABLE_H
#define MYTABLE_H

#include <QTableWidget>

namespace Ui {
class MyTable;
}

class MyTable : public QTableWidget
{
    Q_OBJECT

public:
    explicit MyTable(QWidget *parent = nullptr);
    ~MyTable();

private:

};

#endif // MYTABLE_H
