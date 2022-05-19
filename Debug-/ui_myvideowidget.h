/********************************************************************************
** Form generated from reading UI file 'myvideowidget.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYVIDEOWIDGET_H
#define UI_MYVIDEOWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyVideoWidget
{
public:

    void setupUi(QWidget *MyVideoWidget)
    {
        if (MyVideoWidget->objectName().isEmpty())
            MyVideoWidget->setObjectName(QString::fromUtf8("MyVideoWidget"));
        MyVideoWidget->resize(400, 300);

        retranslateUi(MyVideoWidget);

        QMetaObject::connectSlotsByName(MyVideoWidget);
    } // setupUi

    void retranslateUi(QWidget *MyVideoWidget)
    {
        MyVideoWidget->setWindowTitle(QCoreApplication::translate("MyVideoWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyVideoWidget: public Ui_MyVideoWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYVIDEOWIDGET_H
