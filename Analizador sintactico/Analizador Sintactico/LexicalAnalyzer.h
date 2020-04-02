#ifndef LEXICALANALYZER_H_INCLUDED
#define LEXICALANALYZER_H_INCLUDED

#include <iostream>

using namespace std;

/// constante -> 2 2.5 "cadena"
/// identificador
/// opSuma -> +
/// OpMul -> *
/// opRel -> != == > < >= <=
/// igual -> =
/// opIgualdad -> ==
/// parentesisIzq -> (
/// parentesisDer -> )
/// llaveIzq -> {
/// llaveDer -> }
/// puntoComa -> ;
/// coma -> ,
/// opAnd -> &&
/// opOr -> ||
/// opNot -> !
/// while
/// if
/// else
/// return
/// error
/// tipo de dato -> int float char void

class LexicalAnalyzer{
private:
    string code;
    string keyWords[28] = {"+", "-", "*", "/", "!=", "==", ">", "<", "<=", ">=", "=", "(", ")", "{", "}", ";", ",", "&&", "||", "!", "while", "if", "else", "return", "int", "float", "char", "void"};
    int keyWordsSize; /// Cambia este numero en el constructor si cambias el tamaño de arreglo de keyWords!!!!
    string currentAnalyzingWord;
    string resultText;
    bool quoteFound;
    bool multipleCharKeyWordFound;
    int index;
    string regexOneOrMoreSpaces = "^[[:space:]]+$";
    string regexNumber = "^[[:digit:]]*(([[:digit:]]\.)?|(\.[[:digit:]])?)?[[:digit:]]*$";
    string regexQuote = "^\".*\"$";
    string regexId = "^[_a-zA-Z][[:alnum:]]*$";


    void twoCharKeyWord(string keyWord);
    void analyzeWord();
    void quotedText();
    bool wordInKeyWords(string word);
    void textInKeyWords();
    bool regexCompare(string myRegex, string text);
    string leftStrip(string text);
    string lookForKeyWord();
    string lookForKeyWordID();
    string To_String(char myChar);

public:
    LexicalAnalyzer();
    string analyze();
    void setCode(string c);
};

#endif // LEXICALANALYZER_H_INCLUDED
