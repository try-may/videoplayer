#include "mytable.h"
#include "qheaderview.h"

MyTable::MyTable(QWidget *parent) :
    QTableWidget(parent)

{
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->setColumnCount(2);
    this->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Interactive);
    this->setColumnWidth(0,150);
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setHorizontalHeaderLabels(QStringList()<<"项目名"<<"时长");
    this->setSelectionBehavior(QAbstractItemView::SelectRows);

}

MyTable::~MyTable()
{

}
