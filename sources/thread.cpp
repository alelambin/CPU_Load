#include "../headers/thread.h"

Thread::Thread(void *(* function)(void *arg), void *arg) {
    pthread_attr_t attribute;
    pthread_attr_init(&attribute);
    pthread_create(&threadID, &attribute, function, arg);
}

void *Thread::join() {
    void *data;
    pthread_join(threadID, &data);
    return data;
}

void Thread::detach() {
    pthread_detach(threadID);
}

void Thread::cancel() {
    pthread_cancel(threadID);
}
