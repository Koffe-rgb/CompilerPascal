#ifndef COMPILERPASCAL_SYNTAXER_H
#define COMPILERPASCAL_SYNTAXER_H

#pragma once
#include <exception>
#include <set>
#include <vector>
#include "../Lexer/Lexer.h"
#include "../Headers/Type.h"

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
    //void listError(int code, int idx, int line);

    void scanNextToken();

    void accept(TokenCodes tokenCode);
    bool isSymbolBelong(const set<TokenCodes>& starters) const;
    set<TokenCodes> unionOfSets(const set<TokenCodes>& first, const set<TokenCodes>& second);
    void skipTo(const set<TokenCodes>& starters);
    void skipTo(const set<TokenCodes>& starters, const set<TokenCodes>& followers);

    void openScope();
    void closeScope();
    void initFictiousScope();

    void program();
    void block(const set<TokenCodes>& followers);
    void constPart(const set<TokenCodes>& followers);
    void constDeclaration(const set<TokenCodes>& followers);
    Type constant(const set<TokenCodes>& followers);
    void typePart(const set<TokenCodes>& followers);
    void typeDeclaration(const set<TokenCodes>& followers);
    Type type(const set<TokenCodes>& followers);
    //Type searchType();
    Type simpleType(const set<TokenCodes>& followers);
    Type enumType(const set<TokenCodes>& followers);
    Type limitedType(const set<TokenCodes>& followers);
    Type compositeType(const set<TokenCodes>& followers);
    Type arrayType(const set<TokenCodes>& followers);
    void varPart(const set<TokenCodes>& followers);
    //void addVariableTo(vector)
    void varDeclaration(const set<TokenCodes>& followers);
    void statementPart(const set<TokenCodes>& followers);
    void compoundStatement(const set<TokenCodes>& followers);
    void writeLine(const set<TokenCodes>& followers);
    void statement(const set<TokenCodes>& followers);
    bool checkAssignmentTypes(Type varType, Type exprType);
    void assignmentStatement(const set<TokenCodes>& followers);
    Type variable(const set<TokenCodes>& followers);
    Type checkRelationOperation(Type firstType, Type secondType, int operation);
    Type expression(const set<TokenCodes>& followers);
    void checkRightSign(Type type);
    Type checkAdditiveOperation(Type firstType, Type secondType, int operation, int errPos);
    Type simpleExpression(const set<TokenCodes>& followers);
    Type checkMultiplicativeOperation(Type firstType, Type secondType, int operation, int errPos);
    Type term(const set<TokenCodes>& followers);
    Type checkLogical(Type type);
    //Identifier searchIdentifier(Scope scope, string name);
    Type factor(const set<TokenCodes>& followers);
    void ifStatement(const set<TokenCodes>& followers);
    void whileStatement(const set<TokenCodes>& followers);
};

#endif //COMPILERPASCAL_SYNTAXER_H
