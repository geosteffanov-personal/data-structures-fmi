#include <iostream>
#include <assert.h>
#include <stack>
using namespace std;
template <class T>
class Queue {
    stack<T> head;
    stack<T> tail;

public:

    void push(const T& data);
    T front();
    void pop();
    bool empty() const;
};

template <class T>
void Queue<T>::push(const T& data) {
    tail.push(data);
}

template <class T>
T Queue<T>::front() {
    if (head.empty()) {
        assert(!tail.empty());
        while(!tail.empty()) {
            head.push(tail.top());
            tail.pop();
        }
    }
    return head.top();
}

template <class T>
void Queue<T>::pop() {
    if (head.empty()) {
        assert(!tail.empty());
        while(!tail.empty()) {
            head.push(tail.top());
            tail.pop();
        }
    }
    head.pop();
}

template <class T>
bool Queue<T>::empty() const {
    return head.empty() && tail.empty();
}

/* tests */
void testEmptyConstruction() {
    Queue<int> queues[10];
    for (int i = 0; i < 10; i++) {
        assert(queues[i].empty());
    }
}

void testCopyConstruction() {
    Queue<int> queues[10];
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j <= i; j++) {
            queues[i].push(j);
        }
    }
    for (int i = 0; i < 10; i++) {
        Queue<int> testQ(queues[i]);
        for (int j = 0; j <= i; j++) {
            assert(testQ.front() == j);
            testQ.pop();
        }
        assert(testQ.empty());
    }

    for (int i = 0; i < 10; i++) {
        assert(!queues[i].empty());
    }
}

void testAssignemnt() {
    Queue<int> queues[10];
    Queue<int> testQ;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j <= i; j++) {
            queues[i].push(j);
        }
    }
    for (int i = 0; i < 10; i++) {
        Queue<int> testQ = queues[i];
        for (int j = 0; j <= i; j++) {
            assert(testQ.front() == j);
            testQ.pop();
        }
        assert(testQ.empty());
    }

    for (int i = 0; i < 10; i++) {
        assert(!queues[i].empty());
    }
}

int main() {
    testEmptyConstruction();
    testCopyConstruction();
    testAssignemnt();
}
