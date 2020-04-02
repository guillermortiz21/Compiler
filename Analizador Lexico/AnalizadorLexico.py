# constante -> 2 2.5 "cadena"
# identificador
# opSuma -> +
# OpMul -> *
# opRel -> != == > < >= <= 
# igual -> =
# opIgualdad -> ==
# parentesisIzq -> (
# parentesisDer -> )
# llaveIzq -> {
# llaveDer -> }
# puntoComa -> ;
# coma -> ,
# opAnd -> &&
# opOr -> ||
# opNot -> !
# while
# if
# else
# return
# pesos -> $
# error
# tipo de dato -> int float char void

from tkinter import *
import re


class TextAnalyzer():
    def __init__(self):
        self.keyWords = ["+", "-", "*", "/", "!=", "==", ">", "<", "<=", ">=", "=", "(", ")", "{", "}", ";", ",", "&&", "||", "!",
                         "while", "if", "else", "return", "$", "int", "float", "char", "void"]
        self.window = Tk()
        self.codeEntry = Text(self.window, height=30, width=50)
        self.analyzeButton = Button(self.window, text="Analizar Texto", command=self.analyzeText)
        self.resultBox = Text(self.window, height=30, width=50)
        self.resultText = ""
        self.currentAnalyzingWord = ""
        self.analyzingText = ""
        self.index = 0
        self.multipleCharKeyWordFound = False
        self.quoteFound = False
        self.regexOneOrMoreSpaces = "^\s+$"
        self.regexNumber = "^\d*((\d\.)?|(\.\d)?)?\d*$"
        self.regexQuote = "^\".*\"$"
        

    def runWindow(self):
        self.window.title("Analizador Léxico")
        self.window.geometry('820x550')
        self.codeEntry.grid(column=0, row=0)
        self.resultBox.grid(column=1, row=0)
        self.resultBox.config(state='disabled')
        self.analyzeButton.grid(column=0, row=1, columnspan=2, sticky=N + S + E + W)
        self.window.mainloop()

    def analyzeText(self):
        self.analyzingText = self.codeEntry.get("1.0", 'end-1c')
        self.currentAnalyzingWord = ""
        self.resultText = ""
        self.quoteFound = False
        self.multipleCharKeyWordFound = False
        self.index = 0
        for self.index in range(len(self.analyzingText)):
            if self.multipleCharKeyWordFound:
                self.multipleCharKeyWordFound = False
                continue
            if not self.quoteFound:
                if self.index+1 < len(self.analyzingText):
                    if self.analyzingText[self.index] == "!" and self.analyzingText[self.index+1] == "=":
                        self.twoCharKeyWord("!=")
                        continue
                    elif self.analyzingText[self.index] == "=" and self.analyzingText[self.index+1] == "=":
                        self.twoCharKeyWord("==")
                        continue
                    elif self.analyzingText[self.index] == "<" and self.analyzingText[self.index+1] == "=":
                        self.twoCharKeyWord("<=")
                        continue
                    elif self.analyzingText[self.index] == ">" and self.analyzingText[self.index+1] == "=":
                        self.twoCharKeyWord(">=")
                        continue
                    elif self.analyzingText[self.index] == "&" and self.analyzingText[self.index+1] == "&":
                        self.twoCharKeyWord("&&")
                        continue
                    elif self.analyzingText[self.index] == "|" and self.analyzingText[self.index+1] == "|":
                        self.twoCharKeyWord("||")
                        continue
                if self.analyzingText[self.index] == " ":
                    self.analyzeWord()
                elif self.analyzingText[self.index] == "\n":
                    self.analyzeWord()
                elif self.analyzingText[self.index] == "\t": #tab
                    continue
                elif self.analyzingText[self.index] == "\"": #quote. leer hasta encontrar el cierre
                    self.quotedText()
                elif self.analyzingText[self.index] in self.keyWords:
                    self.textInKeyWords()
                else:
                    self.currentAnalyzingWord = self.currentAnalyzingWord + self.analyzingText[self.index]
            else:
                self.currentAnalyzingWord = self.currentAnalyzingWord + self.analyzingText[self.index]
                if self.analyzingText[self.index] == "\"":
                    self.quoteFound = False
                    self.analyzeWord()
        self.analyzeWord()
        self.printResult()

    def twoCharKeyWord(self, keyWord):
        self.analyzeWord()
        self.currentAnalyzingWord = keyWord
        self.analyzeWord()
        self.multipleCharKeyWordFound = True

    def analyzeWord(self):
        if re.search(self.regexOneOrMoreSpaces, self.currentAnalyzingWord):
            self.currentAnalyzingWord = ""
        if self.currentAnalyzingWord != "": 
            self.currentAnalyzingWord = self.currentAnalyzingWord.lstrip()
            self.resultText = self.resultText + self.currentAnalyzingWord + " " + self.lookForKeyword() + "\n"
            self.currentAnalyzingWord = ""

    def quotedText(self):
        self.quoteFound = True
        self.analyzeWord()
        self.currentAnalyzingWord = self.analyzingText[self.index]

    def textInKeyWords(self):
        self.analyzeWord()
        self.currentAnalyzingWord = self.analyzingText[self.index]
        self.analyzeWord()

    def getKeywordID(self):
        if self.currentAnalyzingWord == "+":
            return "suma"
        if self.currentAnalyzingWord == "-":
            return "resta"
        if self.currentAnalyzingWord == "*":
            return "multiplicación"
        if self.currentAnalyzingWord == "/":
            return "división"
        if self.currentAnalyzingWord == "!=":
            return "diferente"
        if self.currentAnalyzingWord == "==":
            return "igualdad"
        if self.currentAnalyzingWord == ">":
            return "mayor que"
        if self.currentAnalyzingWord == "<":
            return "menor que"
        if self.currentAnalyzingWord == "<=":
            return "menor igual"
        if self.currentAnalyzingWord == ">=":
            return "mayor igual"
        if self.currentAnalyzingWord == "=":
            return "igual"
        if self.currentAnalyzingWord == "(":
            return "paréntesis izquierdo"
        if self.currentAnalyzingWord == ")":
            return "paréntesis derecho"
        if self.currentAnalyzingWord == "{":
            return "llave izquierda"
        if self.currentAnalyzingWord == "}":
            return "llave derecha"
        if self.currentAnalyzingWord == ":":
            return "dos puntos"
        if self.currentAnalyzingWord == ";":
            return "punto y coma"
        if self.currentAnalyzingWord == ",":
            return "coma"
        if self.currentAnalyzingWord == "&&":
            return "and"
        if self.currentAnalyzingWord == "||":
            return "or"
        if self.currentAnalyzingWord == "!":
            return "not"
        if self.currentAnalyzingWord == "while":
            return "ciclo while"
        if self.currentAnalyzingWord == "if":
            return "condicional if"
        if self.currentAnalyzingWord == "else":
            return "condicional else"
        if self.currentAnalyzingWord == "return":
            return "retorno"
        if self.currentAnalyzingWord == "$":
            return "pesos"
        if self.currentAnalyzingWord == "int":
            return "dato entero"
        if self.currentAnalyzingWord == "float":
            return "dato flotante"
        if self.currentAnalyzingWord == "char":
            return "dato caracter"
        if self.currentAnalyzingWord == "void":
            return "dato vacío"
        if re.search(self.regexNumber, self.currentAnalyzingWord):
            return "constante"
        if re.search(self.regexQuote, self.currentAnalyzingWord):
            return "constante"
        return "identificador"


    def lookForKeyword(self):
        if self.currentAnalyzingWord == "+":
            return "suma"
        if self.currentAnalyzingWord == "-":
            return "resta"
        if self.currentAnalyzingWord == "*":
            return "multiplicación"
        if self.currentAnalyzingWord == "/":
            return "división"
        if self.currentAnalyzingWord == "!=":
            return "diferente"
        if self.currentAnalyzingWord == "==":
            return "igualdad"
        if self.currentAnalyzingWord == ">":
            return "mayor que"
        if self.currentAnalyzingWord == "<":
            return "menor que"
        if self.currentAnalyzingWord == "<=":
            return "menor igual"
        if self.currentAnalyzingWord == ">=":
            return "mayor igual"
        if self.currentAnalyzingWord == "=":
            return "igual"
        if self.currentAnalyzingWord == "(":
            return "paréntesis izquierdo"
        if self.currentAnalyzingWord == ")":
            return "paréntesis derecho"
        if self.currentAnalyzingWord == "{":
            return "llave izquierda"
        if self.currentAnalyzingWord == "}":
            return "llave derecha"
        if self.currentAnalyzingWord == ":":
            return "dos puntos"
        if self.currentAnalyzingWord == ";":
            return "punto y coma"
        if self.currentAnalyzingWord == ",":
            return "coma"
        if self.currentAnalyzingWord == "&&":
            return "and"
        if self.currentAnalyzingWord == "||":
            return "or"
        if self.currentAnalyzingWord == "!":
            return "not"
        if self.currentAnalyzingWord == "while":
            return "ciclo while"
        if self.currentAnalyzingWord == "if":
            return "condicional if"
        if self.currentAnalyzingWord == "else":
            return "condicional else"
        if self.currentAnalyzingWord == "return":
            return "retorno"
        if self.currentAnalyzingWord == "$":
            return "pesos"
        if self.currentAnalyzingWord == "int":
            return "dato entero"
        if self.currentAnalyzingWord == "float":
            return "dato flotante"
        if self.currentAnalyzingWord == "char":
            return "dato caracter"
        if self.currentAnalyzingWord == "void":
            return "dato vacío"
        if re.search(self.regexNumber, self.currentAnalyzingWord):
            return "constante"
        if re.search(self.regexQuote, self.currentAnalyzingWord):
            return "constante"
        return "identificador"

    def addToResultText(self, text):
        self.resultText = self.resultText + text + "\n"

    def printResult(self):
        self.resultBox.config(state='normal')
        self.resultBox.delete("0.0", END)
        self.resultBox.insert("1.0", self.resultText)
        self.resultBox.config(state='disabled')
        self.resultText = ""
        self.currentAnalyzingWord = ""


def main():
    textAnalyzer = TextAnalyzer()
    textAnalyzer.runWindow()


main()
