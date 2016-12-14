#include <iostream>
#include <vector>
#include <stack>
#include <assert.h>
using namespace std;


void permutations(string symbols,string crrPermutation,vector<string> &allPermutations)
{
    if(symbols.size()==0)
    {
        allPermutations.push_back(crrPermutation);
        return;
    }
    for(int i=0;i<symbols.size();i++)
    {
        string nextPermutation=crrPermutation;
        nextPermutation.push_back(symbols[i]);
        string next = symbols;
        next.erase(i,1);
        permutations(next,nextPermutation,allPermutations);
    }

}

/*
    Задача 1: Да се генерират всички пермутации на дадено множество символи:
    а) чрез рекурсивна функция
    б) чрез стек
    И в двата случая функцията да връща вектор, съдържащ пермутациите.
    Например за вход “abc” програмата трябва да върне вектор с низовете:
    "cba", "cab", "bca", "bac", "acb", "abc" (не задължително в този ред)
    в) Да се имплементира клас PermutationIterator, позволяващ да се итерира по всички
    пермутации на зададено множество от символи.
*/
template <class T>
vector<T> placeAt(vector<T> v, T data, int index) {
    vector<T> result = v;
    result.push_back(T());
    assert(index >= 0 && index <= v.size());
    for (int i = v.size(); i >= index + 1; i--) {
        result[i] = result[i - 1];
    }
    result[index] = data;
    return result;
}

template <class T>
vector <T> appendVectors(vector<T> first, vector<T> second) {
    vector<T> result = first;
    for (int i = 0; i < second.size(); i++) {
        result.push_back(second[i]);
    }
    return result;
}

template <class T>
vector<vector<T>> permutations(vector<T> sset) {
    if(sset.size() == 1) {
        vector<vector<T>> result;
        result.push_back(sset);
        return result;
    }

    vector<T> help;
    for (int i = 1; i < sset.size(); i++) {
        help.push_back(sset[i]);
    }

    T first = sset[0];
    vector<vector<T>> res;

    vector<vector<T>> prev = permutations(help);
    for (int i = 0; i < prev.size(); i++) {
        vector<T> crrPerm = prev[i];
        for (int j = 0; j <= crrPerm.size(); j++) {
            res.push_back(placeAt(crrPerm, first, j));
        }
    }

    return res;
}


#define PERM 0
#define SETP 1
#define DONE 2

template <class T>
vector<vector<T>> stackPermutations(vector<T> sset) {
    int maxLength = sset.size();
    vector<vector<T>> result;

    struct stackFrame {
        int op;
        vector<T> sset;
        T current;
        int position;
        int expectedLength;
    };

    stack<stackFrame> opStack;
    stack<stackFrame> done;
    stack<stackFrame> help;
    stackFrame main;
    main.op = PERM;
    main.sset= sset;
    opStack.push(main);

    while (!opStack.empty()) {
        cout << "OPSTACK IS NOT EMPTY ############ " << endl;
        stackFrame top = opStack.top();
        opStack.pop();

        if (top.op == PERM) {
                cout << "PERMUTATION" << endl;
                if (top.sset.size() == 1) {
                    stackFrame newFrame;
                    newFrame.op = DONE;
                    newFrame.sset = top.sset;
                    done.push(newFrame);
                } else {
                    int k = top.sset.size();
                    T lastEl = top.sset.back();
                    top.sset.pop_back();

                    vector<T> newSet = top.sset;

                    for (int i = 0; i < k; i++) {
                        stackFrame putFrame;
                        putFrame.op = SETP;
                        putFrame.expectedLength = k - 1;
                        putFrame.current = lastEl;
                        putFrame.position = i;
                        opStack.push(putFrame);

                        stackFrame permute;
                        permute.op = PERM;
                        permute.sset = top.sset;
                        opStack.push(permute);
                    }
                }
        } else if (top.op == SETP) {
            cout << "SETP" << endl;
            assert(top.op == SETP);
            int expLength = top.expectedLength;
            int position = top.position;
            int data = top.current;

            while(!done.empty()) {
                if (done.top().sset.size() != expLength) {
                    break;
                }
                cout << "WITH EXPECTED LENGTH: " << expLength << endl;
                stackFrame doneTop = done.top();
                done.pop();
                cout << "TOPPED SIZE: " << doneTop.sset.size() << endl;
                cout << "TOPPED: "  << endl;
                for (int i = 0; i < doneTop.sset.size(); i++) {
                    cout << doneTop.sset[i] << endl;
                }
                cout << endl << endl;
                cout << "POPPED HERE. " << endl;
                stackFrame newDone;
                newDone.op = DONE;
                cout << "POSITION TO PASTE: " << position << endl;
                cout << "SIZE OF SET TO PASTE TO: " << doneTop.sset.size() << endl;
                newDone.sset = placeAt(doneTop.sset, data, position);
                cout << "SET AFTER PLACING: " << endl;
                cout << "SIZE: " << newDone.sset.size() <<  endl;
                for (int i = 0; i < newDone.sset.size(); i++) {
                    cout << newDone.sset[i] <<endl;
                }
                if (newDone.sset.size() == maxLength) {
                    cout << "PUSHING TO RESULT" << endl;
                    result.push_back(newDone.sset);
                } else {
                    cout << "BEFORE PUSHING TO HELP" << endl;
                    help.push(newDone);
                    cout << "AFTER PUSHIN TO HELP" << endl;
                }
            }
            while(!help.empty()) {
                cout << "POPPIN AN PUSHIN INTO DONE" << endl;
                stackFrame toPop = help.top();
                cout << "OPERATION: " << toPop.op << endl;
                cout << "SIZE: " << toPop.sset.size() << endl;
                done.push(help.top());
                cout << "JUST PUSHED!" << endl;
                help.pop();
            }
        } else {
            cout << "IMPOSSIBLE SCENARIO" << endl;
        }
    }
    return result;
}

int main () {
    vector<int> test;
    for (int i = 0; i < 4; i++) {
        test.push_back(i);
    }


    vector<vector<int>> resultRecurs = permutations(test);

    for (int i = 0; i < resultRecurs .size(); i++) {
        for (int j = 0; j < resultRecurs [i].size(); j++) {
            cout << resultRecurs [i][j];
        }
        cout <<endl;
    }

    vector<vector<int>> resultStack = stackPermutations(test);
    for (int i = 0; i < resultStack.size(); i++) {
        for (int j = 0; j < resultStack[i].size(); j++) {
            cout << resultStack[i][j];
        }
        cout <<endl;
    }


    return 0;
}
