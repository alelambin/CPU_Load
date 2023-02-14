#include "../headers/mainwidget.h"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent) {
    int coreCount = getCoreCount();

    openGLWidget = new OpenGLWidget(this);
    selectWidget = new SelectWidget(coreCount, this);
    selectWidget->setFixedWidth(150);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(selectWidget);
    layout->addWidget(openGLWidget);
    setLayout(layout);

    connect(selectWidget, SIGNAL(change(unsigned int)), openGLWidget, SLOT(diagramChanged(unsigned int)));
    connect(this, SIGNAL(addedValue(CircularList<float> *)), openGLWidget, SLOT(addedValue(CircularList<float> *)));

    Worker *worker = new WorkerCPU();
    workers.append(worker);
    params.append({worker, openGLWidget});
    threads.append(new Thread(&WorkerCPU::start, &params.last()));
    for (int i = 0; i < coreCount; ++i) {
        worker = new WorkerCore(i);
        workers.append(worker);
        params.append({worker, openGLWidget});
        threads.append(new Thread(&WorkerCore::start, &params.last()));
    }
}

MainWidget::~MainWidget() {
    for (auto *thread : threads) {
        thread->cancel();
        delete thread;
    }
    for (auto &worker : workers) {
        delete worker;
    }
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

//DWORD WINAPI MainWidget::workerRun(LPVOID lpParam) {
//    WorkerFunctionParam *param = (WorkerFunctionParam *) lpParam;
//    Worker *worker = param->worker;
//    MainWidget *widget = param->widget;
//    while (true) {
//        worker->run();
//        emit widget->addedValue(worker->results());
//        Sleep(1000);
//    }
//    ExitThread(0);
//}
