#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>
#include <map>
using namespace std;
/* declarative programming - shoutout to Dimitar 'Guru' Milev */
vector<string> split(string& text) {
    string bufferString; // Have a buffer string
    stringstream textStream(text); // Insert the string into a stream
    vector<string> words; // Create vector to hold our words

    while (textStream >> bufferString)
        words.push_back(bufferString);

    return words;
}


int taskThree(string& text1, string& text2) {
    int count = 0;
    vector<string> words1 = split(text1);
    map<string, int> occurences;
    for (int i = 0; i < words1.size(); i++) {
        if (occurences.find(words1[i]) != occurences.end()) {
            occurences[words1[i]] += 1;
        } else {
            occurences[words1[i]] = 1;
        }
    }

    vector<string> words2 = split(text2);
    for (int i = 0 ; i < words2.size() ; i++) {
        if (occurences.find(words2[i]) != occurences.end())
            count++;
    }

    return count;
}

int taskFour(string& text1, string& text2) {
    int count = 0;
    vector<string> words1 = split(text1);
    map<string, int> occurences1;
    for (int i = 0; i < words1.size(); i++) {
        if (occurences1.find(words1[i]) != occurences1.end()) {
            occurences1[words1[i]] += 1;
        } else {
            occurences1[words1[i]] = 1;
        }
    }

    vector<string> words2 = split(text2);
    map<string, int> occurences2;
    for (int i = 0; i < words2.size(); i++) {
        if (occurences2.find(words2[i]) != occurences2.end()) {
            occurences2[words2[i]] += 1;
        } else {
            occurences2[words2[i]] = 1;
        }
    }
    for (int i = 0; i < words2.size() ; i++) {
        if (occurences2[words2[i]] == 1 && (occurences1.find(words2[i]) != occurences1.end())) {
            count++;
        }
    }
    return count;
}
string taskFive(string& text) {
    vector<string> words = split(text);
    map<string, int> occurences;
    for (int i = 0; i < words.size(); i++) {
        if (occurences.find(words[i]) != occurences.end()) {
            occurences[words[i]]+= 1;
        } else {
            occurences[words[i]] = 1;
        }
    }

    int max = 0;
    string maxxedWord;
    for (int i = 0; i < words.size(); i++) {
        if (words[i].size() > 3 && occurences[words[i]] > max) {
            max = occurences[words[i]];
            maxxedWord = words[i];
        }
    }

    return maxxedWord;
}
bool taskSix() {
    int n, x, fx;
    cout << "Enter n: ";
    cin >> n;
    map<int, int> function;

    for (int i = 0; i < n; i++) {
        cout << " Enter x: ";
        cin >> x;
        cout << " Enter f(x): ";
        cin >> fx;
        if (function.find(x) != function.end() && function[x] != fx) {
            return false;
        } else {
            function[x] = fx;
        }
    }
    return true;
}


int main () {
    string firstText = "a a b b c d e f g aah bbef cdeg bbef cdeg cdeg";
    string secondText = "a a b c d e b b m aah bbef cdeg";

    cout << "Task three: " << taskThree(firstText, secondText) << endl;
    cout << "Task four: " << taskFour(firstText, secondText) << endl;
    cout << "Task five: " << taskFive(firstText) << endl;
    cout << "Task six: " << taskSix() << endl;

    return 0;
}
