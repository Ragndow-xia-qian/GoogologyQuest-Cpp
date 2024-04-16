//
// Created by 37237 on 2024/1/18.
//

#ifndef GOOGOLOGYQUEST_MAININTERFACE_H
#define GOOGOLOGYQUEST_MAININTERFACE_H

#include <QMainWindow>
#include <QRect>
#include <QList>
#include <QCloseEvent>
#include <QPaintEvent>
#include <QFlags>
#include <QLabel>

namespace Interface {
    QT_BEGIN_NAMESPACE
    namespace Ui { class MainInterface; }
    QT_END_NAMESPACE

    class MainInterface : public QMainWindow {
    Q_OBJECT

    public:
        explicit MainInterface(QWidget *parent = nullptr, QFlags<Qt::WindowType> flags = Qt::WindowFlags());

        void setFixed();

        [[nodiscard]] static QRect getScreen();

        [[nodiscard]] static QList<QRect> getScreens();

        bool setIcon(const QString &file);

        bool setBackground(const QString &file);

        static void sleep(unsigned int time);

        void finish();

        ~MainInterface() override;

    public slots:
        void closeEvent(QCloseEvent *event) override;

        void paintEvent(QPaintEvent *event) override;

    private:
        Ui::MainInterface *ui;
        QLabel *label;

        bool finished{};
    };
} // Interface

#endif //GOOGOLOGYQUEST_MAININTERFACE_H
