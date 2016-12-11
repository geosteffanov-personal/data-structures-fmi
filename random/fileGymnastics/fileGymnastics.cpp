#include<iostream>
#include <vector>
#include <cstring>
#include<unordered_map>

#define TBLTN '\t'
#define NWLN '\n'
#define CMMA ','
#define EXCLM '!'
#define SPCE ' '
#define QSTN '?'
#define FLLSTP '.'

using namespace std;

const string fileNames[] = {
    "file0.txt",
    "file1.txt",
    "file2.txt",
    "file3.txt",
    "file4.txt"
};

vector<string> tokenize(char* word) {
    const char delimiters[] = { '\t',
                                ',',
                                '!',
                                ' ',
                                '?',
                                '.'};
    vector<string> tokens;
    char* res;
    res = strtok(word, ",");
    if (res != NULL) {
        cout << res << endl;
        string token (res);
        cout << "token: " << token << endl;
        tokens.push_back(token);
    }

    while(res != NULL) {
        res = strtok(NULL, ",");
        string token(res);
        if (res != NULL) {
            cout << res << endl;
            cout << "token: " << token << endl;
            tokens.push_back(token);
        }
    }

    return tokens;
}
/*
unordered_map<string, int> mapFile(ifstream& inFile) {
    unordered_map<string, int> result;
    string fileString;
    while(inFile.eof()) {
        getline(inFile, fileString);
        vector<string> currentTokens =  tokenize(fileString);

        for (int i = 0; i < currentTokens.size(); i++) {
            string currentToken = currentTokens[i];
            if (!(result.find(currentToken) != result.end())) {
                result[currentToken] = 0;
            }
            result[currentToken] += 1;
        }
    }

    return result;
}
*/

int main() {
 // string input;
  //getline()
  //char he[] = "aa,bb,cc,dd";
  //vector<string> result = tokenize(he);
  //for (int i = 0; i < result.size(); i++) {
  //  cout << result[i] << endl;
  //}
  string test(NULL);
  return 0;
}
