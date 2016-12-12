#include <iostream>
#include <assert.h>
#include "cyclic-queue.cpp"
using namespace std;
void testInitialize() {
    CyclicQueue<int> q;
}
void testPush() {
    CyclicQueue<int> q;
    q.push(5);
    q.push(4);
    assert(q.toString().compare("5\n4") == 0);
}
void testPop() {
    CyclicQueue<int> q;
    q.push(5);
    q.push(4);
    assert(q.pop() == 4);
    assert(q.pop() == 5);
    assert(q.empty());
}
void testDeserialize() {

}
int main() {
    testInitialize();
    testPush();
    return 0;
}

