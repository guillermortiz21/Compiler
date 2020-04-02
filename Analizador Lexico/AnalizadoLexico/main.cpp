#include <iostream>
#include <fstream>
#include "LexicalAnalyzer.h"

using namespace std;

int main() {
    string fileName;
    cout << "Nombre del archivo: ";
    getline(cin, fileName);
    ifstream inputFile(fileName);
    if(!inputFile.good()){
        cout << "Error en el nombre del archivo." << endl;
        return 0;
    }
    string fileStr("");
    string myStr;
    while(getline(inputFile, myStr)){
        fileStr = fileStr + myStr + "\n";
    }
    inputFile.close();
    LexicalAnalyzer myAnalyzer(fileStr);
    cout << myAnalyzer.analyzeCode();
    return 0;
}
