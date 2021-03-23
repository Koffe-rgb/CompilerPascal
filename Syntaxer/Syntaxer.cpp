#include "Syntaxer.h"


using namespace std;

void Syntaxer::listError(int code) const {
    ioModule->logError(code, curToken->toString().size());
}

void Syntaxer::scanNextToken() {
    delete curToken;
    curToken = lexer->scanNextToken();
}

void Syntaxer::accept(TokenCodes tokenCode) {
    if (curToken->getCode() == tokenCode) {
        scanNextToken();
    } else {
        ioModule->logError(tokenCode, curToken->toString().size());
    }
}

bool Syntaxer::isSymbolBelongTo(const set<TokenCodes>& symbols) const {
    return symbols.contains(curToken->getCode());
}

set<TokenCodes> Syntaxer::unionOf(const set<TokenCodes>& first, const set<TokenCodes>& second) {
    set<TokenCodes> res = first;
    res.insert(second.begin(), second.end());
    return res;
}

void Syntaxer::skipTo(const set<TokenCodes>& symbols) {
    while(!symbols.contains(curToken->getCode())) {
        scanNextToken();
    }
}

void Syntaxer::skipTo(const set<TokenCodes> &symbols, const set<TokenCodes> &followers) {
    while(!symbols.contains(curToken->getCode()) && !followers.contains(curToken->getCode())) {
        scanNextToken();
    }
}

void Syntaxer::program() {
    scanNextToken();
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
    }
    if (isSymbolBelongTo(start_block)) {
        auto symbols = unionOf(follow_constPart, followers);
        constPart(symbols);
        symbols = unionOf(follow_typePart, followers);
        typePart(symbols);
        symbols = unionOf(follow_varPart, followers);
        varPart(symbols);
        operatorPart(followers);
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
    }
}

void Syntaxer::constDeclaration(const set<TokenCodes> &followers) {
    if (!isSymbolBelongTo(start_constDeclaration)) {
        listError(18);
        skipTo(start_constDeclaration, followers);
    }
    if (isSymbolBelongTo(start_constDeclaration)) {
        accept(ident);
        accept(TokenCodes::equal);
        constant(followers);
    }
}

void Syntaxer::constant(const set<TokenCodes> &followers) {
    if (!isSymbolBelongTo(start_constant)) {
        listError(18);
        skipTo(start_constant, followers);
    }
    if (isSymbolBelongTo(start_constant)) {
        switch (curToken->getCode()) {
            case intconst:
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
                    scanNextToken();
                    auto code = curToken->getCode();
                    switch (code) {
                        case intconst: break;
                        case floatconst: break;
                        case ident: break;
                    }
                    scanNextToken();
                }
                break;
        }
    }
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
    }
}

void Syntaxer::typeDeclaration(const set<TokenCodes> &followers) {
    if (!isSymbolBelongTo(start_typeDeclaration)) {
        listError(18);
        skipTo(start_typeDeclaration, followers);
    }
    if (isSymbolBelongTo(start_typeDeclaration)) {
        accept(ident);
        accept(TokenCodes::equal);
        type(followers);
    }
}

void Syntaxer::type(const set<TokenCodes> &followers) {
    if (!isSymbolBelongTo(start_type)) {
        listError(10);
        skipTo(start_type, followers);
    }
    if (isSymbolBelongTo(start_type)) {
        if (curToken->getCode() == arrow) {
            referenceType(followers);
        }
        else {
            simpleType(followers);
        }
    }
}

void Syntaxer::simpleType(const set<TokenCodes> &followers) {
    if (!isSymbolBelongTo(start_simpleType)) {
        listError(10);
        skipTo(start_simpleType, followers);
    }
    if (isSymbolBelongTo(start_simpleType)) {
        if (curToken->getCode() == ident) {
            accept(ident);
        }
    }
}

void Syntaxer::referenceType(const set<TokenCodes> &followers) {
    if (!isSymbolBelongTo(start_linkType)) {
        listError(22);
        skipTo(start_linkType, followers);
    }
    if (isSymbolBelongTo(start_linkType)) {
        accept(arrow);
        accept(ident);
    }
}

