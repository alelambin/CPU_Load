#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <fstream>
#include <stdexcept>
#include <QWidget>
#include "selectwidget.h"
#include "openglwidget.h"

class MainWidget : public QWidget {
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget() = default;

private:
    static int getCoreCount();

    SelectWidget *selectWidget;
    OpenGLWidget *openGLWidget;

};

#endif // MAINWIDGET_H
