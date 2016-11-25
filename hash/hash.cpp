#include <vector>
#include <iostream>
#include <list>
#include <assert.h>
using namespace std;

template <class KEY>
using hashFn  = unsigned int (*) (KEY, unsigned int);

template <class KEY, class VALUE>
class Hash {
    struct Pair {
        KEY key;
        VALUE value;

        Pair(KEY _k, VALUE _v) : key(_k), value(_v){}
    };

    unsigned int size;
    vector<list<Pair>> table;
    hashFn<KEY> hashFunction;

public:
    Hash(unsigned int size) {
        this->size = size;
        table.assign(size, list<Pair>());
    }

    Hash(hashFn<KEY> function, unsigned int size) {
        this->hashFunction = function;
        this->size = size;
        table.assign(size, list<Pair>());
    }

    VALUE operator[](const KEY& key) const {
        unsigned int index = hashFunction(key, size);

        for (const Pair& current : table[index]) {
            if (current.key == key)
                return current.value;
        }

        assert(false);
        return VALUE();
    }

    VALUE& operator[] (const KEY& key) {
        unsigned int index = hashFunction(key, size);

        for (Pair& current : table[index]) {
            if (current.key == key)
                return current.value;
        }

        table[index].push_back(Pair(key, VALUE(444)));
        return table[index].back().value;
    }
};

unsigned int hashFunction(int key, unsigned int size) {
    return key % size;
}

int main() {
 Hash<int, int> b(hashFunction, 5);
 b[1] = 10;
 b[6] = 13;
 cout << b[6] << " " << b[1];

 return 0;

}

