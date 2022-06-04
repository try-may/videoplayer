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
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "mybutton.h"
#include "myslider.h"
#include "myvideowidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *openfile;
    QAction *close;
    QAction *fullscreen;
    QAction *playlist;
    QAction *play;
    QAction *preplay;
    QAction *nextplay;
    QAction *normal;
    QAction *speedup;
    QAction *slowdown;
    QAction *muted;
    QAction *volup;
    QAction *voldown;
    QAction *speed2x;
    QAction *speed4x;
    QAction *speed8x;
    QAction *actionzhuzhencaozuo;
    QAction *minus1_frame;
    QAction *plus1_frame;
    QAction *minus5_frame;
    QAction *plus5_frame;
    QAction *preview_switch;
    QAction *inf;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    MyVideoWidget *videowidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QWidget *widget_3;
    QGridLayout *gridLayout;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_2;
    MySlider *horizontalSlider;
    QLabel *label;
    Mybutton *playmodebtn;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    Mybutton *Prebtn;
    Mybutton *Playbtn;
    Mybutton *Nextbtn;
    Mybutton *Openbtn;
    QSpacerItem *horizontalSpacer;
    Mybutton *volumebtn;
    QSlider *VolumeSlider;
    Mybutton *Fullscreenbtn;
    Mybutton *Playlistbtn;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu_4;
    QMenu *menu_5;
    QStatusBar *statusbar;
    QDockWidget *PlaylistWidget;
    QWidget *dockWidgetContents_2;
    QVBoxLayout *verticalLayout_3;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QWidget *widget;
    QVBoxLayout *verticalLayout_4;
    QPushButton *Addsourcebtn;
    QPushButton *Delsourcebtn;
    QPushButton *ClearAllbtn;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1202, 609);
        openfile = new QAction(MainWindow);
        openfile->setObjectName(QString::fromUtf8("openfile"));
        close = new QAction(MainWindow);
        close->setObjectName(QString::fromUtf8("close"));
        fullscreen = new QAction(MainWindow);
        fullscreen->setObjectName(QString::fromUtf8("fullscreen"));
        playlist = new QAction(MainWindow);
        playlist->setObjectName(QString::fromUtf8("playlist"));
        play = new QAction(MainWindow);
        play->setObjectName(QString::fromUtf8("play"));
        preplay = new QAction(MainWindow);
        preplay->setObjectName(QString::fromUtf8("preplay"));
        nextplay = new QAction(MainWindow);
        nextplay->setObjectName(QString::fromUtf8("nextplay"));
        normal = new QAction(MainWindow);
        normal->setObjectName(QString::fromUtf8("normal"));
        speedup = new QAction(MainWindow);
        speedup->setObjectName(QString::fromUtf8("speedup"));
        slowdown = new QAction(MainWindow);
        slowdown->setObjectName(QString::fromUtf8("slowdown"));
        muted = new QAction(MainWindow);
        muted->setObjectName(QString::fromUtf8("muted"));
        volup = new QAction(MainWindow);
        volup->setObjectName(QString::fromUtf8("volup"));
        voldown = new QAction(MainWindow);
        voldown->setObjectName(QString::fromUtf8("voldown"));
        speed2x = new QAction(MainWindow);
        speed2x->setObjectName(QString::fromUtf8("speed2x"));
        speed4x = new QAction(MainWindow);
        speed4x->setObjectName(QString::fromUtf8("speed4x"));
        speed8x = new QAction(MainWindow);
        speed8x->setObjectName(QString::fromUtf8("speed8x"));
        actionzhuzhencaozuo = new QAction(MainWindow);
        actionzhuzhencaozuo->setObjectName(QString::fromUtf8("actionzhuzhencaozuo"));
        minus1_frame = new QAction(MainWindow);
        minus1_frame->setObjectName(QString::fromUtf8("minus1_frame"));
        plus1_frame = new QAction(MainWindow);
        plus1_frame->setObjectName(QString::fromUtf8("plus1_frame"));
        minus5_frame = new QAction(MainWindow);
        minus5_frame->setObjectName(QString::fromUtf8("minus5_frame"));
        plus5_frame = new QAction(MainWindow);
        plus5_frame->setObjectName(QString::fromUtf8("plus5_frame"));
        preview_switch = new QAction(MainWindow);
        preview_switch->setObjectName(QString::fromUtf8("preview_switch"));
        inf = new QAction(MainWindow);
        inf->setObjectName(QString::fromUtf8("inf"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        videowidget = new MyVideoWidget(centralwidget);
        videowidget->setObjectName(QString::fromUtf8("videowidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(3);
        sizePolicy.setHeightForWidth(videowidget->sizePolicy().hasHeightForWidth());
        videowidget->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(videowidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));

        verticalLayout->addWidget(videowidget);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_3);

        widget_3 = new QWidget(centralwidget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
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
        horizontalSlider->setMaximum(10000);
        horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(horizontalSlider);

        label = new QLabel(widget_4);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        playmodebtn = new Mybutton(widget_4);
        playmodebtn->setObjectName(QString::fromUtf8("playmodebtn"));

        horizontalLayout_2->addWidget(playmodebtn);


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
        Prebtn = new Mybutton(widget_2);
        Prebtn->setObjectName(QString::fromUtf8("Prebtn"));
        Prebtn->setEnabled(true);
        Prebtn->setMouseTracking(false);
        Prebtn->setFlat(false);

        horizontalLayout->addWidget(Prebtn);

        Playbtn = new Mybutton(widget_2);
        Playbtn->setObjectName(QString::fromUtf8("Playbtn"));

        horizontalLayout->addWidget(Playbtn);

        Nextbtn = new Mybutton(widget_2);
        Nextbtn->setObjectName(QString::fromUtf8("Nextbtn"));

        horizontalLayout->addWidget(Nextbtn);

        Openbtn = new Mybutton(widget_2);
        Openbtn->setObjectName(QString::fromUtf8("Openbtn"));

        horizontalLayout->addWidget(Openbtn);

        horizontalSpacer = new QSpacerItem(115, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        volumebtn = new Mybutton(widget_2);
        volumebtn->setObjectName(QString::fromUtf8("volumebtn"));

        horizontalLayout->addWidget(volumebtn);

        VolumeSlider = new QSlider(widget_2);
        VolumeSlider->setObjectName(QString::fromUtf8("VolumeSlider"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(VolumeSlider->sizePolicy().hasHeightForWidth());
        VolumeSlider->setSizePolicy(sizePolicy3);
        VolumeSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(VolumeSlider);

        Fullscreenbtn = new Mybutton(widget_2);
        Fullscreenbtn->setObjectName(QString::fromUtf8("Fullscreenbtn"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(Fullscreenbtn->sizePolicy().hasHeightForWidth());
        Fullscreenbtn->setSizePolicy(sizePolicy4);

        horizontalLayout->addWidget(Fullscreenbtn);

        Playlistbtn = new Mybutton(widget_2);
        Playlistbtn->setObjectName(QString::fromUtf8("Playlistbtn"));

        horizontalLayout->addWidget(Playlistbtn);


        gridLayout->addWidget(widget_2, 3, 0, 1, 1);


        verticalLayout->addWidget(widget_3);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1202, 26));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        menu_4 = new QMenu(menu_3);
        menu_4->setObjectName(QString::fromUtf8("menu_4"));
        menu_5 = new QMenu(menubar);
        menu_5->setObjectName(QString::fromUtf8("menu_5"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        PlaylistWidget = new QDockWidget(MainWindow);
        PlaylistWidget->setObjectName(QString::fromUtf8("PlaylistWidget"));
        PlaylistWidget->setAllowedAreas(Qt::RightDockWidgetArea);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QString::fromUtf8("dockWidgetContents_2"));
        verticalLayout_3 = new QVBoxLayout(dockWidgetContents_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        tabWidget = new QTabWidget(dockWidgetContents_2);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setContextMenuPolicy(Qt::CustomContextMenu);
        tabWidget->setElideMode(Qt::ElideLeft);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tabWidget->addTab(tab, QString());

        verticalLayout_3->addWidget(tabWidget);

        widget_5 = new QWidget(dockWidgetContents_2);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        horizontalLayout_3 = new QHBoxLayout(widget_5);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(widget_5);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy5);

        horizontalLayout_3->addWidget(label_2);

        widget = new QWidget(widget_5);
        widget->setObjectName(QString::fromUtf8("widget"));
        verticalLayout_4 = new QVBoxLayout(widget);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        Addsourcebtn = new QPushButton(widget);
        Addsourcebtn->setObjectName(QString::fromUtf8("Addsourcebtn"));

        verticalLayout_4->addWidget(Addsourcebtn);

        Delsourcebtn = new QPushButton(widget);
        Delsourcebtn->setObjectName(QString::fromUtf8("Delsourcebtn"));

        verticalLayout_4->addWidget(Delsourcebtn);

        ClearAllbtn = new QPushButton(widget);
        ClearAllbtn->setObjectName(QString::fromUtf8("ClearAllbtn"));

        verticalLayout_4->addWidget(ClearAllbtn);


        horizontalLayout_3->addWidget(widget);


        verticalLayout_3->addWidget(widget_5);

        PlaylistWidget->setWidget(dockWidgetContents_2);
        MainWindow->addDockWidget(Qt::RightDockWidgetArea, PlaylistWidget);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menu_3->menuAction());
        menubar->addAction(menu_5->menuAction());
        menu->addAction(openfile);
        menu->addAction(inf);
        menu->addAction(close);
        menu_2->addAction(fullscreen);
        menu_2->addSeparator();
        menu_2->addAction(playlist);
        menu_2->addAction(preview_switch);
        menu_3->addAction(play);
        menu_3->addSeparator();
        menu_3->addAction(preplay);
        menu_3->addAction(nextplay);
        menu_3->addSeparator();
        menu_3->addAction(menu_4->menuAction());
        menu_3->addAction(minus1_frame);
        menu_3->addAction(plus1_frame);
        menu_3->addAction(minus5_frame);
        menu_3->addAction(plus5_frame);
        menu_4->addAction(normal);
        menu_4->addAction(speedup);
        menu_4->addAction(slowdown);
        menu_4->addAction(speed2x);
        menu_4->addAction(speed4x);
        menu_4->addAction(speed8x);
        menu_5->addAction(muted);
        menu_5->addSeparator();
        menu_5->addAction(volup);
        menu_5->addAction(voldown);

        retranslateUi(MainWindow);

        Prebtn->setDefault(false);
        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        openfile->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
#if QT_CONFIG(shortcut)
        openfile->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        close->setText(QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255", nullptr));
        fullscreen->setText(QCoreApplication::translate("MainWindow", "\345\205\250\345\261\217", nullptr));
#if QT_CONFIG(shortcut)
        fullscreen->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+F", nullptr));
#endif // QT_CONFIG(shortcut)
        playlist->setText(QCoreApplication::translate("MainWindow", "\346\222\255\346\224\276\345\210\227\350\241\250", nullptr));
#if QT_CONFIG(shortcut)
        playlist->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+L", nullptr));
#endif // QT_CONFIG(shortcut)
        play->setText(QCoreApplication::translate("MainWindow", "\346\222\255\346\224\276/\346\232\202\345\201\234", nullptr));
#if QT_CONFIG(shortcut)
        play->setShortcut(QCoreApplication::translate("MainWindow", "Space", nullptr));
#endif // QT_CONFIG(shortcut)
        preplay->setText(QCoreApplication::translate("MainWindow", "\344\270\212\344\270\200\346\226\207\344\273\266", nullptr));
#if QT_CONFIG(shortcut)
        preplay->setShortcut(QCoreApplication::translate("MainWindow", "PgUp", nullptr));
#endif // QT_CONFIG(shortcut)
        nextplay->setText(QCoreApplication::translate("MainWindow", "\344\270\213\344\270\200\346\226\207\344\273\266", nullptr));
#if QT_CONFIG(shortcut)
        nextplay->setShortcut(QCoreApplication::translate("MainWindow", "PgDown", nullptr));
#endif // QT_CONFIG(shortcut)
        normal->setText(QCoreApplication::translate("MainWindow", "\346\255\243\345\270\270\351\200\237\345\272\246", nullptr));
        speedup->setText(QCoreApplication::translate("MainWindow", "\345\212\240\351\200\237", nullptr));
        slowdown->setText(QCoreApplication::translate("MainWindow", "\345\207\217\351\200\237", nullptr));
        muted->setText(QCoreApplication::translate("MainWindow", "\351\235\231\351\237\263", nullptr));
#if QT_CONFIG(shortcut)
        muted->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+M", nullptr));
#endif // QT_CONFIG(shortcut)
        volup->setText(QCoreApplication::translate("MainWindow", "\351\237\263\351\207\217+", nullptr));
#if QT_CONFIG(shortcut)
        volup->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl++", nullptr));
#endif // QT_CONFIG(shortcut)
        voldown->setText(QCoreApplication::translate("MainWindow", "\351\237\263\351\207\217-", nullptr));
#if QT_CONFIG(shortcut)
        voldown->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+-", nullptr));
#endif // QT_CONFIG(shortcut)
        speed2x->setText(QCoreApplication::translate("MainWindow", "2\345\200\215\351\200\237", nullptr));
        speed4x->setText(QCoreApplication::translate("MainWindow", "4\345\200\215\351\200\237", nullptr));
        speed8x->setText(QCoreApplication::translate("MainWindow", "8\345\200\215\351\200\237", nullptr));
        actionzhuzhencaozuo->setText(QCoreApplication::translate("MainWindow", "zhuzhencaozuo", nullptr));
        minus1_frame->setText(QCoreApplication::translate("MainWindow", "\344\270\2121\345\270\247", nullptr));
        plus1_frame->setText(QCoreApplication::translate("MainWindow", "\344\270\2131\345\270\247", nullptr));
        minus5_frame->setText(QCoreApplication::translate("MainWindow", "\344\270\2125\345\270\247", nullptr));
        plus5_frame->setText(QCoreApplication::translate("MainWindow", "\344\270\2135\345\270\247", nullptr));
        preview_switch->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\220\257/\345\205\263\351\227\255\350\247\206\351\242\221\351\242\204\350\247\210", nullptr));
        inf->setText(QCoreApplication::translate("MainWindow", "\350\216\267\345\217\226\344\277\241\346\201\257", nullptr));
#if QT_CONFIG(shortcut)
        inf->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+I", nullptr));
#endif // QT_CONFIG(shortcut)
        label_3->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "00:00:00/00:00:00", nullptr));
#if QT_CONFIG(tooltip)
        playmodebtn->setToolTip(QCoreApplication::translate("MainWindow", "\346\222\255\346\224\276\346\250\241\345\274\217", nullptr));
#endif // QT_CONFIG(tooltip)
        playmodebtn->setText(QCoreApplication::translate("MainWindow", "\346\222\255\346\224\276\346\250\241\345\274\217", nullptr));
#if QT_CONFIG(tooltip)
        Prebtn->setToolTip(QCoreApplication::translate("MainWindow", "\344\270\212\344\270\200\346\226\207\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
        Prebtn->setText(QCoreApplication::translate("MainWindow", "\344\270\212\344\270\200\346\233\262", nullptr));
#if QT_CONFIG(tooltip)
        Playbtn->setToolTip(QCoreApplication::translate("MainWindow", "\346\222\255\346\224\276/\346\232\202\345\201\234", nullptr));
#endif // QT_CONFIG(tooltip)
        Playbtn->setText(QCoreApplication::translate("MainWindow", "\346\232\202\345\201\234", nullptr));
#if QT_CONFIG(tooltip)
        Nextbtn->setToolTip(QCoreApplication::translate("MainWindow", "\344\270\213\344\270\200\346\226\207\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
        Nextbtn->setText(QCoreApplication::translate("MainWindow", "\344\270\213\344\270\200\346\233\262", nullptr));
#if QT_CONFIG(tooltip)
        Openbtn->setToolTip(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
        Openbtn->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
#if QT_CONFIG(tooltip)
        volumebtn->setToolTip(QCoreApplication::translate("MainWindow", "\351\237\263\351\207\217", nullptr));
#endif // QT_CONFIG(tooltip)
        volumebtn->setText(QCoreApplication::translate("MainWindow", "\351\237\263\351\207\217", nullptr));
#if QT_CONFIG(tooltip)
        VolumeSlider->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        Fullscreenbtn->setToolTip(QCoreApplication::translate("MainWindow", "\345\205\250\345\261\217", nullptr));
#endif // QT_CONFIG(tooltip)
        Fullscreenbtn->setText(QCoreApplication::translate("MainWindow", "\345\205\250\345\261\217", nullptr));
#if QT_CONFIG(tooltip)
        Playlistbtn->setToolTip(QCoreApplication::translate("MainWindow", "\346\222\255\346\224\276\345\210\227\350\241\250", nullptr));
#endif // QT_CONFIG(tooltip)
        Playlistbtn->setText(QCoreApplication::translate("MainWindow", "\346\222\255\346\224\276\345\210\227\350\241\250", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266(1)", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", "\350\247\202\347\234\213(2)", nullptr));
        menu_3->setTitle(QCoreApplication::translate("MainWindow", "\346\222\255\346\224\276(3)", nullptr));
        menu_4->setTitle(QCoreApplication::translate("MainWindow", "\346\222\255\346\224\276\351\200\237\345\272\246", nullptr));
        menu_5->setTitle(QCoreApplication::translate("MainWindow", "\345\243\260\351\237\263(4)", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "+\346\226\260\345\273\272\344\270\223\350\276\221", nullptr));
        label_2->setText(QString());
#if QT_CONFIG(tooltip)
        Addsourcebtn->setToolTip(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\345\215\225\344\270\252\346\210\226\345\244\232\344\270\252\346\226\207\344\273\266\345\210\260\344\270\223\350\276\221", nullptr));
#endif // QT_CONFIG(tooltip)
        Addsourcebtn->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240", nullptr));
#if QT_CONFIG(tooltip)
        Delsourcebtn->setToolTip(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244\344\270\223\350\276\221\351\207\214\345\215\225\344\270\252\346\226\207\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
        Delsourcebtn->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244", nullptr));
#if QT_CONFIG(tooltip)
        ClearAllbtn->setToolTip(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272\344\270\223\350\276\221\346\226\207\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
        ClearAllbtn->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
