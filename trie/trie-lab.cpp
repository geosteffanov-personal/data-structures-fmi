#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;
struct TrieNode{
    TrieNode* parent;
    TrieNode* children[26];
    bool end;
    int value;

    TrieNode() {
        parent = nullptr;
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }

        end = false;
        value = -1;
    }

};

class Trie {
    TrieNode* root;
private:
    int set(char* key, const int value, TrieNode*& current, TrieNode* parent);
    int get(char* key, TrieNode*& current);
    bool member(char* key, TrieNode*& current);

public:
    Trie();
    Trie(const Trie& other);
    Trie& operator= (const Trie& other);
    ~Trie();

    int get(char* key);
    int set(char* key, const int value);
    bool member(char* key);
    void print();
    int remove(const char*);
};

Trie::Trie() {
    root = new TrieNode;
}

Trie::~Trie() {
    delete root;
    root = nullptr;
}

int Trie::set(char* key, const int value, TrieNode*& current, TrieNode* parent) {
    if (*key == '\0') {
        if (current == nullptr) {
            current = new TrieNode;
            current->parent = parent;
        }

        current->value = value;
        current->end = true;
        return value;

    } else {
        if (current == nullptr) {
            current = new TrieNode;
            current->parent = parent;
        }
        char currentChar = key[0];
        return set(key + 1, value, current->children[currentChar - 'a'], current);
    }
}

int Trie::set(char* key, const int value) {
    return set(key, value, root, nullptr);
}

int Trie::get(char* key, TrieNode*& current) {
    if (*key == '\0') {
        assert(current->end);
        return(current->value);
    }
    assert(current != nullptr);
    char currentChar = key[0];
    return get(key + 1, current->children[currentChar - 'a']);
}

int Trie::get(char* key) {
    return get(key, root);
}

bool Trie::member(char* key) {
    return member(key, root);
}

bool Trie::member(char* key, TrieNode*& current) {
    if (*key == '\0') {
        if (current == nullptr)
            return false;
        if (!current->end)
            return false;
        return true;
    } else {
        char currentChar = *key;
        if (current == nullptr)
            return false;
        return member(key + 1, current->children[currentChar - 'a']);
    }

}
