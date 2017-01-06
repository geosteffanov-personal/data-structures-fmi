#include <iostream>
#include <assert.h>
#include "task1.cpp"
using namespace std;

void testDistribution() {
        Plant A("A", 0, 5);
        Plant B("B", 2.3, 7);
        Plant C("C", 11, 25);
        Plant D("D", 10, 23);

        double temp1 = 2.5;
        double temp2 = 11.2;
        double temp3 = 6;
        double temp4 = 10;
        double temp5 = 8;

        stack<Plant> plants;
        plants.push(D);
        plants.push(C);
        plants.push(B);
        plants.push(A);

        stack<double> temps;
        temps.push(temp5);
        temps.push(temp4);
        temps.push(temp3);
        temps.push(temp2);
        temps.push(temp1);
        queue<stack<Plant>> result = distribution(plants, temps);
        queue<stack<Plant>> expected;
        stack<Plant> exp1;
        exp1.push(A);
        exp1.push(B);
        stack<Plant> exp2;
        exp2.push(C);
        exp2.push(D);
        stack<Plant> exp3;
        exp3.push(B);
        stack<Plant> exp4;
        exp4.push(D);
        stack<Plant> exp5;

        expected.push(exp1);
        expected.push(exp2);
        expected.push(exp3);
        expected.push(exp4);
        expected.push(exp5);
        assert(expected == result);
}

void testDeserialization() {
    Plant p1("plantA", 3.3, 2);
    Plant p2("planB", 4.5, 4.7);
    Plant p3("plantC", 990, 1011);
    stack<Plant> expected;
    expected.push(p1);
    expected.push(p2);
    expected.push(p3);
    stack<Plant> result = deserialize("plants.txt");
    assert(result == expected);
}

void testStatistics() {
    Plant tree1("tree 1", 2.3, 6.9);
    Plant tree2("tree 2", 8, 8);
    Plant tree3("tree 3", 4.6, 4.9);

    stack<Plant> st;
    st.push(tree3);
    st.push(tree2);
    st.push(tree1);
    serializeStatistics(st, 4.6);
    ifstream reader("botanic.bin", ios::binary);
    stack<Plant> res;
    Plant test("", 1,1);
    reader.read((char *)&test, sizeof(Plant));
    assert(test == tree1);
    reader.read((char *)&test, sizeof(Plant));
    assert(test == tree3);
}
int main() {
    testDistribution();
    testDeserialization();
    testStatistics();
}

