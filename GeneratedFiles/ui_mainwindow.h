/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Tue Mar 20 15:47:30 2018
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QScrollArea>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QTreeView>
#include <QtGui/QTreeWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QAction *openAction;
    QAction *PanAction;
    QAction *NewAction;
    QAction *MagnifyAction;
    QAction *ReductionAction;
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QTreeView *treeView;
    QTreeWidget *treeWidget;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QGraphicsView *graphicsView;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QString::fromUtf8("MainWindowClass"));
        MainWindowClass->resize(1015, 827);
        openAction = new QAction(MainWindowClass);
        openAction->setObjectName(QString::fromUtf8("openAction"));
        PanAction = new QAction(MainWindowClass);
        PanAction->setObjectName(QString::fromUtf8("PanAction"));
        NewAction = new QAction(MainWindowClass);
        NewAction->setObjectName(QString::fromUtf8("NewAction"));
        MagnifyAction = new QAction(MainWindowClass);
        MagnifyAction->setObjectName(QString::fromUtf8("MagnifyAction"));
        ReductionAction = new QAction(MainWindowClass);
        ReductionAction->setObjectName(QString::fromUtf8("ReductionAction"));
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        treeView = new QTreeView(centralWidget);
        treeView->setObjectName(QString::fromUtf8("treeView"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(treeView->sizePolicy().hasHeightForWidth());
        treeView->setSizePolicy(sizePolicy);
        treeView->setMinimumSize(QSize(300, 0));

        gridLayout_2->addWidget(treeView, 1, 0, 1, 1);

        treeWidget = new QTreeWidget(centralWidget);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        sizePolicy.setHeightForWidth(treeWidget->sizePolicy().hasHeightForWidth());
        treeWidget->setSizePolicy(sizePolicy);
        treeWidget->setMinimumSize(QSize(300, 0));

        gridLayout_2->addWidget(treeWidget, 0, 0, 1, 1);

        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 684, 727));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(scrollAreaWidgetContents->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents->setSizePolicy(sizePolicy1);
        gridLayout = new QGridLayout(scrollAreaWidgetContents);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        graphicsView = new QGraphicsView(scrollAreaWidgetContents);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setMaximumSize(QSize(1677215, 1677215));
        graphicsView->setSceneRect(QRectF(0, 0, 0, 0));

        gridLayout->addWidget(graphicsView, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout_2->addWidget(scrollArea, 0, 1, 2, 1);

        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1015, 26));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        MainWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindowClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindowClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindowClass->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(openAction);
        mainToolBar->addAction(NewAction);
        mainToolBar->addAction(PanAction);
        mainToolBar->addAction(MagnifyAction);
        mainToolBar->addAction(ReductionAction);

        retranslateUi(MainWindowClass);

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "MainWindow", 0, QApplication::UnicodeUTF8));
        openAction->setText(QApplication::translate("MainWindowClass", "\346\211\223\345\274\200\345\233\276\345\203\217(&O)", 0, QApplication::UnicodeUTF8));
        PanAction->setText(QApplication::translate("MainWindowClass", "\346\274\253\346\270\270", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        PanAction->setToolTip(QApplication::translate("MainWindowClass", "\345\233\276\345\203\217\346\274\253\346\270\270", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        NewAction->setText(QApplication::translate("MainWindowClass", "\346\226\260\345\273\272", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        NewAction->setToolTip(QApplication::translate("MainWindowClass", "\346\226\260\345\273\272\345\233\276\345\203\217", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        MagnifyAction->setText(QApplication::translate("MainWindowClass", "\346\224\276\345\244\247", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        MagnifyAction->setToolTip(QApplication::translate("MainWindowClass", "\345\233\276\345\203\217\346\224\276\345\244\247", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        ReductionAction->setText(QApplication::translate("MainWindowClass", "\347\274\251\345\260\217", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ReductionAction->setToolTip(QApplication::translate("MainWindowClass", "\345\233\276\345\203\217\347\274\251\345\260\217", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        menu->setTitle(QApplication::translate("MainWindowClass", "\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
