#ifndef INFMATION_H
#define INFMATION_H

#include <QDialog>
#include<QGridLayout>
#include<QTextEdit>
namespace Ui {
class infmation;
}

class infmation : public QDialog
{
    Q_OBJECT

public:
    explicit infmation(QWidget *parent = nullptr,QString nowpath="");
    ~infmation();
    bool initTextEdit(QString nowpath);     //初始化文本编译器
    void initLayout();     //初始化布局管理器
private:
    Ui::infmation *ui;
    QTextEdit *m_textEdit;  //显示
    QGridLayout *m_layout;  //布局管理器
};

#endif // INFMATION_H
