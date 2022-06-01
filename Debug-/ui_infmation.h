/********************************************************************************
** Form generated from reading UI file 'infmation.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFMATION_H
#define UI_INFMATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include "mytable.h"

QT_BEGIN_NAMESPACE

class Ui_infmation
{
public:
    QVBoxLayout *verticalLayout;
    MyTable *tableWidget;
    QLabel *label;

    void setupUi(QDialog *infmation)
    {
        if (infmation->objectName().isEmpty())
            infmation->setObjectName(QString::fromUtf8("infmation"));
        infmation->resize(468, 597);
        verticalLayout = new QVBoxLayout(infmation);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tableWidget = new MyTable(infmation);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        verticalLayout->addWidget(tableWidget);

        label = new QLabel(infmation);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);


        retranslateUi(infmation);

        QMetaObject::connectSlotsByName(infmation);
    } // setupUi

    void retranslateUi(QDialog *infmation)
    {
        infmation->setWindowTitle(QCoreApplication::translate("infmation", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("infmation", "\346\262\241\346\234\211\346\211\223\345\274\200\347\232\204\346\226\207\344\273\266\357\274\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class infmation: public Ui_infmation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFMATION_H
