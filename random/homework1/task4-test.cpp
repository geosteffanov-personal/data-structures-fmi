#include <iostream>
#include "task4.cpp"
#include <assert.h>
using namespace std;
void testEverything() {
    Queue<int> q1;
    assert(q1.empty());
    Queue<int> q2(q1);
    assert(q2.empty());
    Queue<int> q3;
    q3.push(5);
    assert(q3.front() == 5);
    assert(!q3.empty());
    q3.pop();
    assert(q3.empty());
    q3.push(-5);
    assert(!q3.empty());
    assert(q3.front() == -5);
    q2 = q3;
    assert(q2.front() == -5);
    assert(!q2.empty());
    q3 = q1;
    assert(q3.empty());
    assert(!q2.empty());
    q2.push(3);q2.push(8);
    assert(q2.front() == -5);q2.pop();
    assert(q2.front() == 3);q2.pop();
    assert(q2.front() == 8);q2.pop();
}

int main(){
    testEverything();
    return 0;
}
