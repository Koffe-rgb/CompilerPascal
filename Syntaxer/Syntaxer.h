#ifndef COMPILERPASCAL_SYNTAXER_H
#define COMPILERPASCAL_SYNTAXER_H

#pragma once
#include <set>
#include <vector>
#include "../Lexer/Lexer.h"
#include "../Headers/Sets.h"


class Syntaxer {
private:
    Lexer* lexer;
    IoModule* ioModule;
    AbstractToken* curToken;
public:
    Syntaxer(Lexer* lexer) {
        this->lexer = lexer;
        this->ioModule = lexer->getIoModule();
        this->curToken = nullptr;
    };
    ~Syntaxer() {
        delete lexer;
    };

    void start() {
        program();
    };
private:
    void listError(int code) const;

    void scanNextToken();

    void accept(TokenCodes tokenCode);
    bool isSymbolBelongTo(const set<TokenCodes>& starters) const;
    static set<TokenCodes> unionOf(const set<TokenCodes>& first, const set<TokenCodes>& second);
    void skipTo(const set<TokenCodes>& starters);
    void skipTo(const set<TokenCodes>& starters, const set<TokenCodes>& followers);


    // Грамматики
    void program();
    void block(const set<TokenCodes>& followers);
    void constPart(const set<TokenCodes>& followers);
    void constDeclaration(const set<TokenCodes>& followers);
    void constant(const set<TokenCodes>& followers);
    void typePart(const set<TokenCodes>& followers);
    void typeDeclaration(const set<TokenCodes>& followers);
    void type(const set<TokenCodes>& followers);
    void simpleType(const set<TokenCodes>& followers);
    void referenceType(const set<TokenCodes>& followers);
    void varPart(const set<TokenCodes>& followers);
    void varDeclaration(const set<TokenCodes>& followers);
    void operatorPart(const set<TokenCodes>& followers);
    void compoundOperator(const set<TokenCodes>& followers);
    void oper(const set<TokenCodes>& followers);
    void assignmentOperator(const set<TokenCodes>& followers);
    void variable(const set<TokenCodes>& followers);
    void expression(const set<TokenCodes>& followers);
    void simpleExpression(const set<TokenCodes>& followers);
    void term(const set<TokenCodes>& followers);
    void factor(const set<TokenCodes>& followers);
    void ifOperator(const set<TokenCodes>& followers);
    void whileOperator(const set<TokenCodes>& followers);
    void caseOperator(const set<TokenCodes>& followers);
    void elementOfVariants(const set<TokenCodes>& followers);
    void listOfMarks(const set<TokenCodes>& followers);
};

#endif //COMPILERPASCAL_SYNTAXER_H
