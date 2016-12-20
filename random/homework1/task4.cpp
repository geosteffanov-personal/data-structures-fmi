#include <iostream>
#include <assert.h>
#include <stack>
using namespace std;
template <class T>
class Queue {
    stack<T> head;
    stack<T> tail;

    void emptyQueue();

public:
    Queue();
    Queue(const Queue<T>& other);
    Queue& operator=(const Queue<T>& other);
    ~Queue();

    void push(const T& data);
    T front();
    void pop();
    bool empty() const;
};
template <class T>
Queue<T>::Queue() : head(), tail() {}

template <class T>
Queue<T>::Queue(const Queue<T>& other) : head(), tail() {
    assert(head.empty());
    assert(tail.empty());
    head = other.head;
    tail =other.tail;
}

template <class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other) {
    if (this != &other) {
            emptyQueue();
            assert(head.empty());
            assert(tail.empty());
            head = other.head;
            tail = other.tail;
    }
    return *this;
}

template <class T>
void Queue<T>::emptyQueue() {
    while(!head.empty()) {
        head.pop();
    }
    while (!tail.empty()) {
        tail.pop();
    }
}

template <class T>
Queue<T>::~Queue() {
    emptyQueue();
}

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
void testInitialization(){
    Queue<int> q;
    assert(q.empty());
    Queue<int> q2(q);
    assert(q2.empty());
}
void testAssignment() {
    Queue<int> q;
    Queue<int> p;
    p = q;
    assert(p.empty());
}

void testPushPop() {
    Queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    assert(q.front() == 1);
    Queue<int> p(q);
    assert(!p.empty());
    assert(p.front() == 1);
    p.pop();
    assert(p.front() == 2);
    p.pop();
    assert(p.front() == 3);
    p.pop();
    assert(p.empty());
}

int main() {
    testInitialization();
    testAssignment();
    testPushPop();
}

