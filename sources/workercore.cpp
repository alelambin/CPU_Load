#include "../headers/workercore.h"

WorkerCore::WorkerCore(int core, unsigned int listSize) : core(core) {
    cpuLoadValues = new CircularList<float>(listSize, -1.0);
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
    Worker *worker = *((Worker **) data);
    while (true) {
        worker->run();
        emit(worker->newValue(worker->id()));
        sleep(1);
    }
}

float WorkerCore::getLoad() {
    CPUStat newStat = readStat(core + 1);
    float load = calculateLoad(stat, newStat);
    stat = newStat;
    return load;
}
