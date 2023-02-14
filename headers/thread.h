#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>

class Thread {
public:
    Thread(void *(*) (void *), void *);
    ~Thread() = default;
    void *join();
    void detach();
    void cancel();

private:
    pthread_t threadID;

};

#endif // THREAD_H
