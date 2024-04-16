//
// Created by 37237 on 2024/4/12.
//

#ifndef GOOGOLOGYQUEST_BUTTON_H
#define GOOGOLOGYQUEST_BUTTON_H

#include <QObject>
#include <QEvent>
#include <QPushButton>

namespace Control {

    class Button : public QPushButton {
    Q_OBJECT
    public:
        explicit Button(QWidget *parent, int siz);

        bool eventFilter(QObject *obj, QEvent *event) override;
    };

} // Control

#endif //GOOGOLOGYQUEST_BUTTON_H
