#include "../headers/openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent) {
    backgroundColor = QWidget::palette().color(QWidget::backgroundRole());

    shaderProgram = new QOpenGLShaderProgram(this);

    measuringCount = 60;
    loadValues = new CircularList<float>(measuringCount);
    diagram = 0;
}

void OpenGLWidget::changeValues(int workerID, CircularList<float> *list) {
    if (diagram == workerID) {
        loadValues = list;
        update();
    }
}

void OpenGLWidget::initializeGL() {
    initializeOpenGLFunctions();

    if (!shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/diagram.vsh")) {
        logErrors(shaderProgram, "Vertex");
    }
    if (!shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/diagram.fsh")) {
        logErrors(shaderProgram, "Fragment");
    }
    if (!shaderProgram->link()) {
        logErrors(shaderProgram, "Program");
    }
    for (auto shader : shaderProgram->shaders()) {
        glDeleteShader(shader->shaderId());
    }
}

void OpenGLWidget::resizeGL(int width, int height) {
    glViewport(0, 0, (GLint) width, (GLint) height);
}

void OpenGLWidget::paintGL() {
    glViewport(0, 0, width(), height());
    glClearColor(backgroundColor.redF(), backgroundColor.greenF(), backgroundColor.blueF(), 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    QVector<float> values(measuringCount);
    for (unsigned int i = 0; i < measuringCount; ++i) {
        values[i] = (*loadValues)[i];
    }

    shaderProgram->bind();

    shaderProgram->setUniformValue("uMeasuringCount", measuringCount);

    shaderProgram->setAttributeArray("aValue", values.cbegin(), 1, 0);
    shaderProgram->enableAttributeArray("aValue");

    glLineWidth(5);
    glDrawArrays(GL_LINE_STRIP, 0, values.size());

    shaderProgram->disableAttributeArray("aValue");

    shaderProgram->release();
}

void OpenGLWidget::diagramChanged(unsigned int diagramID) {
    diagram = diagramID;
    update();
}

void OpenGLWidget::addedValue(CircularList<float> *result) {
    loadValues = result;
    update();
}

void OpenGLWidget::logErrors(QOpenGLShaderProgram *shaderProgram, QString type) {
    if (type != "Program") {
        const char *log = QString("ERROR: " + type + " shader not succesfully compiled").toLatin1();
        qDebug() << log;
        qDebug() << shaderProgram->log();
    } else {
        const char *log = QString("ERROR: " + type + " shader not succesfully linked").toLatin1();
        qDebug() << log;
        qDebug() << shaderProgram->log();
    }
}
