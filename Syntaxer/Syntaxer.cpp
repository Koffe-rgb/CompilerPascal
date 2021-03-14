#include "Syntaxer.h"

#include <utility>

using namespace std;

void Syntaxer::listError(int code) const {
    ioModule->logError(code);
}

void Syntaxer::scanNextToken() {
    curToken = lexer->scanNextToken();
}

void Syntaxer::accept(TokenCodes tokenCode) {
    if (curToken->getCode() == tokenCode) {
        curToken = lexer->scanNextToken();
    } else {
        ioModule->logError(tokenCode);
    }
}

bool Syntaxer::isSymbolBelong(const set<TokenCodes>& starters) const {
    return starters.contains(curToken->getCode());
}

set<TokenCodes> Syntaxer::unionOfSets(const set<TokenCodes>& first, const set<TokenCodes>& second) {
    set<TokenCodes> res = first;
    res.insert(second.begin(), second.end());
    return res;
}

void Syntaxer::skipTo(const set<TokenCodes>& starters) {
    while(!starters.contains(curToken->getCode())) {
        curToken = lexer->scanNextToken();
    }
}

void Syntaxer::skipTo(const set<TokenCodes> &starters, const set<TokenCodes> &followers) {
    while(!starters.contains(curToken->getCode()) && !followers.contains(curToken->getCode())) {
        curToken = lexer->scanNextToken();
    }
}

void Syntaxer::program() {
    // TODO initFictiousScope
    //initFictiousScope();
    //openScope();
    curToken = lexer->scanNextToken();
    accept(programsy);
    accept(ident);
    accept(semicolon);
    block(follow_block);
    accept(point);
}

void Syntaxer::block(const set<TokenCodes> &followers) {
    if (!isSymbolBelong(start_block)) {
        listError(18);
        skipTo(start_block, followers);
    } else {
        auto symbols = unionOfSets(follow_constpart, followers);
        constPart(symbols);
        symbols = unionOfSets(follow_typepart, followers);
        typePart(symbols);
        symbols = unionOfSets(follow_varpart, followers);
        varPart(symbols);
        statementPart(followers);
        if (!isSymbolBelong(followers)) {
            listError(6);
            skipTo(followers);
        }
    }
}

void Syntaxer::constPart(const set<TokenCodes> &followers) {
    if (!isSymbolBelong(start_constpart)) {
        listError(18);
        skipTo(start_constpart, followers);
    }
    if (curToken->getCode() == constsy) {
        accept(constsy);
        auto symbols = unionOfSets(follow_constdeclaration, followers);
        do {
            constDeclaration(symbols);
            accept(semicolon);
        } while (curToken->getCode() == ident);

        if (!isSymbolBelong(followers)) {
            listError(6);
            skipTo(followers);
        }
    }
}