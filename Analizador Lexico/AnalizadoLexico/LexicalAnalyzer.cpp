#include <regex>
#include "LexicalAnalyzer.h"

using namespace std;
LexicalAnalyzer::LexicalAnalyzer(string c) {
    code = c;
    quoteFound = false;
    multipleCharKeyWordFound = false;
    index = 0;
    currentAnalyzingWord = "";
    resultText = "";
    keyWordsSize = 28;
}

string LexicalAnalyzer::analyzeCode() {
    analyze();
    return resultText;
}

void LexicalAnalyzer::analyze(){
    for(index = 0; index < code.length(); index++){
        if(multipleCharKeyWordFound){
            multipleCharKeyWordFound = false;
            continue;
        }
        if(!quoteFound){
            if(index + 1 < code.length()){
                if(code[index] == '!' && code[index+1] == '='){
                    twoCharKeyWord("!=");
                    continue;
                }else if(code[index] == '=' && code[index+1] == '='){
                    twoCharKeyWord("==");
                    continue;
                }else if(code[index] == '<' && code[index+1] == '='){
                    twoCharKeyWord("<=");
                    continue;
                }else if(code[index] == '>' && code[index+1] == '='){
                    twoCharKeyWord(">=");
                    continue;
                }else if(code[index] == '&' && code[index+1] == '&'){
                    twoCharKeyWord("&&");
                    continue;
                }else if(code[index] == '|' && code[index+1] == '|'){
                    twoCharKeyWord("||");
                    continue;
                }
                if(code[index] == ' '){
                    analyzeWord();
                }else if(code[index] == '\n'){
                    analyzeWord();
                }
                else if(code[index] == '\t'){
                    continue;
                }
                else if(code[index] == '\"'){
                    quotedText();
                }
                else if(wordInKeyWords(To_String(code[index]))){
                    textInKeyWords();
                }
                else{
                    currentAnalyzingWord = currentAnalyzingWord + code[index];
                }
            }
        }else{
            currentAnalyzingWord = currentAnalyzingWord + code[index];
            if(code[index] == '\"'){
                quoteFound = false;
                analyzeWord();
            }
        }
    }
}

void LexicalAnalyzer::twoCharKeyWord(string keyWord){
    analyzeWord();
    currentAnalyzingWord = keyWord;
    analyzeWord();
    multipleCharKeyWordFound = true;
}

void LexicalAnalyzer::analyzeWord(){
    if(regexCompare(regexOneOrMoreSpaces, currentAnalyzingWord)){
        currentAnalyzingWord = "";
    }
    if(currentAnalyzingWord != ""){
        currentAnalyzingWord = leftStrip(currentAnalyzingWord);
        resultText = resultText + currentAnalyzingWord + " " + lookForKeyWord() + "\n";
        currentAnalyzingWord = "";
    }
}

void LexicalAnalyzer::quotedText(){
    quoteFound = true;
    analyzeWord();
    currentAnalyzingWord = code[index];
}

bool LexicalAnalyzer::wordInKeyWords(string word){
    for(int i(0); i < keyWordsSize; i++){
        if(keyWords[i] == word){
            return true;
        }
    }
    return false;
}

void LexicalAnalyzer::textInKeyWords(){
    analyzeWord();
    currentAnalyzingWord = code[index];
    analyzeWord();
}

bool LexicalAnalyzer::regexCompare(string myRegex, string text){
    return regex_match(text, regex(myRegex));
}

string LexicalAnalyzer::leftStrip(string str){
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last-first+1));
}

string LexicalAnalyzer::lookForKeyWord(){
    if(currentAnalyzingWord == "+"){
        return "suma";
    }
    if(currentAnalyzingWord == "-"){
        return "resta";
    }
    if(currentAnalyzingWord == "*"){
        return "multiplicacion";
    }
    if(currentAnalyzingWord == "/"){
        return "division";
    }
    if(currentAnalyzingWord == "!="){
        return "diferente";
    }
    if(currentAnalyzingWord == "=="){
        return "igualdad";
    }
    if(currentAnalyzingWord == ">"){
        return "mayor que";
    }
    if(currentAnalyzingWord == "<"){
        return "menor que";
    }
    if(currentAnalyzingWord == "<="){
        return "menor igual";
    }
    if(currentAnalyzingWord == ">="){
        return "mayor igual";
    }
    if(currentAnalyzingWord == "="){
        return "igual";
    }
    if(currentAnalyzingWord == "("){
        return "parentesis izquierdo";
    }
    if(currentAnalyzingWord == ")"){
        return "parentesis derecho";
    }
    if(currentAnalyzingWord == "{"){
        return "llave izquierda";
    }
    if(currentAnalyzingWord == "}"){
        return "llave derecha";
    }
    if(currentAnalyzingWord == ":"){
        return "dos puntos";
    }
    if(currentAnalyzingWord == ";"){
        return "punto y coma";
    }
    if(currentAnalyzingWord == ","){
        return "coma";
    }
    if(currentAnalyzingWord == "&&"){
        return "and";
    }
    if(currentAnalyzingWord == "||"){
        return "or";
    }
    if(currentAnalyzingWord == "!"){
        return "not";
    }
    if(currentAnalyzingWord == "while"){
        return "ciclo while";
    }
    if(currentAnalyzingWord == "if"){
        return "condicional if";
    }
    if(currentAnalyzingWord == "else"){
        return "condicional else";
    }
    if(currentAnalyzingWord == "return"){
        return "retorno";
    }
    /*if(currentAnalyzingWord == "$"){
        return "pesos";
    }*/
    if(currentAnalyzingWord == "int"){
        return "dato entero";
    }
    if(currentAnalyzingWord == "float"){
        return "dato flotante";
    }
    if(currentAnalyzingWord == "char"){
        return "dato caracter";
    }
    if(currentAnalyzingWord == "void"){
        return "dato vacío";
    }
    if(regexCompare(regexNumber, currentAnalyzingWord)){
        return "constante";
    }
    if(regexCompare(regexQuote, currentAnalyzingWord)){
        return "constante";
    }
    return "identificador";
}

string LexicalAnalyzer::To_String(char myChar){
    string myStr = "";
    myStr.push_back(myChar);
    return myStr;
}