void Syntaxer::varPart(const set<TokenCodes> &followers) {
    if (!isSymbolBelongTo(start_varPart)) {
        listError(18);
        skipTo(start_varPart, followers);
    }
    if (isSymbolBelongTo(start_varPart)) {
        accept(varsy);
        auto symbols = unionOf(follow_varDeclaration, followers);
        do {
            varDeclaration(symbols);
            accept(semicolon);
        } while (curToken->getCode() == ident);
    }
}

void Syntaxer::varDeclaration(const set<TokenCodes> &followers) {
    if (!isSymbolBelongTo(start_varDeclaration)) {
        listError(2);
        skipTo(start_varDeclaration, followers);
    }
    if (isSymbolBelongTo(start_varDeclaration)) {
        accept(ident);
        while (curToken->getCode() == comma) {
            accept(comma);
            accept(ident);
        }
        accept(colon);
        type(followers);
    }
}

void Syntaxer::operatorPart(const set<TokenCodes> &followers) {
    compoundOperator(followers);
}

void Syntaxer::compoundOperator(const set<TokenCodes> &followers) {
    if(!isSymbolBelongTo(start_compoundOperator)) {
        listError(22);
        skipTo(start_compoundOperator, followers);
    }
    if (isSymbolBelongTo(start_compoundOperator)) {
        accept(beginsy);
        auto symbols = unionOf(follow_operator, followers);
        while(isSymbolBelongTo(start_operator)) {
            oper(symbols);
            accept(semicolon);
        }
        accept(endsy);
    }
}

void Syntaxer::oper(const set<TokenCodes> &followers) {
    if (!isSymbolBelongTo(start_operator)) {
        listError(22);
        skipTo(start_operator, followers);
    }
    if (isSymbolBelongTo(start_operator)) {
        switch (curToken->getCode()) {
            case ident: assignmentOperator(followers); break;
            case beginsy: compoundOperator(followers); break;
            case ifsy:
                ifOperator(followers); break;
            case casesy:
                caseOperator(followers); break;
            case whilesy:
                whileOperator(followers); break;
            case semicolon:
            case endsy:
            case elsesy: break;
        }
    }
}

void Syntaxer::assignmentOperator(const set<TokenCodes> &followers) {
    if (!isSymbolBelongTo(start_assignmentOperator)) {
        listError(22);
        skipTo(start_assignmentOperator, followers);
    }
    if (isSymbolBelongTo(start_assignmentOperator)) {
        auto symbols = unionOf(follow_assignmentOperator, followers);
        variable(symbols);
        accept(assign);
        expression(followers);
    }
}

void Syntaxer::variable(const set<TokenCodes> &followers) {
    if (!isSymbolBelongTo(start_variable)) {
        listError(22);
        skipTo(start_variable, followers);
    }
    if (isSymbolBelongTo(start_variable)) {
        accept(ident);
        // TODO
        if (curToken->getCode() == arrow) {
            accept(arrow);
        }
    }
}

void Syntaxer::expression(const set<TokenCodes> &followers) {
    if (!isSymbolBelongTo(start_expression)) {
        listError(23);
        skipTo(start_expression, followers);
    }
    if (isSymbolBelongTo(start_expression)) {
        auto symbols = unionOf(follow_simpleExpression, followers);
        simpleExpression(symbols);

        auto code = curToken->getCode();
        if (code == TokenCodes::equal || code == latergreater ||
            code == later || code == laterequal ||
            code == greaterequal || code == TokenCodes::greater)
        {
            scanNextToken();
            simpleExpression(followers);
        }
    }
}

void Syntaxer::simpleExpression(const set<TokenCodes> &followers) {
    if (!isSymbolBelongTo(start_simpleExpression)) {
        listError(22);
        skipTo(start_simpleExpression, followers);
    }
    if (isSymbolBelongTo(start_simpleExpression)) {
        // TODO

        if (curToken->getCode() == TokenCodes::plus || curToken->getCode() == TokenCodes::minus) {
            scanNextToken();
        }

        auto symbols = unionOf(start_additive, followers);
        term(symbols);

        while (isSymbolBelongTo(start_additive)) {
            scanNextToken();
            term(symbols);
        }
    }
}

