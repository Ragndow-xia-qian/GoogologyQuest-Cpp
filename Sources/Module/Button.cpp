//
// Created by 37237 on 2024/4/12.
//
#include <QObject>
#include <QWidget>
#include <QEvent>
#include <QPushButton>
#include <QMouseEvent>
#include <QDebug>

#include "../Header/Button.h"

namespace Control {
    Button::Button(QWidget *parent, int siz): QPushButton(parent) {
        this->setMouseTracking(true);
        this->installEventFilter(this);

        this->setStyleSheet("QPushButton{"
                                "color:rgb(0,0,0);"
                                "border：none;"
                                "background-color:transparent"
                                "}");

        QFont font;
        font.setPointSize(siz);
        font.setFamily("华文彩云");
        this->setFont(font);
    }

    bool Button::eventFilter(QObject *obj, QEvent *event) {
        if (obj == this) {
            if (event->type() == QEvent::Enter) {
                this->setStyleSheet("QPushButton{"
                                    "background-color: rgba(128, 128, 128, 70);"
                                    "}");
            } else if (event->type() == QEvent::Leave) {
                this->setStyleSheet("QPushButton{background-color:transparent}");
            }
        }

        return QWidget::eventFilter(obj, event);
    }
} // Control