#include <iostream>
#include <list>
#include <queue>
using namespace std;
using dpair =  pair<double, double>;

bool hasPNPartition(list<queue<double>> l) {
    bool result = false;

    double sumOfPositives = 0;
    double sumOfNegatives = 0;

    list<dpair> statistics;
    for (queue<double> q : l) {
        while(!q.empty()) {
            double p = q.front();
            q.pop();
            if (p < 0)
                sumOfNegatives+=p;
            else
                sumOfPositives+=p;
        }
        statistics.push_back(pair<double, double>(sumOfPositives, sumOfNegatives));
    }
    for (dpair crrPair : statistics) {
        double positive = crrPair.first;
        double negative = crrPair.second;
        if (positive == negative - sumOfNegatives) {
            result = true;
            cout << positive << endl;
        }
    }
    return result;
}
