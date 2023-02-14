#ifndef WORKERCPU_H
#define WORKERCPU_H

#include <unistd.h>
#include "worker.h"
#include "circularlist.h"

class WorkerCPU : public Worker {
public:
    WorkerCPU(unsigned int listSize = 60);
    ~WorkerCPU();
    virtual int id() const override;
    virtual CircularList<float> *results() const override;
    virtual void run() override;
    static void *start(void *data);

protected:
    virtual float getLoad() override;

private:
    CircularList<float> *cpuLoadValues;
    CPUStat stat;

};

#endif // WORKERCPU_H
