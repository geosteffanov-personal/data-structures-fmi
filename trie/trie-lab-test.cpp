#include "trie-lab.cpp"
#include <iostream>
#include <assert.h>
using namespace std;
void testAddAndAssign() {
    Trie trie;
    trie.set("", 1);
    assert(trie.get("") == 1);

    trie.set("aa", 2);
    assert(trie.get("aa") == 2);

        /*
    trie.set("westworld", 5);
    assert(trie.get("westworld") == 5);
    */

}
void testCanonical() {
    Trie trie;
}
void testMember() {
    Trie trie;
    trie.set("a", 2);
    trie.set("b", 3);
    trie.set("westworld", 8);
    assert(trie.member("a"));
    assert(trie.member("b"));
    assert(trie.member("westworld"));
    assert(!trie.member("eastworld"));
    assert(!trie.member(""));
}

int main() {
    testCanonical();
    testAddAndAssign();
    testMember();

    return 0;
}
