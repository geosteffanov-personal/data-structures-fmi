#include <iostream>
#include "task5.cpp"
#include <assert.h>
using namespace std;
void testCrown() {
    int expectedWith5[] =
    {
        5, 6, 10, 7, 12, 11, 20, 8, 14, 13, 24, 12, 22
    };
    int expectedWith11[] =
    {
        11, 12, 22, 13, 24, 23, 44, 14, 26
    };
    for (int i = 0; i < 13; i++) {
        assert(expectedWith5[i] == CrownSequence(5, i));
    }
    for (int i = 0; i < 9; i++) {
        assert(expectedWith11[i] == CrownSequence(11, i));
    }
}

int main(){
    testCrown();
    return 0;
}
