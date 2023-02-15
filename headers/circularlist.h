#ifndef CIRCULARLIST_H
#define CIRCULARLIST_H

#include <stdexcept>
#include "mutex.h"

template<typename T>
class CircularList {
public:
    CircularList(unsigned int size, T initData) : size(size) {
        if (size == 0) {
            throw std::invalid_argument("Error: invalid list size");
        }

        data = new T[size + 1];
        mutex.lock();
        for (int i = 0; i < size + 1; ++i) {
            data[i] = initData;
        }
        mutex.unlock();
        headIndex = 0;
        tailIndex = size - 1;
    }

    ~CircularList() {
        delete [] data;
    }

    void append(T element) {
        mutex.lock();
        data[headIndex] = element;
        if (headIndex == 0) {
            data[size] = element;
        }
        mutex.unlock();
        tailIndex = headIndex;
        headIndex = (headIndex + 1) % size;
    }

    T last() {
        mutex.lock();
        T result = data[tailIndex];
        mutex.unlock();
        return result;
    }

    unsigned int length() const {
        return size;
    }

    T operator[] (unsigned int index) {
        if (index >= size) {
            throw std::out_of_range("Error: index is out of range");
        }

        mutex.lock();
        T result = data[index];
        mutex.unlock();
        return result;
    }

    T *getData() const {
        return data;
    }

    unsigned int index() const {
        return headIndex;
    }

private:
    T *data;
    unsigned int headIndex;
    unsigned int tailIndex;
    unsigned int size;
    Mutex mutex;

};

#endif // CIRCULARLIST_H
