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
    semancer->openScope();
    semancer->initGlobalScope();

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
        string identName = ((IdentifierToken*)curToken)->getIdentName();

        auto identifier = new Identifier(identName, CONST_CLASS, nullptr, true);

        accept(ident);
        accept(TokenCodes::equal);
        auto type = constant(followers);
        identifier->setType(type);

        if (semancer->getLocalScope()->getIdentifiers().contains(identName))
            listError(101);
        else
            semancer->getLocalScope()->addIdentifier(identifier);
    }
}

AbstractType* Syntaxer::constant(const set<TokenCodes> &followers) {
    AbstractType* type = nullptr;
    Scope* scope;
    Identifier* identifier;
    string name;

    if (!isSymbolBelongTo(start_constant)) {
        listError(18);
        skipTo(start_constant, followers);
    }
    if (isSymbolBelongTo(start_constant)) {
        switch (curToken->getCode()) {
            case intconst:
                type = semancer->integerType;
                lastIntegerValue = ((IntConstant*)((ConstantToken*)curToken)->getConstant())->getValue();

                accept(intconst);
                break;
            case floatconst:
                type = semancer->realType;
                lastRealValue = ((FloatConstant*)((ConstantToken*)curToken)->getConstant())->getValue();

                accept(floatconst);
                break;
            case stringconst:
                type = semancer->charType;
                lastStringValue = ((StringConstant*)((ConstantToken*)curToken)->getConstant())->getValue();

                accept(stringconst);
                break;
            case charconst:
                type = semancer->charType;
                lastCharValue = ((CharConstant*)((ConstantToken*)curToken)->getConstant())->getValue();

                accept(charconst);
                break;
            case ident:
                scope = semancer->getLocalScope();
                name = ((IdentifierToken*)curToken)->getIdentName();
                identifier = semancer->searchIdentifier(scope, name);

                if (identifier == nullptr)
                    listError(104);
                else {
                    type = identifier->getType();
                }

                accept(ident);
                break;
            default:
                if (curToken->getCode() == TokenCodes::plus ||
                    curToken->getCode() == TokenCodes::minus)
                {
                    scanNextToken();
                    auto code = curToken->getCode();
                    switch (code) {
                        case intconst:
                            type = semancer->integerType;
                            break;
                        case floatconst:
                            type = semancer->realType;
                            break;
                        case ident:
                            scope = semancer->getLocalScope();
                            name = ((IdentifierToken*)curToken)->getIdentName();
                            identifier = semancer->searchIdentifier(scope, name);

                            if (identifier == nullptr)
                                listError(104);
                            else {
                                type = identifier->getType();
                            }
                            break;
                    }
                    scanNextToken();
                }
                break;
        }
    }
    return type;
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
        string identName = ((IdentifierToken*)curToken)->getIdentName();
        auto identifier = new Identifier(identName, TYPE_CLASS, nullptr);

        accept(ident);
        accept(TokenCodes::equal);
        auto t = type(followers);

        identifier->setType(t);
        semancer->getLocalScope()->addIdentifier(identifier);
    }
}

AbstractType* Syntaxer::type(const set<TokenCodes> &followers) {
    AbstractType* t = nullptr;
    if (!isSymbolBelongTo(start_type)) {
        listError(10);
        skipTo(start_type, followers);
    }
    if (isSymbolBelongTo(start_type)) {
        if (curToken->getCode() == arrow) {
            t = referenceType(followers);
        }
        else {
            t = simpleType(followers);
        }
    }
    return t;
}

AbstractType* Syntaxer::simpleType(const set<TokenCodes> &followers) {
    AbstractType* type = nullptr;
    if (!isSymbolBelongTo(start_simpleType)) {
        listError(10);
        skipTo(start_simpleType, followers);
    }
    if (isSymbolBelongTo(start_simpleType)) {
        if (curToken->getCode() == ident) {
            string name = ((IdentifierToken*)curToken)->getIdentName();
            type = semancer->searchType(semancer->getLocalScope(), name);
            if (type == nullptr) {
                auto identifier = semancer->searchIdentifier(semancer->getLocalScope(), name);
                if (identifier == nullptr) {
                    listError(104);

                    // TODO ?????????
                    accept(ident);
                }
            }

            accept(ident);
        }
    }
    return type;
}

