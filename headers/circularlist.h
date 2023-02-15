#ifndef CIRCULARLIST_H
#define CIRCULARLIST_H

#include <stdexcept>

template<typename T>
class CircularList {
public:
    CircularList(unsigned int size, T initData) : size(size) {
        if (size == 0) {
            throw std::invalid_argument("Error: invalid list size");
        }

        data = new T[size + 1];
        for (int i = 0; i < size + 1; ++i) {
            data[i] = initData;
        }
        headIndex = 0;
        tailIndex = size - 1;
    }

    ~CircularList() {
        delete [] data;
    }

    void append(T element) {
        data[headIndex] = element;
        if (headIndex == 0) {
            data[size] = element;
        }
        tailIndex = headIndex;
        headIndex = (headIndex + 1) % size;
    }

    T last() const {
        return data[tailIndex];
    }

    unsigned int length() const {
        return size;
    }

    T operator[] (unsigned int index) const {
        if (index >= size) {
            throw std::out_of_range("Error: index is out of range");
        }

        return data[index];
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

};

#endif // CIRCULARLIST_H
