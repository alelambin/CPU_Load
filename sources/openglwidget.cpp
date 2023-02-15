#include "../headers/openglwidget.h"

OpenGLWidget::OpenGLWidget(unsigned int coreCount, QWidget *parent) : QOpenGLWidget(parent) {
    backgroundColor = QWidget::palette().color(QWidget::backgroundRole());

    shaderProgram = new QOpenGLShaderProgram(this);

    measuringCount = 60;
    loadValues = new CircularList<float>(measuringCount, -1.0);
    diagram = 0;

    Worker *worker = new WorkerCPU();
    connect(worker, SIGNAL(newValue(int)), this, SLOT(valueReceived(int)));
    workers.append(worker);
    threads.append(new Thread(&WorkerCPU::start, &workers.last()));
    for (int i = 0; i < coreCount; ++i) {
        worker = new WorkerCore(i);
        connect(worker, SIGNAL(newValue(int)), this, SLOT(valueReceived(int)));
        workers.append(worker);
        threads.append(new Thread(&WorkerCore::start, &workers.last()));
    }
}

OpenGLWidget::~OpenGLWidget() {
    for (auto *thread : threads) {
        thread->cancel();
        delete thread;
    }
    for (auto &worker : workers) {
        delete worker;
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

    shaderProgram->bind();

    loadValues = workers[diagram]->results();

    shaderProgram->setUniformValue("uStartIndex", loadValues->index());
    shaderProgram->setUniformValue("uVertexCount", loadValues->length());

    shaderProgram->setAttributeArray("aValue", loadValues->getData(), 1, 0);
    shaderProgram->enableAttributeArray("aValue");

    glLineWidth(5);
    glDrawArrays(GL_LINE_STRIP, loadValues->index(), loadValues->length() - loadValues->index() + 1);
    glDrawArrays(GL_LINE_STRIP, 0, loadValues->index());

    shaderProgram->disableAttributeArray("aValue");

    shaderProgram->release();
}

void OpenGLWidget::diagramChanged(unsigned int diagramID) {
    diagram = diagramID;
    update();
}

void OpenGLWidget::valueReceived(int workerID) {
    if (diagram == workerID) {
        emit(change(loadValues->last()));
        update();
    }
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
