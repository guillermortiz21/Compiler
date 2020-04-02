#include <iostream>
#include "SemanticAnalyzer.h"

using namespace std;


SemanticAnalyzer::SemanticAnalyzer(string fileContents){
    this->fileContents = fileContents;
    validCode = true;
}

string SemanticAnalyzer::getError(){
    return this->error;
}

bool SemanticAnalyzer::getValidCode(){
    return this->validCode;
}

void SemanticAnalyzer::analyzeText(){
    this->findVariables();
    this->validateOperations();
}

void SemanticAnalyzer::findVariables(){
    /// tengo todo el archivo en file contents.
    /// en él buscar todas las veces que aparezca la keyword int
    /// cada que aparezca se estará declarando alguna variable.
    vector<int> intsPositions = this->findIndexesInstring(this->fileContents, "int");
    for(int i(1); i < intsPositions.size(); i++){
        /// cada vez que haya un int, habrá una declaración de varaible.
        /// 4 índices después del int empiezan las variables
        /// hasta encontrar el punto y coma. (pueden ser variables seapradas por comas)
        this->insertVariables(intsPositions[i] + 4, findNextSemicolon(intsPositions[i]));
    }
}

void SemanticAnalyzer::validateOperations(){
    vector<string> lookFor;
    lookFor.push_back("+");
    lookFor.push_back("*");
    lookFor.push_back(">");
    lookFor.push_back("<");
    lookFor.push_back("-");
    lookFor.push_back("/");
    lookFor.push_back("=");
    lookFor.push_back("&&");
    lookFor.push_back("||");
    lookFor.push_back("!");
    /// iteramos a través de todo mi archivo.
    /// y buscamos esos símbolos
    for(int i(0); i < this->fileContents.length(); i++){
        char myChar = this->fileContents[i];
        if(this->isInVector(lookFor, myChar)){
            this->validateOperator(i);
        }
    }
}

vector<int>  SemanticAnalyzer::findIndexesInstring(string str, string s){
    vector<int> myVector;
    for (int i = 0; i < str.length(); i++) {
        if (str.substr(i, s.length()) == s) {
            myVector.push_back(i);
        }
    }
    return myVector;
}

int SemanticAnalyzer::findNextSemicolon(int startIndex){
    bool found = false;
    int index = startIndex;
    while(!found){
        if(this->fileContents[index] == ';'){
            found = true;
            index--;
        }
        index++;
    }
    return index;
}

void SemanticAnalyzer::insertVariables(int startIndex, int endIndex){
    int index = startIndex;
    string varsString = "";
    while(index < endIndex){
        varsString = varsString + this->fileContents[index];
        index++;
    }
    /// en varsString tengo mis candidatos a variable
    /// la variable puede estar sola, o pueden haber comas
    /// hay que iterar por varsStrings e ir detectando variables.
    string myVar;
    vector<string> myVars;
    for(int i(0); i < varsString.length(); i++){
        /// iterar hasta encontrar una coma o hasta el fin de cadena
        if(varsString[i] == ','){
            myVars.push_back(myVar);
            myVar = "";
        }else if(varsString[i] == ' '){
            // ignoramos el espacio
        }else{
            myVar = myVar + varsString[i];
        }
    }
    myVars.push_back(myVar);
    for(int i(0); i < myVars.size(); i++){
        /// ya tengo mis variables separadas. Las voy a insertar en variables
        /// hay que validar que no estén ya ahí.
        if(this->checkIfInVariables(myVars[i])){
            this->error = this->error + "\nError: La variable " + myVars[i] + " ya habia sido declarada.";
            this->validCode = false;
        }else{
            this->variables.push_back(myVars[i]);
        }
    }
}

bool SemanticAnalyzer::checkIfInVariables(string myVar){
    for(int i(0); i < this->variables.size(); i++){
        if(this->variables[i] == myVar){
            return true;
        }
    }
    return false;
}

bool SemanticAnalyzer::isInVector(vector<string> myVector, char str){
   for(int i(0); i < myVector.size(); i++){
        if(myVector[i] == string(1, str)){
            return true;
        }
    }
    return false;
}

void SemanticAnalyzer::validateOperator(int index){
    char myChar = this->fileContents[index];
    string keyWord = "hola mundo";
    cout << keyWord << endl;

    if(myChar == '&'){
        if(this->fileContents[index+1] == '&'){
            keyWord = "&&";
        }else{
            this->error = this->error + "\nError: & sin doble &&";
        }
    }
    if(myChar == '|'){
        if(this->fileContents[index+1] == '|'){
            keyWord = "||";
        }else{
            this->error = this->error + "\nError: | sin doble ||.";
        }
    }
    if(myChar == '!' || myChar == '=' || myChar == '<' || myChar == '>'){
        if(this->fileContents[index+1] == '='){
            keyWord = myChar + "=";
        }else{
            keyWord = myChar + "";
        }
    }
    if(myChar == '+' || myChar == '*' || myChar == '-' || myChar == '/'){
        keyWord = myChar + "";
    }

    cout << keyWord << endl;

    /*if(myChar == '+' || myChar == '*' || myChar == '-' || myChar == '/'){
        keyWord = string(1, myChar);
        /// checar num/varDec atrás y num/varDec delante
    }else if(myChar == '>' || myChar == '<'){
        /// checar que no haya un = después
        if(this->fileContents[index+1] == '='){

        }
        /// checar num/varDec/negado atrás y num/varDec/negado delante
    }else if(myChar == '='){
        /// checar que no haya un = después
        /// si es = : checar varDec atrás y num/varDec/negacion delante
        /// si es == : checar num/varDec/negacion atrás y num/varDec/negacion delante
    }else if(myChar == '!'){
        /// checar que no hay un = después
        /// si es ! : checar que no haya nada atrás y num/varDec/negacion delante
        /// si es != : checar num/varDec/negacion atrás y num/varDec/negacion delante
    }else if(myChar == '&'){
        /// debe haber otro & después.
        /// checar num/varDec/negacion atrás y num/varDec/negacion delante
    }else if(myChar == '|'){
        /// debe haber otro | después.
        /// checar num/varDec/negacion atrás y num/varDec/negacion delante
    }*/
}

vector<string> SemanticAnalyzer::getWords(int index){

}
