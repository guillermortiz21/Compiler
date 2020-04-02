#ifndef SINTAXISANALYZER_H_INCLUDED
#define SINTAXISANALYZER_H_INCLUDED

#include <iostream>
#include <vector>
#include "LexicalAnalyzer.h"

using namespace std;

class SintaxisAnalyzer{
private:
    LexicalAnalyzer textAnalyzer;
    vector<int> parserStack;
    vector<vector<int>> tableFileList;
    vector<vector<int>> ruleFileList;
    string decodedCodeString;
    vector<int> decodedCode;
    string text;
    int index;
    string result;
    void decodedStringToArray();
    void printDecodedCode();
    void printParserStack();

public:
    SintaxisAnalyzer(string c);
    bool analyzeText();
    void getLists();
    int getNumberInTable(int row, int column);
    vector<int> getRule(int ruleNumber);
    bool parse();
};


#endif // SINTAXISANALYZER_H_INCLUDED
