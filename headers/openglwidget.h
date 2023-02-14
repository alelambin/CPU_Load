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

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    OpenGLWidget(QWidget *parent = nullptr);
    void changeValues(int coreNum, CircularList<float> *);

protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int width, int height) override;
    virtual void paintGL() override;

public slots:
    void diagramChanged(unsigned int);
    void addedValue(CircularList<float> *);

private:
    void logErrors(QOpenGLShaderProgram *shaderProgram, QString type);

    QColor backgroundColor;
    QOpenGLShaderProgram *shaderProgram;
    CircularList<float> *loadValues;
    unsigned int measuringCount;
    unsigned int diagram;

};


#endif // OPENGLWIDGET_H
