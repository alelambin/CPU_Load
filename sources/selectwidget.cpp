#include "../headers/selectwidget.h"

SelectWidget::SelectWidget(unsigned int cores, QWidget *parent) : QWidget(parent) {
    QScrollArea *scrollArea = new QScrollArea(this);

    QWidget *buttonWidget = new QWidget(scrollArea);
    for (unsigned int i = 0; i < cores + 1; ++i) {
        QString name = "ЦП " + (i == 0 ? "(общий)" : QString::number(i - 1));
        QPushButton *button = new QPushButton(name, buttonWidget);
        button->setMinimumWidth(buttonWidget->width());
        buttons.append(button);
    }
    curButtonID = 0;
    buttons[curButtonID]->setEnabled(false);

    QVBoxLayout *buttonLayout = new QVBoxLayout(this);
    for (auto *button : buttons) {
        buttonLayout->addWidget(button);
    }
    buttonLayout->setAlignment(Qt::AlignTop);
    buttonWidget->setLayout(buttonLayout);
    scrollArea->setWidget(buttonWidget);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(scrollArea);
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