void Syntaxer::term(const set<TokenCodes> &followers) {
    if (!isSymbolBelongTo(start_term)) {
        listError(22);
        skipTo(start_term, followers);
    }
    if (isSymbolBelongTo(start_term)) {
        auto symbols = unionOf(start_multiplicative, followers);
        factor(symbols);

        while (isSymbolBelongTo(start_multiplicative)) {
            scanNextToken();
            factor(symbols);
        }
    }
}

void Syntaxer::factor(const set<TokenCodes> &followers) {
    if (!isSymbolBelongTo(start_factor)) {
        listError(22);
        skipTo(start_factor, followers);
    }
    if (isSymbolBelongTo(start_factor)) {
        switch (curToken->getCode()) {
            case leftpar: {
                accept(leftpar);
                auto symbols = unionOf(follow_factorExpression, followers);
                expression(symbols);
                accept(rightpar);
            } break;
            case notsy:
                accept(notsy);
                factor(followers);
                break;
            case intconst:
                accept(intconst);
                break;
            case floatconst:
                accept(floatconst);
                break;
            case charconst:
                accept(charconst);
                break;
            case stringconst:
                accept(stringconst);
                break;
            case nilsy:
                accept(nilsy);
                break;
            case ident:
                // todo
                accept(ident);
                break;
        }
    }
}

void Syntaxer::ifOperator(const set<TokenCodes> &followers) {
    if (!isSymbolBelongTo(start_ifOperator)) {
        listError(22);
        skipTo(start_ifOperator, followers);
    }
    if (isSymbolBelongTo(start_ifOperator)) {
        accept(ifsy);
        auto symbols = unionOf(follow_ifOperatorThen, followers);
        expression(symbols);
        accept(thensy);
        symbols = unionOf(follow_ifOperatorElse, followers);
        oper(symbols);
        if (curToken->getCode() == elsesy) {
            accept(elsesy);
            oper(symbols);
        }
    }
}

void Syntaxer::whileOperator(const set<TokenCodes> &followers) {
    if (!isSymbolBelongTo(start_whileOperator)) {
        listError(22);
        skipTo(start_whileOperator, followers);
    }
    if (isSymbolBelongTo(start_whileOperator)) {
        accept(whilesy);
        auto symbols = unionOf(follow_whileDo, followers);
        expression(symbols);
        accept(dosy);
        oper(followers);
    }
}

void Syntaxer::caseOperator(const set<TokenCodes> &followers) {
    if (!isSymbolBelongTo(start_caseOperator)) {
        listError(22);
        skipTo(start_caseOperator, followers);
    }
    if (isSymbolBelongTo(start_caseOperator)) {
        accept(casesy);
        auto symbols = unionOf(follow_caseOf, followers);
        expression(symbols);
        accept(ofsy);
        symbols = unionOf(follow_caseEnd, followers);
        elementOfVariants(symbols);

        while (curToken->getCode() == semicolon) {
            accept(semicolon);
            elementOfVariants(symbols);
        }

        accept(endsy);
    }
}

void Syntaxer::elementOfVariants(const set<TokenCodes> &followers) {
    if (!isSymbolBelongTo(start_elementOfVariants)) {
        listError(22);
        skipTo(start_elementOfVariants, followers);
    }
    if (isSymbolBelongTo(start_elementOfVariants)) {
        auto symbols = unionOf(follow_elementOfVariants, followers);
        listOfMarks(symbols);
        accept(colon);
        oper(followers);
    }
}

void Syntaxer::listOfMarks(const set<TokenCodes> &followers) {
    if (!isSymbolBelongTo(start_listOfMarks)) {
        listError(22);
        skipTo(start_listOfMarks, followers);
    }
    if (isSymbolBelongTo(start_listOfMarks)) {
        constant(followers);

        while (curToken->getCode() == comma) {
            accept(comma);
            constant(followers);
        }
    }
}

IoModule *Syntaxer::getIoModule() const {
    return ioModule;
}
