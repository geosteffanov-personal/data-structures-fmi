#include <iostream>
#include <stack>
#include <assert.h>
using namespace std;

int factorialRecursive(int n) {
    if (n == 0)
        return 1;
    return n * factorialRecursive(n - 1);

}
#define FACTORIAL 0
#define VALUE 1
struct Operation {
    int opCode;
    int n;
    int value;
};

int factorialStack(int n) {
    stack<Operation> opStack;

    int result = 1;

    Operation mainOp;
    mainOp.opCode = FACTORIAL;
    mainOp.n = n;

    opStack.push(mainOp);

    while(!opStack.empty()) {
        Operation topOp = opStack.top();
        opStack.pop();

        if (topOp.opCode == FACTORIAL) {
             int n = topOp.n;

             if (n == 0) {
                Operation valueZero;
                valueZero.opCode = VALUE;
                valueZero.value = 1;
                opStack.push(valueZero);
             } else {
                Operation firstSummand;
                firstSummand.n = n-1;
                firstSummand.opCode = FACTORIAL;

                opStack.push(firstSummand);
                Operation secondSummand;
                secondSummand.opCode = VALUE;
                secondSummand.value = n;

                opStack.push(secondSummand);
             }
        } else {
            assert(topOp.opCode == VALUE);
            int value = topOp.value;
            result *= value;
        }
    }

    return result;
}
int main() {
    for (int i = 0; i < 15; i++) {
        cout << factorialStack(i) << endl;
    }
    return 0;
}
