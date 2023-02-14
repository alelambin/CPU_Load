#ifndef CIRCULARLIST_H
#define CIRCULARLIST_H

#include <stdexcept>
#include "listnode.h"

template<typename T>
class CircularList {
public:
    CircularList(unsigned int size) : size(size) {
        if (size == 0) {
            throw std::invalid_argument("Error: invalid list size");
        }

        head = new ListNode<T>();
        ListNode<T> *prevNode = head;
        ListNode<T> *curNode = nullptr;
        for (int i = 1; i < size; ++i) {
            curNode = new ListNode<T>();
            prevNode->setNext(curNode);
            prevNode = curNode;
        }
        tail = curNode;
        tail->setNext(head);
    }

    ~CircularList() {
        ListNode<T> *prevNode = head;
        ListNode<T> *curNode = head;
        while (curNode != tail) {
            curNode = curNode->getNext();
            delete prevNode;
            prevNode = curNode;
        }
        delete curNode;
    }

    void append(T data) {
        head->setData(data);
        head = head->getNext();
        tail = tail->getNext();
    }

    T last() const {
        return tail->getData();
    }

    unsigned int length() const {
        return size;
    }

//    T &operator[] (int index) {
//        if (index < 0 || index >= size) {
//            throw std::out_of_range("Error: index is out of range");
//        }

//        ListNode<T> *curNode = head;
//        for (int i = 0; i < index; ++i) {
//            curNode = curNode->getNext();
//        }
//        return curNode->getData();
//    }

    T operator[] (unsigned int index) const {
        if (index >= size) {
            throw std::out_of_range("Error: index is out of range");
        }

        ListNode<T> *curNode = head;
        for (int i = 0; i < index; ++i) {
            curNode = curNode->getNext();
        }
        return curNode->getData();
    }

private:
    ListNode<T> *head;
    ListNode<T> *tail;
    unsigned int size;

};

#endif // CIRCULARLIST_H
