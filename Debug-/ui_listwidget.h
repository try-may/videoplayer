/********************************************************************************
** Form generated from reading UI file 'listwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISTWIDGET_H
#define UI_LISTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ListWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QHBoxLayout *horizontalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;

    void setupUi(QWidget *ListWidget)
    {
        if (ListWidget->objectName().isEmpty())
            ListWidget->setObjectName(QString::fromUtf8("ListWidget"));
        ListWidget->resize(400, 300);
        horizontalLayout = new QHBoxLayout(ListWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        dockWidget = new QDockWidget(ListWidget);
        dockWidget->setObjectName(QString::fromUtf8("dockWidget"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        horizontalLayout_2 = new QHBoxLayout(dockWidgetContents);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        tabWidget = new QTabWidget(dockWidgetContents);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());

        horizontalLayout_2->addWidget(tabWidget);

        dockWidget->setWidget(dockWidgetContents);

        horizontalLayout->addWidget(dockWidget);


        retranslateUi(ListWidget);

        QMetaObject::connectSlotsByName(ListWidget);
    } // setupUi

    void retranslateUi(QWidget *ListWidget)
    {
        ListWidget->setWindowTitle(QCoreApplication::translate("ListWidget", "Form", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("ListWidget", "Tab 1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("ListWidget", "Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ListWidget: public Ui_ListWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTWIDGET_H
