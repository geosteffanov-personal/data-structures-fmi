#include <iostream>
#include <cstring>
#include <fstream>
#include <stack>
#include <queue>
using namespace std;

struct Plant {
    char species[20];
    double tInf;
    double tSup;

    Plant(const char species[20], double _tInf, double _tSup) : tInf(_tInf), tSup(_tSup) {
        int i = 0;
        for (i = 0; species[i] != '\0'; i++) {
            this->species[i] = species[i];
        }
        this->species[i] = '\0';
    }

    Plant& operator= (const Plant& other) {
        tInf = other.tInf;
        tSup = other.tSup;
        int i = 0;
        for (i = 0; other.species[i] != '\0'; i++) {
            species[i] = other.species[i];
        }
        species[i] = '\0';
    }

    bool operator==(const Plant& other) const {
        int i = 0;
        for (i = 0; species[i] != '\0'; i++) {
            if (species[i] != other.species[i])
                return false;
        }
        if (other.species[i] != '\0')
            return false;

        return tInf == other.tInf && tSup == other.tSup;
    }

    Plant(const Plant& other) {
        tInf = other.tInf;
        tSup = other.tSup;
        int i = 0;
        for (i = 0; other.species[i] != '\0'; i++) {
            species[i] = other.species[i];
        }
        species[i] = '\0';
    }

    bool canInhabit(const double& temp) const {
        return temp >= tInf && temp <= tSup;
    }

    double meanTemp() const {
        return (tInf + tSup)/2;
    }

    void print() const {
        cout << "====" << endl;
        cout << "name: " << species << endl;
        cout << "tMin, tMax: " << tInf << ":" << tSup << endl;
        cout << "====" << endl;
    }
};

queue<stack<Plant>> distribution(stack<Plant> S, stack<double> tempLevels) {
    queue<stack<Plant>> result;
    while (!tempLevels.empty()) {
        stack<Plant> crrSt;

        double crrTemp = tempLevels.top();
        tempLevels.pop();

        stack<Plant> copySt(S);
        while(!copySt.empty()) {
            Plant currentPl = copySt.top();
            copySt.pop();

            if (currentPl.canInhabit(crrTemp)) {
                crrSt.push(currentPl);
            }
        }

        result.push(crrSt);
    }
    return result;

}
stack<Plant> deserialize(const char* fileName) {
    stack<Plant> result;
    ifstream file;
    file.open(fileName);
    string line;
    double tInf,tSup;
    while(true) {
        if (!(getline(file, line))) break;
        char name[20];
        int i = 0;
        for (i = 0; line[i]!= '\0'; i++) {
            name[i] = line[i];
        }
        name[i] = '\0';

        if(file.peek() == '\n')
            file.ignore();

        file >> tInf >> tSup;
        Plant crrPl(name, tInf, tSup);
        result.push(crrPl);
        if (file.peek() == '\n')
            file.ignore();
    }
    file.close();
    return result;
}
void serializeStatistics(stack<Plant> S, double temparature) {
    ofstream file("botanic.bin", ios::binary);
    while(!S.empty()) {
        Plant crr = S.top();
        S.pop();
        double crrMean = crr.meanTemp();
        if (temparature -2 <= crrMean && crrMean <= temparature + 2) {
            file.write((char*)&crr, sizeof(Plant));
        }
    }
    file.close();
}
