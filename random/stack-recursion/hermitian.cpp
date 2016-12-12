#include <iostream>
#include <stack>
#include <assert.h>
using namespace std;

#define HERMITIAN 0
#define MULT 1
#define SUBT 2
#define VALUE 3

struct Frame {
    double value;
    double n;
    int opCode;
};


class HermitianPolynomial {
public:
    double recursiveHermitian (double x, double n) {
        if (n == 0)
            return 1;
        if (n == 1)
            return 2*x;
        double a = 2*x*recursiveHermitian(x, n -1);
        double b = 2*(n-1)*recursiveHermitian(x, n-2);
        return a - b;
    }

    double stackHermitian (double x, double n) {
        int i = 0;
        double result;
        stack<Frame> helperStack;
        stack<Frame> opStack;

        Frame mainFrame;
        mainFrame.opCode = HERMITIAN;
        mainFrame.n = n;
        mainFrame.value = x;

        opStack.push(mainFrame);

        while(!opStack.empty()) {
            Frame topOp = opStack.top();
            opStack.pop();

            Frame first;
            Frame second;
            Frame result;

            while(topOp.opCode == VALUE && !opStack.empty()) {
                helperStack.push(topOp);

                topOp = opStack.top();
                opStack.pop();
            }

            /* at this point at the top of the stack is
               an operation
            */

            switch(topOp.opCode) {
            case HERMITIAN:
                if (topOp.n == 0) {
                   Frame newTop;
                   newTop.opCode = VALUE;
                   newTop.value = 1;
                   helperStack.push(newTop);
                } else if (topOp.n == 1) {
                    Frame newTop;
                    newTop.opCode = VALUE;
                    newTop.value = 2 * x;
                    helperStack.push(newTop);
                } else {
                    int n = topOp.n;
                    /* here comes a big else clause */
                    Frame hermitianLeft;
                    Frame hermitianRight;
                    Frame mult;
                    Frame subt;
                    Frame doubleX;
                    Frame doubleN1;

                    subt.opCode = SUBT;
                    mult.opCode = MULT;

                    hermitianLeft.opCode = HERMITIAN;
                    hermitianLeft.n = n - 1;

                    hermitianRight.opCode = HERMITIAN;
                    hermitianRight.n = n - 2;

                    doubleX.opCode = VALUE;
                    doubleX.value = 2 * x;

                    doubleN1.opCode = VALUE;
                    doubleN1.value = 2 * (n - 1);

                    opStack.push(subt);
                    opStack.push(mult);
                    opStack.push(doubleN1);
                    opStack.push(hermitianRight);
                    opStack.push(mult);
                    opStack.push(doubleX);
                    opStack.push(hermitianLeft);
                }
                break;
            case MULT:
                 first = helperStack.top();
                 helperStack.pop();

                 second = helperStack.top();
                 helperStack.pop();

                 result.opCode = VALUE;
                 result.value = first.value * second.value;

                 helperStack.push(result);
                 break;

            case SUBT:
                  first = helperStack.top();
                  helperStack.pop();

                  second = helperStack.top();
                  helperStack.pop();

                  result.opCode = VALUE;
                  result.value = second.value - first.value;

                  helperStack.push(result);
                  break;
            }
        }
        return helperStack.top().value;
    }
};

void testHermitian() {
    HermitianPolynomial c;
    for (int i = 0 ; i < 10; i++) {
        assert(c.stackHermitian(3, i) == c.recursiveHermitian(3, i));
    }
}

int main() {
    testHermitian();
    return 0;
}
