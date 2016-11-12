#include <iostream>
#include <assert.h>
using namespace std;

template <class T>
struct Node {
    T data;
    Node<T>* next;

    Node(T _data) : data(_data), next(NULL) {}
    Node(T _data, Node<T>* _next) : data(_data), next(_next) {}
};

template <class T>
class Queue {
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    Queue() {
        head = NULL;
        tail = NULL;
        size = 0;
    }

    bool isEmpty() const {
        return size == 0;
    }

    void push(const T& number) {
        if (size == 0) {
            head = new Node<T>(number);
            tail = head;
        } else if (size == 1) {
            tail = new Node<T>(number);
            head->next = tail;
        } else {
            tail->next = new Node<T>(number);
            tail = tail->next;
        }
        size++;
    }

    T pop() {
        assert(!isEmpty());

        Node<T>* tmp;
        T result;

        tmp = head;
        result = tmp->data;
        head = head->next;

        if(size == 1) {
            tail = NULL;
        }

        delete tmp;
        size--;
        return result;
    }

    bool isMember(const T& value) const {
        Node<T>* temp = head;
        while (temp != NULL) {
            if (temp->data == value)
                return true;

            temp = temp->next;
        }
        return false;
    }
};


void testEmptyQueue() {
    Queue<int> newQueue;
    assert(newQueue.isEmpty());
}

void testPushPop() {
    Queue<int> newQueue;

    newQueue.push(1);
    newQueue.push(2);
    newQueue.push(3);

    assert(newQueue.pop() == 1);
    assert(newQueue.pop() == 2);
    assert(newQueue.pop() == 3);
}

void testMember() {
    Queue<int> newQueue;
    newQueue.push(1);
    newQueue.push(2);
    assert(newQueue.isMember(2));
    assert(!newQueue.isMember(3));
}

void testCopy() {
    Queue<int> newQueue;
    for (int i = 0; i < 7; i++) {
        newQueue.push(i);
    }

    Queue<int> secondQueue(newQueue);
    for (int i = 0; i < 7; i++) {
        assert(secondQueue.isMember(i));
    }

    for (int i = 0; i < 7; i++) {
        secondQueue.pop();
    }

    secondQueue = newQueue;
    for (int i = 0; i < 7; i++) {
        assert(secondQueue.isMember(i));
    }
}
int main() {
    testEmptyQueue();
    testPushPop();
    testMember();
    testCopy();
}
