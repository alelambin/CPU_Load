#include "../headers/workercpu.h"

WorkerCPU::WorkerCPU(unsigned int listSize) {
    cpuLoadValues = new CircularList<float>(listSize);
    stat = readStat(0);
}

WorkerCPU::~WorkerCPU() {
    delete cpuLoadValues;
}

int WorkerCPU::id() const {
    return 0;
}

CircularList<float> *WorkerCPU::results() const {
    return cpuLoadValues;
}

void WorkerCPU::run() {
    cpuLoadValues->append(getLoad());
}

void *WorkerCPU::start(void *data) {
    auto *param = (Worker::FunctionParam *) data;
    Worker *worker = param->worker;
    OpenGLWidget *widget = param->widget;
    while (true) {
        worker->run();
        widget->changeValues(worker->id(), worker->results());
        sleep(1);
    }
}

float WorkerCPU::getLoad() {
    CPUStat newStat = readStat(0);
    float load = calculateLoad(stat, newStat);
    stat = newStat;
    return load;
}
