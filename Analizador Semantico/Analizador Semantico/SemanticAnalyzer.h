#ifndef SEMANTICANALYZER_H_INCLUDED
#define SEMANTICANALYZER_H_INCLUDED

#include <iostream>
#include <vector>

using namespace std;

class SemanticAnalyzer{
private:
    string fileContents;
    string error;
    vector<string> variables;
    bool validCode;

    void findVariables();
    void validateOperations();
    vector<int> findIndexesInstring(string str, string s);
    int findNextSemicolon(int startIndex);
    void insertVariables(int startIndex, int endIndex);
    bool checkIfInVariables(string myVar);
    bool isInVector(vector<string> myVector, char str);
    void validateOperator(int index);
    vector<string> getWords(int index);

public:
    SemanticAnalyzer(string fileContents);
    string getError();
    bool getValidCode();
    void analyzeText();
};

#endif // SEMANTICANALYZER_H_INCLUDED
