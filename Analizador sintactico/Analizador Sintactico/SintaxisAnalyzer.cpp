#include <iostream>
#include "SintaxisAnalyzer.h"
#include <string>
#include <cstring>
#include <vector>

using namespace std;

SintaxisAnalyzer::SintaxisAnalyzer(string c) {
    //cout << c;
    textAnalyzer.setCode(c);
    getLists();
}


void SintaxisAnalyzer::analyzeText(){
    this->decodedCodeString = this->textAnalyzer.analyze();
    decodedStringToArray();
    parse();
}

void SintaxisAnalyzer::decodedStringToArray(){
    string myStr("");
    for(int i(0); i < decodedCodeString.length(); i++){
        if(decodedCodeString[i] != ' '){
            myStr = myStr + decodedCodeString[i];
        }else{
            int myNum = stoi(myStr);
            decodedCode.push_back(myNum);
            myStr = "";
        }
    }
    decodedCode.push_back(21); // signo de pesos
}

int SintaxisAnalyzer::getNumberInTable(int row, int column){
    //cout << row << " " << column << endl;
    return tableFileList[row][column];
}

vector<int> SintaxisAnalyzer::getRule(int ruleNumber){
    ruleNumber = abs(int(ruleNumber)) - 1;
    return ruleFileList[ruleNumber];
}

void SintaxisAnalyzer::parse(){
    int row(0);
    bool error(false);
    bool accept(false);
    parserStack.push_back(row);
    while(!error && !accept && decodedCode.size() > 0){
        int column = decodedCode[0];
        int number = getNumberInTable(row, column);
        if(column == -1){
            result = "Error en an�lisis l�xico.";
            cout << "Error en an�lisis l�xico.";
            error = true;
        }else if(number == -1){
            accept = true;
            result = "Acepta.";
            cout << "Acepta.";
        }else if(number == 0){
            error = true;
            result = "Error.";
            cout << "Error.";
        }else if(number > 0){
            //cout << "desplazamiento" << endl;
            /// desplazamiento
            parserStack.push_back(column);
            parserStack.push_back(number);
            row = number;
            decodedCode.erase(decodedCode.begin());
        }else{
            //cout << "regla" << endl;
            vector<int> rule = getRule(number);
            int left = rule[0];
            int right = rule[1];
            //cout << "right " << right << endl;
            int i = 0;
            /// eliminar right * 2 elementos del stack
            //cout << "Antes de eliminar ";
            //printParserStack();
            while(i < right * 2){
                parserStack.pop_back();
                i = i + 1;
            }
            //cout << "Despu+es de eliminar ";
            //printParserStack();

            /// agregar lado izquierdo al stack
            parserStack.push_back(left);
            /// obtener utlimos dos del stack en la tabla y agregarlo al stack
            row = *(parserStack.rbegin()+1);
            column = parserStack.back();
            //printParserStack();
            //cout << row << " " << column << endl;
            number = getNumberInTable(row, column);
            parserStack.push_back(number);
            row = number;
        }
        //printParserStack();
    }
}

void SintaxisAnalyzer::printDecodedCode() {
    cout << "[";
    for(int i(0); i < decodedCode.size(); i++){
        cout << decodedCode[i] << ", ";
    }
    cout << "]\n";
}

void SintaxisAnalyzer::printParserStack() {
    cout << "[";
    for(int i(0); i < parserStack.size(); i++){
        cout << parserStack[i] << ", ";
    }
    cout << "]\n";
}

