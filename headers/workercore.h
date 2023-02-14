#ifndef WORKERCORE_H
#define WORKERCORE_H

#include <unistd.h>
#include "worker.h"
#include "circularlist.h"

class WorkerCore : public Worker {
public:
    WorkerCore(int core, unsigned int listSize = 60);
    ~WorkerCore();
    virtual int id() const override;
    virtual CircularList<float> *results() const override;
    virtual void run() override;
    static void *start(void *data);

protected:
    virtual float getLoad() override;

private:
    int core;
    CircularList<float> *cpuLoadValues;
    CPUStat stat;

};

#endif // WORKERCORE_H
