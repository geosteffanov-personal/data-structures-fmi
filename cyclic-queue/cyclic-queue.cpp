#include <iostream>
#include <assert.h>
#include <sstream>
#include <cstring>
using namespace std;

template <class T>
class CyclicQueue {

    struct Node{
        Node* next;
        T data;

        Node(T );
        Node(T , Node*);
    };
    Node* tail;

    public:

    CyclicQueue();
    void push(T data);
    T pop();

    string toString();
    bool empty();
};

template <class T>
CyclicQueue<T>::Node::Node(T d) : data(d), next(nullptr) {}

template <class T>
CyclicQueue<T>::Node::Node(T d, Node* n) : data(d), next(n) {}

template <class T>
CyclicQueue<T>::CyclicQueue() : tail(nullptr) {}

template <class T>
void CyclicQueue<T>::push(T data) {
    Node* newNode = new Node(data, nullptr);

    if (tail == nullptr) {
        newNode->next = newNode;
        tail = newNode;
        return;
    }

    newNode->next = tail->next;
    tail->next = newNode;
    tail = newNode;
    return;
}

template <class T>
T CyclicQueue<T>::pop() {
    assert(tail != nullptr);
    Node* toDelete = tail->next;
    T result = toDelete->data;
    if (tail == tail->next) {
        tail = nullptr;
    } else {
        tail->next = tail->next->next;
    }
    delete toDelete;
    return result;
}

template <class T>
string CyclicQueue<T>::toString() {
    string result = "";
    if(tail == nullptr) {
        return result;
    }
    Node* tmp = tail->next;
    while(tmp != tail) {
        stringstream ss;
        ss << tmp->data;
        string str = ss.str();
        result += str;
        result += '\n';
        tmp = tmp->next;
    }
    stringstream ss;
    ss << tmp->data;
    string str = ss.str();
    result += str;

    return result;
}
template <class T>
bool CyclicQueue<T>::empty() {
    return tail == nullptr;
}

