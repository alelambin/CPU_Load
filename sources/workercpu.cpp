#include "../headers/workercpu.h"

WorkerCPU::WorkerCPU(unsigned int listSize) {
    cpuLoadValues = new CircularList<float>(listSize, -1.0);
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
    Worker *worker = *((Worker **) data);
    while (true) {
        worker->run();
        emit(worker->newValue(worker->id()));
        sleep(1);
    }
}

float WorkerCPU::getLoad() {
    CPUStat newStat = readStat(0);
    float load = calculateLoad(stat, newStat);
    stat = newStat;
    return load;
}
