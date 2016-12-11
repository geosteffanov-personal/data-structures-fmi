#include <iostream>
#include <assert.h>
using namespace std;

template <class T>
class Stack {
    struct Node {
        T data;
        Node<T>* next;

        Node(T _data): data(_data), next(NULL) {}

        Node(T _data, Node<T>* _next) : data(_data), next(_next) {}
    };



    Node<T>* top;

    Node<T>* copyStack(Node<T>* nextNode) {
        if (nextNode == NULL)
            return NULL;

        return new Node<T>(nextNode->data, copyStack(nextNode->next));
    }

    void deleteStack() {
        Node<T>* temp;
        while (top != NULL) {
            temp = top;
            top = top->next;
            delete temp;
        }
    }
public:
    Stack() {
        top = NULL;
    }

    Stack(const Stack<T>& other) {
        top = copyStack(other.top);
    }

    Stack& operator=(const Stack<T>& other) {
        if (this != &other) {
            deleteStack();
            top = copyStack(other.top);
        }
        return *this;
    }

    bool isEmpty() const {
        return (top == NULL);
    }

    bool isMember(T value) const {
        Node<T>* temp = top;
        while(temp != NULL) {
            if (temp->data == value)
                return true;

            temp = temp->next;
        }
        return false;
    }

    void push(T newValue) {
        Node<T>* newTop = new Node<T>(newValue, top);
        top = newTop;
    }

    T pop() {
        assert(!isEmpty());
        Node<T>* tmp = top;
        T result = tmp->data;
        top = top->next;
        delete tmp;
        return result;
    }

    ~Stack() {
        deleteStack();
    }
};
void testEmptyStack() {
    Stack<int> emptyStack;
    assert(emptyStack.isEmpty());
}

void testPushPop() {
    Stack<int> newStack;
    for (int i = 0; i < 7; i++) {
        newStack.push(i);
    }

    int counter = 0;
    while(!newStack.isEmpty()) {
        newStack.pop();
        counter++;
    }

    assert(counter == 7 && newStack.isEmpty());
}

void testMember() {
    Stack<int> newStack;
    for (int i = 0; i < 7; i++) {
        newStack.push(i);
    }

    for(int i = 0; i < 7; i++) {
        assert(newStack.isMember(i));
    }
}

void testCopyStack() {
    Stack<int> firstStack;
    firstStack.push(1);
    firstStack.push(2);
    firstStack.push(3);

    Stack<int> secondStack(firstStack);
    assert(secondStack.pop() == 3);
    assert(secondStack.pop() == 2);
    assert(secondStack.pop() == 1);
    assert(secondStack.isEmpty());

    secondStack = firstStack;
    assert(secondStack.pop() == 3);
    assert(secondStack.pop() == 2);
    assert(secondStack.pop() == 1);
    assert(secondStack.isEmpty());
}

int main() {
    testEmptyStack();
    testPushPop();
    testMember();
    testCopyStack();
    return 0;
}
