#include <vector>
#include <iostream>
#include <list>
#include <assert.h>
using namespace std;

template <class KEY>
using hashFn  = unsigned int (*) (KEY, unsigned int);


template <class KEY, c  lass VALUE>
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
    Hash(hashFn<KEY> function, unsigned int size);

    VALUE operator[] (const KEY& key) const;

    VALUE& operator[] (const KEY& key);

    VALUE get(const KEY key) const;

    void set(const KEY key, const VALUE value);

    bool containsKey(KEY key) const;

    double efficiency() const;


    friend ostream& operator<<(ostream& out, const Hash<KEY , VALUE> &hash) {
        for (int i = 0; i < hash.table.size(); i++) {
            for (const typename Hash<KEY, KEY>::Pair& current : hash.table[i]) {
                out << current.key << "::" << current.value << endl;
            }
        }

        return out;
    }
};
/* implementations */

template <class KEY, class VALUE>
Hash<KEY, VALUE>::Hash(hashFn<KEY> function, unsigned int size) {
        this->hashFunction = function;
        this->size = size;
        table.assign(size, list<Pair>());
}

template <class KEY, class VALUE>
VALUE Hash<KEY, VALUE>::operator[] (const KEY& key) const {
        unsigned int index = hashFunction(key, size);

        for (const Pair& current : table[index]) {
            if (current.key == key)
                return current.value;
        }

        assert(false);
        return VALUE();
}

template <class KEY, class VALUE>
VALUE& Hash<KEY,VALUE>::operator[] (const KEY& key) {
        unsigned int index = hashFunction(key, size);

        for (Pair& current : table[index]) {
            if (current.key == key)
                return current.value;
        }

        table[index].push_back(Pair(key, VALUE(444)));
        return table[index].back().value;
}

template <class KEY, class VALUE>
bool Hash<KEY, VALUE>::containsKey(KEY key) const {
    unsigned int index = hashFunction(key, size);

    for (const Pair& current : table[index]) {
        if (current.key == key)
            return true;
    }
    return false;
}

template <class KEY, class VALUE>
void Hash<KEY, VALUE>::set(const KEY key, const VALUE value) {
     unsigned int index = hashFunction(key, size);

     for (Pair& current : table[index]) {
        if (current.key == key)
            current.value = value;
     }

    table[index].push_back(Pair(key, value));
}

template <class KEY, class VALUE>
VALUE Hash<KEY, VALUE>::get(const KEY key) const {
    unsigned int index = hashFunction(key, size);

    for (const Pair& current : table[index]) {
        if (current.key == key)
            return current.value;
    }

    assert(false);
    return VALUE();
}

template <class KEY, class VALUE>
double Hash<KEY, VALUE>::efficiency() const {
    int collisions = 0 ;
    int all = 0;
    for(int i = 0; i < table.size(); i++) {
        all += table[i].size();
        if (table[i].size() > 1) {
            collisions += table[i].size() - 1;
        }
    }

    return  (all - collisions)/((double) all);
}


