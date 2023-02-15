#ifndef SELECTWIDGET_H
#define SELECTWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QButtonGroup>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QVector>

class SelectWidget : public QWidget {
    Q_OBJECT

public:
    SelectWidget(unsigned int, QWidget *parent = nullptr);

signals:
    void change(unsigned int);

private:
    QVector<QPushButton *> buttons;
    int curButtonID;

};

#endif // SELECTWIDGET_H
