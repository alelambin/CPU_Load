#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <fstream>
#include <stdexcept>
#include <QWidget>
#include <QVector>
#include "selectwidget.h"
#include "openglwidget.h"
#include "workercpu.h"
#include "workercore.h"
#include "thread.h"

class MainWidget : public QWidget {
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

signals:
    void addedValue(CircularList<float> *);

private:
    static int getCoreCount();

    SelectWidget *selectWidget;
    OpenGLWidget *openGLWidget;
    QVector<Worker *> workers;
    QVector<Worker::FunctionParam> params;
    QVector<Thread *> threads;

};

#endif // MAINWIDGET_H
