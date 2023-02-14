#ifndef LISTNODE_H
#define LISTNODE_H

template<typename T>
class ListNode {
public:
    ListNode(T value = 0) {
        data = T(value);
//        data = new T(value);
    }

    ~ListNode() {
//        delete data;
    };

    void setData(T newData) {
        data = newData;
//        *data = newData;
    }

    T getData() const {
        return data;
//        return *data;
    }

    void setNext(ListNode *newNext) {
        next = newNext;
    }

    ListNode *getNext() const {
        return next;
    }

private:
    T data;
    ListNode *next;

};

#endif // LISTNODE_H
