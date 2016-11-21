#include <iostream>
#include <stack>
#include <assert.h>
using namespace std;

int fibonacciRecursive(int n) {
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;

    return fibonacciRecursive(n - 1) +
           fibonacciRecursive(n - 2);

}
#define FIBONACCI 0
#define VALUE 1
struct Operation {
    int opCode;
    int n;
    int value;
};

int fibonacciStack(int n) {
    stack<Operation> opStack;

    int result = 0;

    Operation mainOp;
    mainOp.opCode = FIBONACCI;
    mainOp.n = n;

    opStack.push(mainOp);

    while(!opStack.empty()) {
        Operation topOp = opStack.top();
        opStack.pop();

        if (topOp.opCode == FIBONACCI) {
             int n = topOp.n;

             if (n == 0) {
                Operation valueZero;
                valueZero.opCode = VALUE;
                valueZero.value = 0;
                opStack.push(valueZero);
             } else if (n == 1) {
                Operation valueOne;
                valueOne.opCode = VALUE;
                valueOne.value = 1;
                opStack.push(valueOne);
             } else {
                Operation firstSummand;
                firstSummand.n = n-1;
                firstSummand.opCode = FIBONACCI;

                Operation secondSummand;
                secondSummand.n = n-2;
                firstSummand.opCode = FIBONACCI;

                opStack.push(firstSummand);
                opStack.push(secondSummand);
             }
        } else {
            assert(topOp.opCode == VALUE);
            int value = topOp.value;
            result += value;
        }
    }

    return result;
}
int main() {
    for (int i = 0; i < 15; i++) {
        cout << fibonacciStack(i) << endl;
    }
    return 0;
}
