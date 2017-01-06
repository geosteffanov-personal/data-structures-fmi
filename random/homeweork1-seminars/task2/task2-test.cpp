#include <iostream>
#include <assert.h>
#include "task2.cpp"
using namespace std;
void testPNPartition() {
    list<queue<double>> lis;
    queue<double> q1;
    q1.push(-2);
    q1.push(1);
    q1.push(4);
    queue<double> q2;
    q2.push(2);
    q2.push(-2);
    queue<double> q3;
    q3.push(-3);
    q3.push(-1);
    q3.push(-3);
    q3.push(4);
    queue<double> q4;
    q4.push(2);
    q4.push(-1);
    q4.push(-10);
    lis.push_back(q1);
    lis.push_back(q2);
    lis.push_back(q3);
    lis.push_back(q4);
    assert(hasPNPartition(lis));
}

int main() {
    testPNPartition();
}
