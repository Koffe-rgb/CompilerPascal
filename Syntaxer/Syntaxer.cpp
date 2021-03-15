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

bool Syntaxer::isSymbolBelongTo(const set<TokenCodes>& starters) const {
    return starters.contains(curToken->getCode());
}

set<TokenCodes> Syntaxer::unionOf(const set<TokenCodes>& first, const set<TokenCodes>& second) {
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
    // TODO initFictitiousScope
    // TODO open scope
    curToken = lexer->scanNextToken();
    accept(programsy);
    accept(ident);
    accept(semicolon);
    block(follow_block);
    accept(point);
}

void Syntaxer::block(const set<TokenCodes> &followers) {
    if (!isSymbolBelongTo(start_block)) {
        listError(18);
        skipTo(start_block, followers);
    } else {
        auto symbols = unionOf(follow_constPart, followers);
        constPart(symbols);
        symbols = unionOf(follow_typePart, followers);
        typePart(symbols);
        symbols = unionOf(follow_varPart, followers);
        varPart(symbols);
        statementPart(followers);
        if (!isSymbolBelongTo(followers)) {
            listError(6);
            skipTo(followers);
        }
    }
}

void Syntaxer::constPart(const set<TokenCodes> &followers) {
    if (!isSymbolBelongTo(start_constPart)) {
        listError(18);
        skipTo(start_constPart, followers);
    }
    if (curToken->getCode() == constsy) {
        accept(constsy);
        auto symbols = unionOf(follow_constDeclaration, followers);
        do {
            constDeclaration(symbols);
            accept(semicolon);
        } while (curToken->getCode() == ident);

        if (!isSymbolBelongTo(followers)) {
            listError(6);
            skipTo(followers);
        }
    }
}

void Syntaxer::constDeclaration(const set<TokenCodes> &followers) {
    if (!isSymbolBelongTo(start_constDeclaration)) {
        listError(18);
        skipTo(start_constDeclaration, followers);
    }
    else {
        // TODO инит констант на семантике

        accept(ident);
        accept(TokenCodes::equal);
        // TODO проверка на уникальность в scope

        if (!isSymbolBelongTo(followers)) {
            listError(6);
            skipTo(followers);
        }
    }
}

void Syntaxer::constant(const set<TokenCodes> &followers) {
    if (!isSymbolBelongTo(start_constant)) {
        listError(18);
        skipTo(start_constant, followers);
    }
    else {
        switch (curToken->getCode()) {
            case intconst:
                // TODO create int const on semantic level
                accept(intconst);
                break;
            case floatconst:
                accept(floatconst);
                break;
            case stringconst:
                accept(stringconst);
                break;
            case charconst:
                accept(charconst);
                break;
            case ident:
                accept(ident);
                break;
            default:
                if (curToken->getCode() == TokenCodes::plus ||
                    curToken->getCode() == TokenCodes::minus)
                {
                    curToken = lexer->scanNextToken();
                    auto code = curToken->getCode();
                    switch (code) {
                        case intconst: break;
                        case floatconst: break;
                        case ident: break;
                    }
                    curToken = lexer->scanNextToken();
                }
                break;
        }
        if (!isSymbolBelongTo(followers)) {
            listError(6);
            skipTo(followers);
        }
    }
    //return type;
}

void Syntaxer::typePart(const set<TokenCodes> &followers) {
    if (!isSymbolBelongTo(start_typePart)) {
        listError(18);
        skipTo(start_typePart, followers);
    }
    if (curToken->getCode() == typesy) {
        accept(typesy);
        auto symbols = unionOf(follow_typeDeclaration, followers);

        do {
            typeDeclaration(symbols);
            accept(semicolon);
        } while (curToken->getCode() == ident);

        if (!isSymbolBelongTo(followers)) {
            listError(6);
            skipTo(followers);
        }
    }
}

void Syntaxer::typeDeclaration(const set<TokenCodes> &followers) {
    if (!isSymbolBelongTo(start_typeDeclaration)) {
        listError(18);
        skipTo(start_typeDeclaration, followers);
    }
    else {
        // TODO
        accept(ident);
        accept(TokenCodes::equal);
        type(followers);
        // TODO

        if (!isSymbolBelongTo(followers)) {
            listError(6);
            skipTo(followers);
        }
    }
}

void Syntaxer::type(const set<TokenCodes> &followers) {
    if (!isSymbolBelongTo(start_type)) {
        listError(10);
        skipTo(start_type, followers);
    }
    else {
        simpleType(followers);
    }
    if (!isSymbolBelongTo(followers)) {
        listError(6);
        skipTo(followers);
    }
}

void Syntaxer::simpleType(const set<TokenCodes> &followers) {

}
