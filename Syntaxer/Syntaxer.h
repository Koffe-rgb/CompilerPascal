#ifndef COMPILERPASCAL_SYNTAXER_H
#define COMPILERPASCAL_SYNTAXER_H

#pragma once
#include <set>

#include "../Lexer/Lexer.h"
#include "../Semancer/Semancer.h"
#include "Sets.h"


class Syntaxer {
private:
    Lexer* lexer;
    IoModule* ioModule;
    Semancer* semancer;
    AbstractToken* curToken;

    bool isNeedConvert;
    bool wasFirst;

    int lastIntegerValue;
    double lastRealValue;
    char lastCharValue;
    string lastStringValue;

    AbstractType* lastCaseType;

public:
    Syntaxer(string& path) {
        lexer = new Lexer(path);
        ioModule = lexer->getIoModule();
        semancer = new Semancer(ioModule);

        curToken = nullptr;
        wasFirst = false;
        isNeedConvert = false;
    };
    ~Syntaxer() {
        delete lexer;
        delete semancer;
    };

    IoModule *getIoModule() const;

    void start() {
        program();
    };
private:
    void listError(int code) const;

    void scanNextToken();

    void accept(TokenCodes tokenCode);
    bool isSymbolBelongTo(const set<TokenCodes>& symbols) const;
    static set<TokenCodes> unionOf(const set<TokenCodes>& first, const set<TokenCodes>& second);
    void skipTo(const set<TokenCodes>& symbols);
    void skipTo(const set<TokenCodes>& symbols, const set<TokenCodes>& followers);


    // Грамматики
    void program();
    void block(const set<TokenCodes>& followers);
    void constPart(const set<TokenCodes>& followers);
    void constDeclaration(const set<TokenCodes>& followers);
    AbstractType* constant(const set<TokenCodes>& followers);
    void typePart(const set<TokenCodes>& followers);
    void typeDeclaration(const set<TokenCodes>& followers);
    AbstractType* type(const set<TokenCodes>& followers);
    AbstractType* simpleType(const set<TokenCodes>& followers);
    AbstractType* referenceType(const set<TokenCodes>& followers);
    void varPart(const set<TokenCodes>& followers);
    void varDeclaration(const set<TokenCodes>& followers);
    void operatorPart(const set<TokenCodes>& followers);
    void compoundOperator(const set<TokenCodes>& followers);
    void oper(const set<TokenCodes>& followers);
    void assignmentOperator(const set<TokenCodes>& followers);
    AbstractType* variable(const set<TokenCodes>& followers);
    AbstractType* expression(const set<TokenCodes>& followers);
    AbstractType* simpleExpression(const set<TokenCodes>& followers);
    AbstractType* term(const set<TokenCodes>& followers);
    AbstractType* factor(const set<TokenCodes>& followers);
    void ifOperator(const set<TokenCodes>& followers);
    void whileOperator(const set<TokenCodes>& followers);
    void caseOperator(const set<TokenCodes>& followers);
    void elementOfVariants(const set<TokenCodes>& followers);
    void listOfMarks(const set<TokenCodes>& followers);
};

#endif //COMPILERPASCAL_SYNTAXER_H