void SintaxisAnalyzer::getLists(){
    tableFileList =  {{5,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		-2,		0,		1,		2,		3,		0,		4,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		-1,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {5,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		-2,		0,		6,		2,		3,		0,		4,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {-4,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		-4,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {-5,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		-5,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		7,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		-3,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		0,		-7,		10,		9,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		8,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		0,		11,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {13,		0,		0,		0,		0,		-10,	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		12,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		14,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {-6,		-6,		0,		0,		0,		0,		0,		-6,		0,		-6,		-6,		-6,		0,		0,		0,		0,		0,		0,		0,		0,		0,		-6,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		0,		0,		0,		0,		15,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		16,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		0,		-7,		10,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		17,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		0,		0,		0,		0,		0,		19,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		18,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		0,		0,		21,		0,		-12,	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		20,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		0,		-8,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {-9,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		-9,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {26,		27,		0,		0,		0,		0,		0,		-15,	0,		28,		29,		30,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		24,		0,		0,		0,		0,		0,		22,		23,		0,		25,		0,		0,		0,		0,		0,		31,		0,		0},
 {0,		0,		0,		0,		0,		-11,	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {32,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		0,		0,		0,		0,		0,		0,		33,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {26,		27,		0,		0,		0,		0,		0,		-15,	0,		28,		29,		30,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		24,		0,		0,		0,		0,		0,		34,		23,		0,		25,		0,		0,		0,		0,		0,		31,		0,		0},
 {-17,		-17,	0,		0,		0,		0,		0,		-17,	0,		-17,	-17,	-17,	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {-18,		-18,	0,		0,		0,		0,		0,		-18,	0,		-18,	-18,	-18,	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		35,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		0,		0,		0,		37,		0,		0,		0,		36,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		0,		0,		0,		38,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		0,		0,		0,		39,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		46,		0,		0,		41,		0,		0,		0,		0,		0,		0,		0,		0,		47,		42,		43,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		44,		45,		0,		40},
 {0,		0,		48,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		49,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {-14,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		-14,	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		0,		0,		0,		0,		0,		0,		-16,	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		0,		-7,		10,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		8,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		46,		0,		0,		41,		0,		0,		0,		0,		0,		0,		0,		0,		47,		42,		43,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		44,		45,		0,		50},
 {0,		46,		0,		0,		41,		-29,	0,		0,		0,		0,		0,		0,		0,		47,		42,		43,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		51,		0,		44,		45,		0,		52},
 {0,		46,		0,		0,		41,		0,		0,		0,		0,		0,		0,		0,		0,		47,		42,		43,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		44,		45,		0,		53},
 {0,		46,		0,		0,		41,		0,		0,		0,		0,		0,		0,		0,		0,		47,		42,		43,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		44,		45,		0,		54},
 {0,		0,		55,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		57,		0,		56,		58,		59,		60,		61,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		46,		0,		0,		41,		0,		0,		0,		0,		0,		0,		0,		0,		47,		42,		43,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		44,		45,		0,		62},
 {0,		46,		0,		0,		41,		0,		0,		0,		0,		0,		0,		0,		0,		47,		42,		43,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		44,		45,		0,		63},
 {0,		46,		0,		0,		41,		0,		0,		0,		0,		0,		0,		0,		0,		47,		42,		43,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		44,		45,		0,		64},
 {0,		0,		-48,	-48,	0,		-48,	0,		0,		0,		0,		0,		0,		0,		0,		-48,	0,		-48,	-48,	-48,	-48,	-48,	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		0,		-33,	-33,	0,		-33,	0,		0,		0,		0,		0,		0,		0,		0,		-33,	0,		-33,	-33,	-33,	-33,	-33,	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		0,		-34,	-34,	37,		-34,	0,		0,		0,		0,		0,		0,		0,		0,		-34,	0,		-34,	-34,	-34,	-34,	-34,	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		0,		-35,	-35,	0,		-35,	0,		0,		0,		0,		0,		0,		0,		0,		-35,	0,		-35,	-35,	-35,	-35,	-35,	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {-25,		-25,	0,		0,		0,		0,		0,		-25,	0,		-25,	-25,	-25,	-25,	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		0,		0,		21,		0,		-12,	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		65,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		0,		66,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		57,		0,		56,		58,		59,		60,		61,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		0,		0,		0,		0,		67,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		0,		0,		69,		0,		-31,	0,		0,		0,		0,		0,		0,		0,		0,		57,		0,		56,		58,		59,		60,		61,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		68,		0,		0,		0,		0},
 {0,		0,		0,		0,		0,		70,		0,		0,		0,		0,		0,		0,		0,		0,		57,		0,		56,		58,		59,		60,		61,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		0,		0,		0,		0,		71,		0,		0,		0,		0,		0,		0,		0,		0,		57,		0,		56,		58,		59,		60,		61,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {-24,		-24,	0,		0,		0,		0,		0,		-24,	0,		-24,	-24,	-24,	-24,	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		46,		0,		0,		41,		0,		0,		0,		0,		0,		0,		0,		0,		47,		42,		43,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		44,		45,		0,		72},
 {0,		46,		0,		0,		41,		0,		0,		0,		0,		0,		0,		0,		0,		47,		42,		43,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		44,		45,		0,		73},
 {0,		46,		0,		0,		41,		0,		0,		0,		0,		0,		0,		0,		0,		47,		42,		43,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		44,		45,		0,		74},
 {0,		46,		0,		0,		41,		0,		0,		0,		0,		0,		0,		0,		0,		47,		42,		43,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		44,		45,		0,		75},
 {0,		46,		0,		0,		41,		0,		0,		0,		0,		0,		0,		0,		0,		47,		42,		43,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		44,		45,		0,		76},
 {0,		46,		0,		0,		41,		0,		0,		0,		0,		0,		0,		0,		0,		47,		42,		43,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		44,		45,		0,		77},
 {0,		0,		0,		0,		0,		78,		0,		0,		0,		0,		0,		0,		0,		0,		57,		0,		56,		58,		59,		60,		61,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		0,		-40,	-40,	0,		-40,	0,		0,		0,		0,		0,		0,		0,		0,		-40,	0,		-40,	-40,	-40,	-40,	-40,	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		0,		-41,	-41,	0,		-41,	0,		0,		0,		0,		0,		0,		0,		0,		-41,	0,		-41,	-41,	-41,	-41,	-41,	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		0,		0,		0,		0,		-13,	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {-21,		-21,	0,		0,		0,		0,		0,		-21,	0,		-21,	-21,	-21,	-21,	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		0,		-36,	-36,	0,		-36,	0,		0,		0,		0,		0,		0,		0,		0,		-36,	0,		-36,	-36,	-36,	-36,	-36,	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		0,		0,		0,		0,		-30,	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		46,		0,		0,		41,		0,		0,		0,		0,		0,		0,		0,		0,		47,		42,		43,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		44,		45,		0,		79},
 {0,		27,		0,		0,		0,		0,		83,		0,		0,		28,		29,		30,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		81,		0,		82,		0,		0,		0,		31,		80,		0},
 {0,		0,		0,		0,		0,		0,		83,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		84,		0,		0,		0,		0,		0,		0},
 {0,		0,		-42,	-42,	0,		-42,	0,		0,		0,		0,		0,		0,		0,		0,		-42,	0,		-42,	-42,	-42,	-42,	-42,	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		0,		-43,	-43,	0,		-43,	0,		0,		0,		0,		0,		0,		0,		0,		-43,	0,		-43,	-43,	-43,	-43,	-43,	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		0,		-44,	-44,	0,		-44,	0,		0,		0,		0,		0,		0,		0,		0,		-44,	0,		-44,	-44,	-44,	-44,	-44,	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		0,		-45,	-45,	0,		-45,	0,		0,		0,		0,		0,		0,		0,		0,		-45,	0,		-45,	-45,	-45,	-45,	-45,	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		0,		-46,	-46,	0,		-46,	0,		0,		0,		0,		0,		0,		0,		0,		-46,	0,		-46,	-46,	-46,	-46,	-46,	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		0,		-47,	-47,	0,		-47,	0,		0,		0,		0,		0,		0,		0,		0,		-47,	0,		-47,	-47,	-47,	-47,	-47,	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		0,		-39,	-39,	0,		-39,	0,		0,		0,		0,		0,		0,		0,		0,		-39,	0,		-39,	-39,	-39,	-39,	-39,	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		0,		0,		69,		0,		-31,	0,		0,		0,		0,		0,		0,		0,		0,		57,		0,		56,		58,		59,		60,		61,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		85,		0,		0,		0,		0},
 {-26,		-26,	0,		0,		0,		0,		0,		-26,	0,		-26,	-26,	-26,	87,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		86,		0,		0,		0,		0,		0,		0,		0},
 {-37,		-37,	0,		0,		0,		0,		0,		-37,	0,		-37,	-37,	-37,	-37,	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {-38,		-38,	0,		0,		0,		0,		0,		-38,	0,		-38,	-38,	-38,	-38,	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		27,		0,		0,		0,		0,		0,		-19,	0,		28,		29,		30,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		88,		89,		0,		0,		0,		0,		0,		31,		0,		0},
 {-23,		-23,	0,		0,		0,		0,		0,		-23,	0,		-23,	-23,	-23,	-23,	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		0,		0,		0,		0,		-32,	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {-22,		-22,	0,		0,		0,		0,		0,		-22,	0,		-22,	-22,	-22,	-22,	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		27,		0,		0,		0,		0,		83,		0,		0,		28,		29,		30,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		81,		0,		82,		0,		0,		0,		31,		90,		0},
 {0,		0,		0,		0,		0,		0,		0,		91,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		27,		0,		0,		0,		0,		0,		-19,	0,		28,		29,		30,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		92,		89,		0,		0,		0,		0,		0,		31,		0,		0},
 {-27,		-27,	0,		0,		0,		0,		0,		-27,	0,		-27,	-27,	-27,	-27,	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {-28,		-28,	0,		0,		0,		0,		0,		-28,	0,		-28,	-28,	-28,	-28,	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0},
 {0,		0,		0,		0,		0,		0,		0,		-20,	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0}};

 ruleFileList = {{22,1},
                {23,0},
                {23,2},
                {24,1},
                {24,1},
                {25,4},
                {26,0},
                {26,3},
                {27,6},
                {28,0},
                {28,3},
                {29,0},
                {29,4},
                {30,3},
                {31,0},
                {31,2},
                {32,1},
                {32,1},
                {33,0},
                {33,2},
                {34,4},
                {34,6},
                {34,5},
                {34,3},
                {34,2},
                {35,0},
                {35,2},
                {36,3},
                {37,0},
                {37,2},
                {38,0},
                {38,3},
                {39,1},
                {39,1},
                {39,1},
                {40,4},
                {41,1},
                {41,1},
                {42,3},
                {42,2},
                {42,2},
                {42,3},
                {42,3},
                {42,3},
                {42,3},
                {42,3},
                {42,3},
                {42,1}};
}
