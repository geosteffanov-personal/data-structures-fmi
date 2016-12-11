// |8 |4 |2  |7 |5 |2  |7 |X
#include <iostream>
#include "hash.cpp"
#include <assert.h>
unsigned int hashFunction(int key, unsigned int size) {
    return key % size;
}
void testAddAssign() {
  Hash<int, int> b(hashFunction, 5);
  b[1] = 10;
  b[6] = 13;
  assert(b[1] == 10);
  assert(b[6] == 13);
  assert(!b.containsKey(2));
  assert(b.containsKey(1));
}
void testEfficiency() {
    Hash<int, int> b(hashFunction, 10);
     b.set(1, 1);
     b.set(2, 1);
     b.set(11, 2);
     assert((b.efficiency() - 0.667) < 0.01);
}
void testGetAndSet() {
     Hash<int, int> b(hashFunction, 10);
     b.set(1, 1);
     assert(b.get(1) == 1);
     b.set(2, 1);
     b.set(1, 2);
     assert(b.get(1) == 2);
     assert(b.containsKey(1));
     assert(b.containsKey(2));
}
void testOutput() {
     Hash<int, int> b(hashFunction, 10);
     b.set(1, 1);
     b.set(2, 2);
     b.set(3, 4);
     b.set(4, 5);
     b.set(12, 12);
     b.set(6, 3);
     b.set(11, 67);

     cout<< b << endl;
}

int main() {
    testAddAssign();
    testGetAndSet();
    testEfficiency();
    testOutput();
}
