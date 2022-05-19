/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "myslider.h"
#include "myvideowidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    MyVideoWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_3;
    QGridLayout *gridLayout;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_2;
    MySlider *horizontalSlider;
    QLabel *label;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *Prebtn;
    QPushButton *Playbtn;
    QPushButton *Nextbtn;
    QPushButton *Openbtn;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *Fullscreenbtn;
    QSlider *verticalSlider;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QDockWidget *dockWidget_2;
    QWidget *dockWidgetContents_2;
    QVBoxLayout *verticalLayout_3;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *Addsourcebtn;
    QPushButton *Delsourcebtn;
    QPushButton *ClearAllbtn;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1126, 551);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new MyVideoWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(3);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));

        verticalLayout->addWidget(widget);

        widget_3 = new QWidget(centralwidget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy1);
        gridLayout = new QGridLayout(widget_3);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        widget_4 = new QWidget(widget_3);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        horizontalLayout_2 = new QHBoxLayout(widget_4);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSlider = new MySlider(widget_4);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(horizontalSlider);

        label = new QLabel(widget_4);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);


        gridLayout->addWidget(widget_4, 0, 0, 1, 2);

        widget_2 = new QWidget(widget_3);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(4);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy2);
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        Prebtn = new QPushButton(widget_2);
        Prebtn->setObjectName(QString::fromUtf8("Prebtn"));

        horizontalLayout->addWidget(Prebtn);

        Playbtn = new QPushButton(widget_2);
        Playbtn->setObjectName(QString::fromUtf8("Playbtn"));

        horizontalLayout->addWidget(Playbtn);

        Nextbtn = new QPushButton(widget_2);
        Nextbtn->setObjectName(QString::fromUtf8("Nextbtn"));

        horizontalLayout->addWidget(Nextbtn);

        Openbtn = new QPushButton(widget_2);
        Openbtn->setObjectName(QString::fromUtf8("Openbtn"));

        horizontalLayout->addWidget(Openbtn);

        pushButton_3 = new QPushButton(widget_2);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        horizontalLayout->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(widget_2);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        horizontalLayout->addWidget(pushButton_4);

        Fullscreenbtn = new QPushButton(widget_2);
        Fullscreenbtn->setObjectName(QString::fromUtf8("Fullscreenbtn"));

        horizontalLayout->addWidget(Fullscreenbtn);


        gridLayout->addWidget(widget_2, 3, 0, 1, 1);

        verticalSlider = new QSlider(widget_3);
        verticalSlider->setObjectName(QString::fromUtf8("verticalSlider"));
        verticalSlider->setMaximum(100);
        verticalSlider->setOrientation(Qt::Vertical);

        gridLayout->addWidget(verticalSlider, 3, 1, 1, 1);


        verticalLayout->addWidget(widget_3);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1126, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        dockWidget_2 = new QDockWidget(MainWindow);
        dockWidget_2->setObjectName(QString::fromUtf8("dockWidget_2"));
        dockWidget_2->setAllowedAreas(Qt::RightDockWidgetArea);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QString::fromUtf8("dockWidgetContents_2"));
        verticalLayout_3 = new QVBoxLayout(dockWidgetContents_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        tabWidget = new QTabWidget(dockWidgetContents_2);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setElideMode(Qt::ElideLeft);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tabWidget->addTab(tab, QString());

        verticalLayout_3->addWidget(tabWidget);

        widget_5 = new QWidget(dockWidgetContents_2);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        horizontalLayout_3 = new QHBoxLayout(widget_5);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        Addsourcebtn = new QPushButton(widget_5);
        Addsourcebtn->setObjectName(QString::fromUtf8("Addsourcebtn"));

        horizontalLayout_3->addWidget(Addsourcebtn);

        Delsourcebtn = new QPushButton(widget_5);
        Delsourcebtn->setObjectName(QString::fromUtf8("Delsourcebtn"));

        horizontalLayout_3->addWidget(Delsourcebtn);

        ClearAllbtn = new QPushButton(widget_5);
        ClearAllbtn->setObjectName(QString::fromUtf8("ClearAllbtn"));

        horizontalLayout_3->addWidget(ClearAllbtn);


        verticalLayout_3->addWidget(widget_5);

        dockWidget_2->setWidget(dockWidgetContents_2);
        MainWindow->addDockWidget(Qt::RightDockWidgetArea, dockWidget_2);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "00:00:00/00:00:00", nullptr));
        Prebtn->setText(QCoreApplication::translate("MainWindow", "\344\270\212\344\270\200\346\233\262", nullptr));
        Playbtn->setText(QCoreApplication::translate("MainWindow", "\346\232\202\345\201\234", nullptr));
        Nextbtn->setText(QCoreApplication::translate("MainWindow", "\344\270\213\344\270\200\346\233\262", nullptr));
        Openbtn->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "\345\207\217\351\200\237", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "\345\212\240\351\200\237", nullptr));
        Fullscreenbtn->setText(QCoreApplication::translate("MainWindow", "\345\205\250\345\261\217", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "+\346\226\260\345\273\272\344\270\223\350\276\221", nullptr));
        Addsourcebtn->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240", nullptr));
        Delsourcebtn->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244", nullptr));
        ClearAllbtn->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
