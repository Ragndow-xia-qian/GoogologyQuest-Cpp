//
// Created by 37237 on 2024/1/18.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainInterface.h" resolved

#include <QGuiApplication>
#include <QScreen>
#include <QMessageBox>
#include <QPainter>
#include <QFileInfo>
#include <QElapsedTimer>

#include "../Header/maininterface.h"
#include "../Forms/ui_MainInterface.h"

namespace Interface {
    MainInterface::MainInterface(QWidget *parent, QFlags<Qt::WindowType> flags) :
            QMainWindow(parent, flags), ui(new Ui::MainInterface), label(new QLabel(this, flags)) {
        ui->setupUi(this);
        this->setStyleSheet("QMainWindow::titleBar { background-color: red; }");
    }

    void MainInterface::setFixed() {
        setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
        setFixedSize(this->width(), this->height());
    }

    QRect MainInterface::getScreen() {
        return MainInterface::getScreens()[0];
    }

    QList<QRect> MainInterface::getScreens() {
        QList<QRect> res;
        QList<QScreen *> screens = QGuiApplication::screens();
        for (auto &&screen: screens) {
            res.append(screen->geometry());
        }
        return res;
    }

    bool MainInterface::setIcon(const QString &file) {
        QFileInfo ico_file{file};
        if (!ico_file.isFile()) {
            return false;
        }
        QIcon icon{file};
        if (icon.isNull()) {
            return false;
        }
        this->setWindowIcon(icon);
        return true;
    }

    bool MainInterface::setBackground(const QString &file) {
        QFileInfo back_file{file};
        if (!back_file.isFile()) {
            return false;
        }
        QImage background{file};
        if (background.isNull()) {
            return false;
        }
        auto pixmap = QPixmap::fromImage(background);
        pixmap = pixmap.scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        label->setPixmap(pixmap);
        label->show();
        return true;
    }

    MainInterface::~MainInterface() {
        delete ui;
    }

    void MainInterface::closeEvent(QCloseEvent *event) {
        if (finished || QMessageBox::question(this, "提示", "你确定要关闭窗口吗") == QMessageBox::Yes) {
            event->accept();
            return;
        }
        event->ignore();
    }

    void MainInterface::paintEvent(QPaintEvent *event) {
//        QPainter painter(this);
//
//        painter.setPen(Qt::NoPen);
//        painter.setBrush(Qt::cyan);
//
//        painter.drawRect(rect());

        label->setGeometry(0, 0, this->width(), this->height());
        label->show();

        QMainWindow::paintEvent(event);
    }

    void MainInterface::sleep(unsigned int time) {
        QElapsedTimer t;
        t.start();
        while (t.elapsed() < time);
    }

    void MainInterface::finish() {
        this->finished = true;
    }
} // Interface
