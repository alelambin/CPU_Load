#include "../headers/mainwidget.h"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent) {
    int coreCount = getCoreCount();

    openGLWidget = new OpenGLWidget(coreCount, this);
    selectWidget = new SelectWidget(coreCount, this);
    selectWidget->setFixedWidth(150);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(selectWidget);
    layout->addWidget(openGLWidget);
    setLayout(layout);

    connect(selectWidget, SIGNAL(change(unsigned int)), openGLWidget, SLOT(diagramChanged(unsigned int)));
    connect(openGLWidget, SIGNAL(change(float)), selectWidget, SLOT(changedValue(float)));
}

int MainWidget::getCoreCount() {
    std::ifstream infoFile("/proc/cpuinfo");
    if (!infoFile.is_open()) {
        infoFile.close();
        throw std::runtime_error("Error: could not open /proc/cpuinfo file");
    }

    std::string line;
    int count = 0;
    while (std::getline(infoFile, line)) {
        if (line.find("processor") == 0) {
            count++;
        }
    }

    infoFile.close();
    return count;
}
