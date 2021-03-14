#ifndef COMPILERPASCAL_SYNTAXER_H
#define COMPILERPASCAL_SYNTAXER_H

#pragma once
#include <set>
#include <vector>
#include "../Lexer/Lexer.h"

const auto start_block = set<TokenCodes> { constsy, typesy, varsy, beginsy };
const auto start_constpart = set<TokenCodes> { constsy, typesy, varsy, beginsy };

const auto follow_constpart = set<TokenCodes> { typesy, varsy, beginsy };
const auto follow_typepart = set<TokenCodes> { varsy, beginsy };
const auto follow_varpart = set<TokenCodes> { beginsy };
const auto follow_constdeclaration = set<TokenCodes> { semicolon };
const auto follow_block = set<TokenCodes> { point };

class Syntaxer {
public:
    Lexer* lexer;
    IoModule* ioModule;
    AbstractToken* curToken;

    Syntaxer(Lexer* lexer) {
        this->lexer = lexer;
        this->ioModule = lexer->getIoModule();
        this->curToken = nullptr;
    }
    ~Syntaxer() = default;
private:
    void listError(int code) const;

    void scanNextToken();

    void accept(TokenCodes tokenCode);
    bool isSymbolBelong(const set<TokenCodes>& starters) const;
    set<TokenCodes> unionOfSets(const set<TokenCodes>& first, const set<TokenCodes>& second);
    void skipTo(const set<TokenCodes>& starters);
    void skipTo(const set<TokenCodes>& starters, const set<TokenCodes>& followers);

    void program();
    void block(const set<TokenCodes>& followers);
    void constPart(const set<TokenCodes>& followers);
    void constDeclaration(const set<TokenCodes>& followers);
    void constant(const set<TokenCodes>& followers);
    void typePart(const set<TokenCodes>& followers);
    void typeDeclaration(const set<TokenCodes>& followers);
    void type(const set<TokenCodes>& followers);
    void simpleType(const set<TokenCodes>& followers);
    void varPart(const set<TokenCodes>& followers);
    void varDeclaration(const set<TokenCodes>& followers);
    void statementPart(const set<TokenCodes>& followers);
    void compoundStatement(const set<TokenCodes>& followers);
    void statement(const set<TokenCodes>& followers);
    void assignmentStatement(const set<TokenCodes>& followers);
    void variable(const set<TokenCodes>& followers);
    void expression(const set<TokenCodes>& followers);
    void simpleExpression(const set<TokenCodes>& followers);
    void term(const set<TokenCodes>& followers);
    void factor(const set<TokenCodes>& followers);
    void ifStatement(const set<TokenCodes>& followers);
    void whileStatement(const set<TokenCodes>& followers);
    void caseStatement(const set<TokenCodes>& followers);
};

#endif //COMPILERPASCAL_SYNTAXER_H
