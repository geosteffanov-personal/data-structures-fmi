#include <iostream>
#include <stack>
#include <assert.h>
using namespace std;

#define HERMITIAN 0
#define MULT 1
#define ADD 2
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
        return a + b;
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
                   opStack.push(newTop);
                } else if (topOp.n == 1) {
                    Frame newTop;
                    newTop.opCode = VALUE;
                    newTop.value = 2 * x;
                    opStack.push(newTop);
                } else {
                    int n = topOp.n;
                    /* here comes a big else clause */
                    Frame hermitianLeft;
                    Frame hermitianRight;
                    Frame mult;
                    Frame plus;
                    Frame doubleX;
                    Frame doubleN1;

                    plus.opCode = ADD;
                    mult.opCode = MULT;

                    hermitianLeft.opCode = HERMITIAN;
                    hermitianLeft.n = n - 1;

                    hermitianRight.opCode = HERMITIAN;
                    hermitianRight.n = n - 2;

                    doubleX.opCode = VALUE;
                    doubleX.value = 2 * x;

                    doubleN1.opCode = VALUE;
                    doubleN1.value = 2 * (n - 1);

                    opStack.push(plus);
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

                 opStack.push(result);
                 break;

            case ADD:
                  first = helperStack.top();
                  helperStack.pop();

                  second = helperStack.top();
                  helperStack.pop();

                  result.opCode = VALUE;
                  result.value = first.value + second.value;

                  opStack.push(result);
                  break;
            }
            if (opStack.empty() && helperStack.empty()){
                    return topOp.value;
            }

            while(!helperStack.empty()) {
                Frame toPush = helperStack.top();
                helperStack.pop();
                opStack.push(toPush);
            }
        }
    }


};

void testHermitian() {
    HermitianPolynomial c;
    for (int i = 0; i < 15; i++) {
        assert(c.recursiveHermitian(3, i) == c.stackHermitian(3, i));
    }
}

int main() {
    testHermitian();
    return 0;
}
