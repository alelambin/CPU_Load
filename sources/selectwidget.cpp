#include "../headers/selectwidget.h"

SelectWidget::SelectWidget(unsigned int cores, QWidget *parent) : QWidget(parent) {
    for (unsigned int i = 0; i < cores + 1; ++i) {
        QString name = "ЦП " + (i == 0 ? "(общий)" : QString::number(i - 1));
        QPushButton *button = new QPushButton(name, this);
        buttons.append(button);
    }
    curButtonID = 0;
    buttons[curButtonID]->setEnabled(false);

    QVBoxLayout *layout = new QVBoxLayout(this);
    for (auto *button : buttons) {
        layout->addWidget(button);
    }
    layout->setAlignment(Qt::AlignTop);
    setLayout(layout);

    for (unsigned int i = 0; i < cores + 1; ++i) {
        connect(buttons[i], &QPushButton::released, [=] () {
            buttons[curButtonID]->setEnabled(true);
            buttons[i]->setEnabled(false);
            curButtonID = i;
            emit change(i);
        });
    }
}
