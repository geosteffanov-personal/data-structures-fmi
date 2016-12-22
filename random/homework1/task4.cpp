#include <iostream>
#include <assert.h>
#include <stack>
using namespace std;
template <class T>
class Queue {
    stack<T> head;
    stack<T> tail;

    void move() {
        assert(!tail.empty());
        while(!tail.empty()) {
            head.push(tail.top());
            tail.pop();
        }
    }

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
        move();
    }
    return head.top();
}

template <class T>
void Queue<T>::pop() {
    if (head.empty()) {
        move();
    }
    head.pop();
}

template <class T>
bool Queue<T>::empty() const {
    return head.empty() && tail.empty();
}
