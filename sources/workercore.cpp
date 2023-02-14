#include "../headers/workercore.h"

WorkerCore::WorkerCore(int core, unsigned int listSize) : core(core) {
    cpuLoadValues = new CircularList<float>(listSize);
    stat = readStat(core + 1);
}

WorkerCore::~WorkerCore() {
    delete cpuLoadValues;
}

int WorkerCore::id() const {
    return core + 1;
}

CircularList<float> *WorkerCore::results() const {
    return cpuLoadValues;
}

void WorkerCore::run() {
    cpuLoadValues->append(getLoad());
}

void *WorkerCore::start(void *data) {
    auto *param = (Worker::FunctionParam *) data;
    Worker *worker = param->worker;
    OpenGLWidget *widget = param->widget;
    while (true) {
        worker->run();
        widget->changeValues(worker->id(), worker->results());
        sleep(1);
    }
}

float WorkerCore::getLoad() {
    CPUStat newStat = readStat(core + 1);
    float load = calculateLoad(stat, newStat);
    stat = newStat;
    return load;
}
