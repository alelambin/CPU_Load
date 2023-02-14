#ifndef WORKER_H
#define WORKER_H

#include <fstream>
#include <sstream>
#include "openglwidget.h"
#include "circularlist.h"

struct CPUStat {
    unsigned int user;
    unsigned int nice;
    unsigned int system;
    unsigned int idle;
};

class Worker {
public:
    struct FunctionParam {
        Worker *worker;
        OpenGLWidget *widget;
    };

    virtual ~Worker() = default;
    virtual int id() const = 0;
    virtual CircularList<float> *results() const = 0;
    virtual void run() = 0;

protected:
    virtual float getLoad() = 0;

    static CPUStat readStat(int lineNum) {
        std::ifstream statFile("/proc/stat");
        if (!statFile.is_open()) {
            statFile.close();
            throw std::runtime_error("Error: could not open /proc/statFile file");
        }

        std::string line;
        for (int i = 0; i <= lineNum; ++i) {
            std::getline(statFile, line);
        }

        std::string name;
        CPUStat stat;
        std::stringstream stream(line);
        stream >> name;
        stream >> stat.user;
        stream >> stat.nice;
        stream >> stat.system;
        stream >> stat.idle;

        statFile.close();
        return stat;
    }

    static float calculateLoad(CPUStat prevStat, CPUStat curStat) {
        unsigned int userDiff = curStat.user - prevStat.user;
        unsigned int niceDiff = curStat.nice - prevStat.nice;
        unsigned int systemDiff = curStat.system - prevStat.system;
        unsigned int idleDiff = curStat.idle - prevStat.idle;

        return 1.0f - (float) idleDiff / (float) (userDiff + niceDiff + systemDiff + idleDiff);
    }

};

#endif // WORKER_H
