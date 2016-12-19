#include<iostream>
#include <iomanip>
#include<fstream>
#include <vector>
#include <cstring>
#include <sstream>
#include<unordered_map>

#define TBLTN '\t'
#define NWLN '\n'
#define CMMA ','
#define EXCLM '!'
#define SPCE ' '
#define QSTN '?'
#define FLLSTP '.'

using namespace std;

const char delimiters[] = { '\t',
                                ',',
                                '!',
                                ' ',
                                '?',
                                '.',
                                ' '};

vector<string> tokenize(char word[]) {
    const char delimiters[] = { '\t',
                                ',',
                                '!',
                                ' ',
                                '?',
                                '.',
                                ' '};
    vector<string> tokens;
    char* res = strtok(word, delimiters);

    while(res != NULL) {
        string token(res);
        tokens.push_back(token);
        res = strtok(NULL, delimiters);
    }

    return tokens;
}

void inFile(ifstream& inFile, string name, unordered_map<string, unordered_map<string, bool>>& hmap) {
   string inputString;
   vector<bool> found;
    while(!inFile.eof()) {
        getline(inFile, inputString, delimiters[0]);

        vector<string> currentTokens =  tokenize(&inputString[0]);
        for(string tk : currentTokens) {
            if (hmap.find(tk) != hmap.end()) {
                hmap[tk][name] = true;
            }
        }
    }
}

void checkFiles(vector<string> files, unordered_map<string, unordered_map<string, bool>>& hmap) {
    for (string fileName : files) {
            ifstream fileStr(fileName);
            inFile(fileStr, fileName, hmap);
            fileStr.close();
    }
}


int main() {
  char word[] = "hello,world:hi";
  vector<string> res = tokenize(word);
  unordered_map<string, unordered_map<string, bool>> mmap;
  vector<string> fileNames;
  fileNames.push_back("file1.txt");
  fileNames.push_back("file2.txt");
  fileNames.push_back("file3.txt");
  fileNames.push_back("file4.txt");
  for (string crrStr : res) {
     for(string fileNm : fileNames) {
        mmap[crrStr][fileNm] = false;
     }
  }
  checkFiles(fileNames, mmap);

  for (string crrStr : res) {
    for (string fileName : fileNames) {
        cout << "FOR " << crrStr << ", FOR FILE " << fileName << ":: " << boolalpha << mmap[crrStr][fileName] << endl;
    }
  }

  return 0;
}

