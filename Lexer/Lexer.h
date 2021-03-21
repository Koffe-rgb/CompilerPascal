#ifndef COMPILERPASCAL_LEXER_H
#define COMPILERPASCAL_LEXER_H

#pragma once
#include "../IoModule/IoModule.h"
#include "../Headers/Token.h"
#include "../Headers/Codes.h"
#include <string>
#include <algorithm>
#include <cctype>
#include <set>

using namespace std;

class Lexer {
private:
    IoModule* ioModule;		// модуль ввода-вывода
    char curChar;			// текущая литера, полученная от модуля ввода-вывода
    int LEN_MAX = 40;		// максимальная длина строки / имени
    int MAX_INT = INT_MAX;

private:

    AbstractToken* scanLater();
    AbstractToken* scanGreater();
    AbstractToken* scanLeftPar();
    AbstractToken* scanFlpar();
    AbstractToken* scanFrpar();
    AbstractToken* scanStar();
    AbstractToken* scanColon();
    AbstractToken* scanPoint();

    AbstractToken* scanName();
    AbstractToken* scanNumberConstant();
    AbstractToken* scanStringConstant();

public:

    Lexer(IoModule* ioModule) {
        this->ioModule = ioModule;
        curChar = '\0';
    }
    ~Lexer() {
        delete ioModule;
    }

    AbstractToken* scanNextToken();

    IoModule* getIoModule() const;
};


#endif //COMPILERPASCAL_LEXER_H
