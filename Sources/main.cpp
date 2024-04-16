/**
  ******************************************************************************
  * @file           : main.cpp
  * @author         : 夏浅
  * @brief          : None
  * @attention      : None
  * @date           : 2024/1/19
  ******************************************************************************
  */
#include <QApplication>
#include <QRect>
#include <QDebug>
#include <QScreen>
#include <QLabel>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QTimer>
#include <QDateTime>

#include "Header/maininterface.h"
#include "Header/Button.h"

#define LOG_REDIRECT

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    qInstallMessageHandler((QtMessageHandler) [](
            QtMsgType type,
            const QMessageLogContext &context,
            const QString &msg) {
        QString txt;
        switch (type) {
            case QtDebugMsg:
                txt = QString("Debug: %1").arg(msg);
                break;
            case QtWarningMsg:
                txt = QString("Warning: %1").arg(msg);
                break;
            case QtInfoMsg:
                txt = QString("Info: %1").arg(msg);
                break;
            case QtCriticalMsg:
                txt = QString("Critical: %1").arg(msg);
                break;
            case QtFatalMsg:
                txt = QString("Fatal: %1").arg(msg);
                break;
        }

#ifdef LOG_REDIRECT
        QFile outFile("log/logging.log");
        outFile.open(QIODevice::WriteOnly | QIODevice::Append);
        QTextStream ts(&outFile);
        ts << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ") << txt << endl;
#else
        QString ss = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ") + txt;
        qInfo() << ss.toStdString().c_str();
#endif
    });

    Interface::MainInterface window;

    window.setWindowTitle("Googology Quest");

    if (window.setIcon("Resources/images/icon.ico")) {
        qInfo() << "Succeed at setting icon" << endl;
    } else {
        qWarning() << "Failed at setting icon" << endl;
    }

    QRect windowGeometry = Interface::MainInterface::getScreen();
    int screenWidth = windowGeometry.width();
    int screenHeight = windowGeometry.height();

    windowGeometry.setTopLeft(QPoint(screenWidth / 4, screenHeight / 4));
    windowGeometry.setBottomRight(QPoint(screenWidth / 4 * 3, screenHeight / 4 * 3));

    window.setGeometry(windowGeometry);
    window.setFixed();

    if (window.setBackground("Resources/images/background.jpg")) {
        qInfo() << "Succeed at setting background" << endl;
    } else {
        qWarning() << "Failed at setting background" << endl;
    }

    QLabel title(&window);

    {
        title.setAlignment(Qt::AlignCenter);
        title.setText("Googology Quest");
        title.resize(window.width() / 4 * 3, window.height() / 5);

        auto title_geometry = title.geometry();
        title_geometry.setX((window.width() - title_geometry.width()) / 2);
        title_geometry.setY(0);
        title.setGeometry(title_geometry);

        QFont font;
        font.setPointSize(37);
        font.setFamily("华文彩云");
        title.setFont(font);

        QPalette pe;
        pe.setColor(QPalette::WindowText, Qt::gray);
        title.setPalette(pe);
    }

    title.show();

    Control::Button startGame(&window, 37);

    {
        startGame.setText("Start!");

        auto button_geometry = startGame.geometry();
        button_geometry.setLeft((window.width() - window.width() / 10 * 9) / 2);
        button_geometry.setRight(button_geometry.left() + window.width() / 2);
        button_geometry.setTop(window.height() / 5 * 3);
        button_geometry.setBottom(button_geometry.top() + window.height() / 5);
        startGame.setGeometry(button_geometry);

        static QPropertyAnimation animation(&window, "windowOpacity");

        auto event = [&] {
            qDebug() << "Clicked" << endl;

            animation.setDuration(1000);

            animation.setKeyValueAt(0, 1);
            animation.setKeyValueAt(0.5, 0);
            animation.setKeyValueAt(1, 0);

//            animation.setLoopCount(-1);
            animation.start();

            QTimer::singleShot(1100, [&]() {
                window.finish();
                window.close();
            });
        };

        QObject::connect(&startGame, &QPushButton::clicked, event);

        startGame.installEventFilter(&window);
    }

    startGame.show();

    window.show();

    return QApplication::exec();
}
