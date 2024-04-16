/********************************************************************************
** Form generated from reading UI file 'maininterface.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAININTERFACE_H
#define UI_MAININTERFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

namespace Interface {

class Ui_MainInterface
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Interface__MainInterface)
    {
        if (Interface__MainInterface->objectName().isEmpty())
            Interface__MainInterface->setObjectName(QString::fromUtf8("Interface__MainInterface"));
        Interface__MainInterface->resize(400, 300);
        centralwidget = new QWidget(Interface__MainInterface);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        Interface__MainInterface->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Interface__MainInterface);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 400, 17));
        Interface__MainInterface->setMenuBar(menubar);
        statusbar = new QStatusBar(Interface__MainInterface);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Interface__MainInterface->setStatusBar(statusbar);

        retranslateUi(Interface__MainInterface);

        QMetaObject::connectSlotsByName(Interface__MainInterface);
    } // setupUi

    void retranslateUi(QMainWindow *Interface__MainInterface)
    {
        Interface__MainInterface->setWindowTitle(QCoreApplication::translate("Interface::MainInterface", "MainInterface", nullptr));
    } // retranslateUi

};

} // namespace Interface

namespace Interface {
namespace Ui {
    class MainInterface: public Ui_MainInterface {};
} // namespace Ui
} // namespace Interface

#endif // UI_MAININTERFACE_H
