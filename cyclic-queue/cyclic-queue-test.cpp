#include <iostream>
#include <fstream>
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
    assert(q.pop() == 5);
    assert(q.pop() == 4);
    assert(q.empty());
}
void testSerializeDeserialize() {
    CyclicQueue<int> q;
    q.push(6);
    q.push(7);
    q.push(5);
    q.push(4);
    q.push(3);
    ofstream out("out.txt");
    q.serialize(out);
    CyclicQueue<int> q2;
    ifstream in("out.txt");
    q2.deserialize(in);
    while(!q.empty() && !q2.empty()) {
        assert(q.pop() == q2.pop());
    }
    assert(q.empty());
    assert(q2.empty());
}
int main() {
    testInitialize();
    testPush();
    testPop();
    testSerializeDeserialize();
    return 0;
}