AbstractType* Syntaxer::referenceType(const set<TokenCodes> &followers) {
    // TODO REFERENCE TYPE
    AbstractType* type = nullptr;
    if (!isSymbolBelongTo(start_linkType)) {
        listError(22);
        skipTo(start_linkType, followers);
    }
    if (isSymbolBelongTo(start_linkType)) {
        accept(arrow);
        accept(ident);
    }
    return type;
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

void insertVarTo(vector<Identifier*>& variables, AbstractToken* token) {
    string name = ((IdentifierToken*)token)->getIdentName();
    auto identifier = new Identifier(name, VAR_CLASS, nullptr);
    variables.push_back(identifier);
}

void Syntaxer::varDeclaration(const set<TokenCodes> &followers) {
    if (!isSymbolBelongTo(start_varDeclaration)) {
        listError(2);
        skipTo(start_varDeclaration, followers);
    }
    if (isSymbolBelongTo(start_varDeclaration)) {
        vector<Identifier*> variables;
        insertVarTo(variables, curToken);

        accept(ident);

        while (curToken->getCode() == comma) {
            accept(comma);
            insertVarTo(variables, curToken);
            accept(ident);
        }
        accept(colon);
        auto t = type(followers);

        for (auto identifier : variables) {
            identifier->setType(t);
            if (semancer->getLocalScope()->getIdentifiers().contains(identifier->getIdentName()))
                listError(101);
            else
                semancer->getLocalScope()->addIdentifier(identifier);
        }
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
        string varName = ((IdentifierToken*)curToken)->getIdentName();

        auto symbols = unionOf(follow_assignmentOperator, followers);
        auto varType = variable(symbols);

        accept(assign);
        auto exprType = expression(followers);

        if (!semancer->checkAssignmentTypes(varType, exprType))
            listError(328);
    }
}

AbstractType* Syntaxer::variable(const set<TokenCodes> &followers) {
    AbstractType* type = nullptr;
    if (!isSymbolBelongTo(start_variable)) {
        listError(22);
        skipTo(start_variable, followers);
    }
    if (isSymbolBelongTo(start_variable)) {
        string name = ((IdentifierToken*)curToken)->getIdentName();
        auto identifier = semancer->getLocalScope()->retrieveIdentifier(name);
        if (identifier == nullptr)
            listError(104);
        else
            type = identifier->getType();

        accept(ident);

        if (curToken->getCode() == arrow) {
            accept(arrow);
        }
    }
    return type;
}

AbstractType* Syntaxer::expression(const set<TokenCodes> &followers) {
    AbstractType* type = nullptr;
    if (!isSymbolBelongTo(start_expression)) {
        listError(23);
        skipTo(start_expression, followers);
    }
    if (isSymbolBelongTo(start_expression)) {
        auto symbols = unionOf(follow_simpleExpression, followers);
        type = simpleExpression(symbols);

        auto operationCode = curToken->getCode();
        if (operationCode == TokenCodes::equal || operationCode == latergreater ||
            operationCode == later || operationCode == laterequal ||
            operationCode == greaterequal || operationCode == TokenCodes::greater)
        {
            scanNextToken();
            auto sndType = simpleExpression(followers);
            type = semancer->checkRelationOperation(type, sndType);
            if (type == nullptr)
                listError(186);
        }
    }
    return type;
}

AbstractType* Syntaxer::simpleExpression(const set<TokenCodes> &followers) {
    AbstractType* type = nullptr;
    if (!isSymbolBelongTo(start_simpleExpression)) {
        listError(22);
        skipTo(start_simpleExpression, followers);
    }
    if (isSymbolBelongTo(start_simpleExpression)) {
        isNeedConvert = false;
        wasFirst = false;
        bool firstTermHasSign = false;

        if (curToken->getCode() == TokenCodes::plus || curToken->getCode() == TokenCodes::minus) {
            scanNextToken();
            firstTermHasSign = true;
        }

        auto symbols = unionOf(start_additive, followers);
        type = term(symbols);

        if (firstTermHasSign)
            semancer->checkRightSign(type);

        while (isSymbolBelongTo(start_additive)) {
            auto operationCode = curToken->getCode();
            scanNextToken();
            auto sndType = term(symbols);
            type = semancer->checkAdditive(type, sndType, operationCode, curToken->toString().size());
        }
    }
    return type;
}

AbstractType* Syntaxer::term(const set<TokenCodes> &followers) {
    AbstractType* type = nullptr;
    if (!isSymbolBelongTo(start_term)) {
        listError(22);
        skipTo(start_term, followers);
    }
    if (isSymbolBelongTo(start_term)) {
        auto symbols = unionOf(start_multiplicative, followers);
        type = factor(symbols);
        wasFirst = true;

        while (isSymbolBelongTo(start_multiplicative)) {
            auto operationCode = curToken->getCode();
            scanNextToken();
            auto sndType = factor(symbols);
            type = semancer->checkMultiplicative(type, sndType, operationCode, curToken->toString().size());
        }
    }
    return type;
}

AbstractType* Syntaxer::factor(const set<TokenCodes> &followers) {
    AbstractType* t = nullptr;
    if (!isSymbolBelongTo(start_factor)) {
        listError(22);
        skipTo(start_factor, followers);
    }
    if (isSymbolBelongTo(start_factor)) {
        switch (curToken->getCode()) {
            case leftpar: {
                accept(leftpar);
                auto symbols = unionOf(follow_factorExpression, followers);
                t = expression(symbols);
                accept(rightpar);
            } break;
            case notsy:
                accept(notsy);
                t = factor(followers);
                t = semancer->checkBoolean(t);
                if (t == nullptr)
                    listError(210);
                break;
            case intconst:
                t = semancer->integerType;
                accept(intconst);
                break;
            case floatconst:
                t = semancer->realType;
                accept(floatconst);
                break;
            case charconst:
                t = semancer->charType;
                accept(charconst);
                break;
            case stringconst:
                t = semancer->charType;
                accept(stringconst);
                break;
            case nilsy:
                t = semancer->nilType;
                accept(nilsy);
                break;
            case ident:
                string name = curToken->toString();
                auto identifier = semancer->searchIdentifier(semancer->getLocalScope(), name);
                if (identifier != nullptr) {
                    switch (identifier->getIdentClass()) {
                        case VAR_CLASS:
                            t = variable(followers);
                            break;
                        case CONST_CLASS:
                            t = identifier->getType();
                            accept(ident);
                            break;
                        case TYPE_CLASS:
                            // TODO ????
                            t = type(followers);
                            break;
                    }
                }
                else {
                    identifier = new Identifier(name, VAR_CLASS, nullptr);
                    if (semancer->getLocalScope()->getIdentifiers().contains(name))
                        listError(101);
                    else
                        semancer->getLocalScope()->addIdentifier(identifier);
                    listError(104);
                    accept(ident);
                }
                break;
        }
    }
    return t;
}

void Syntaxer::ifOperator(const set<TokenCodes> &followers) {
    if (!isSymbolBelongTo(start_ifOperator)) {
        listError(22);
        skipTo(start_ifOperator, followers);
    }
    if (isSymbolBelongTo(start_ifOperator)) {
        accept(ifsy);
        auto symbols = unionOf(follow_ifOperatorThen, followers);
        auto type = expression(symbols);
        if (type == nullptr)
            listError(328);

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
        auto type = expression(symbols);
        if (type == nullptr)
            listError(328);

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
        // TODO experimental
        lastCaseType = expression(symbols);
        if (lastCaseType == nullptr)
            listError(328);

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
        auto type = constant(followers);
        if (type == nullptr || type != lastCaseType)
            listError(328);

        while (curToken->getCode() == comma) {
            accept(comma);
            constant(followers);
        }
    }
}

IoModule *Syntaxer::getIoModule() const {
    return ioModule;
}
