#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QPushButton>
#include <QVBoxLayout>
#include <QVector>
#include "circularlist.h"
#include "workercpu.h"
#include "workercore.h"
#include "thread.h"

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    OpenGLWidget(unsigned int coreCount, QWidget *parent = nullptr);
    ~OpenGLWidget();
    void changeValues(int coreNum, CircularList<float> *list);

protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int width, int height) override;
    virtual void paintGL() override;

signals:
    void change(float);

public slots:
    void diagramChanged(unsigned int diagramID);
    void valueReceived(int workerID);

private:
    void logErrors(QOpenGLShaderProgram *shaderProgram, QString type);

    QColor backgroundColor;
    QOpenGLShaderProgram *shaderProgram;
    CircularList<float> *loadValues;
    unsigned int measuringCount;
    unsigned int diagram;
    QVector<Thread *> threads;
    QVector<Worker *> workers;

};


#endif // OPENGLWIDGET_H
