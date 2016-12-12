#include <iostream>
#include <stack>
#include <cstring>

using namespace std;
int min(int a, int b) {
    if (a < b)
        return a;
    return b;
}

int el(int a, int b) {
    return (a + b)%10;
}
/*
    <exp> ::= <dig> | (<exp><op><exp>)
    <op> ::= $ | @

    For all the input tokens [S1]:
Read the next token [S2];
If token is an operator (x) [S3]:
While there is an operator (y) at the top of the operators stack and either (x) is
left-associative and its precedence is less or equal to that of (y), or (x) is right-associative
and its precedence is less than (y) [S4]:
Pop (y) from the stack [S5];
Add (y) output buffer [S6];
Push (x) on the stack [S7];
Else If token is left parenthesis, then push it on the stack [S8];
Else If token is a right parenthesis [S9]:
Until the top token (from the stack) is left parenthesis, pop from the stack to the output buffer [S10];
Also pop the left parenthesis but don’t include it in the output buffer [S11];
Else add token to output buffer [S12].
While there are still operator tokens in the stack, pop them to output [S13]



*/

#define MIN 0
#define EL 1
#define VAL 2

char* shuntingYard(string expression) {
    expression = "(" + expression + ")";
    string result;
    stack<char> hs;
    for (int i = 0; i < expression.size(); i++) {
        switch(expression[i]) {
        case '(':
             hs.push('(');
             break;
        case ')':
             while(hs.top() != '(') {
                char crr = hs.top();
                hs.pop();
                result.push_back(crr);
             }
             hs.pop();
             break;
        case '$':
             hs.push(expression[i]);
             break;
        case '@':
             hs.push(expression[i]);
             break;
        default:
             result.push_back(expression[i]);
             break;
        }
    }

    return &result[0];
}

void reverse(char* expression) {
    int n = strlen(expression);
    for (int i = 0; i < n/2 ; i++) {
        char temp = expression[i];
        expression[i] = expression[n-i-1];
        expression[n-i-1] = temp;
    }
}


int calculateExpression(char*& expression) {
    if((*expression) == '@') {
        return (el(calculateExpression(++expression), calculateExpression(++expression)));
    }
    if ((*expression) == '$') {
        return (min(calculateExpression(++expression), calculateExpression(++expression)));
    }
    if ((*expression) >= '0' && (*expression) <= '9')
        return ((*expression)-'0');
}

/*
    даден масив и числа а, б.
    първо отпечатва чилата по-малки от a, после числата между а и b,
    и накрая числата между b.
    без масиви, с 1 обхождане
*/

void printFunny(int* arr, int n, int a, int b, int i) {
    if (i == n) {
        return;
    }
    if(arr[i] < a) {
        cout << arr[i] << endl;
        printFunny(arr, n, a, b, i+1);
        return;
    }
    if (arr[i] >= a && arr[i] <=b) {
        printFunny(arr, n, a, b, i + 1);
        cout << arr[i] << endl;
        return;
    }

//    printFunny(arr, n, a, b, i + 1);
//    cout << arr[i] << endl;
//    return;
}

int main() {
//    char* expr = shuntingYard("(((3@2)$2)@(3@5))");
//    reverse(expr);
//    cout << calculateExpression(expr);
//    cout << boolalpha << true;
    int massive[] = {3, 2, 7, 2, 3, 4, 10, 21};
    int a = 3;
    int b = 8;
    printFunny(massive, 8, a, b, 0);

    return 0;

}
