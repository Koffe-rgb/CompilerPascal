#include "Semancer.h"

Scope *Semancer::openScope() {
    auto scope = new Scope(localScope);
    localScope = scope;
    return scope;
}

Scope *Semancer::initGlobalScope() {
    this->booleanType = localScope->addType(ENUM_TYPE);
    string booleanName = "boolean";
    auto booleanIdent = new Identifier(booleanName, TYPE_CLASS, booleanType);
    localScope->addIdentifier(booleanIdent);

    string falseName = "false";
    auto falseIdent = new Identifier(falseName, CONST_CLASS, booleanType);
    localScope->addIdentifier(falseIdent);
    ((EnumType*)booleanType)->addSymbol(falseName);

    string trueName = "true";
    auto trueIdent = new Identifier(trueName, CONST_CLASS, booleanType);
    localScope->addIdentifier(trueIdent);
    ((EnumType*)booleanType)->addSymbol(trueName);


    this->integerType = localScope->addType(SCALAR_TYPE);
    string integerName = "integer";
    auto integerIdent = new Identifier(integerName, TYPE_CLASS, integerType);
    localScope->addIdentifier(integerIdent);

    this->realType = localScope->addType(SCALAR_TYPE);
    string realName = "real";
    auto readIdent = new Identifier(realName, TYPE_CLASS, realType);
    localScope->addIdentifier(readIdent);

    this->charType = localScope->addType(SCALAR_TYPE);
    string charName = "char";
    auto charIdent = new Identifier(charName, TYPE_CLASS, charType);
    localScope->addIdentifier(charIdent);

    this->nilType = localScope->addType(SCALAR_TYPE);
    string nilName = "nil";
    auto nilIdent = new Identifier(nilName, TYPE_CLASS, nilType);
    localScope->addIdentifier(nilIdent);
}


void Semancer::closeScope() {
    auto idents = localScope->getIdentifiers();
    for (const auto& ident :idents) {
        delete ident.second;
    }
    idents.clear();

    for (auto type : localScope->getTypes()) {
        delete type;
    }

    localScope = localScope->getOuterScope();
}

Identifier *Semancer::searchIdentifier(Scope *scope, string &identName) {
    auto ident = scope->retrieveIdentifier(identName);
    if (ident == nullptr && scope->getOuterScope() != nullptr)
        return searchIdentifier(scope->getOuterScope(), identName);
    return nullptr;
}

AbstractType *Semancer::searchType(Scope *scope, string &name) {
    auto ident = scope->retrieveIdentifier(name);

    if (ident != nullptr && (ident->getIdentClass() == TYPE_CLASS ||
        ident->getIdentClass() == VAR_CLASS))
    {
        return ident->getType();
    }
    if (scope->getOuterScope() != nullptr)
        return searchType(scope->getOuterScope(), name);

    return nullptr;
}

bool Semancer::checkAssignmentTypes(AbstractType *varType, AbstractType *exprType) const {
    if (varType == nullptr || exprType == nullptr)
        return false;
    if (varType == realType && (exprType == realType || exprType == integerType))
        return true;
    if (varType == exprType)
        return true;
    return false;
}

AbstractType* Semancer::checkRelationOperation(AbstractType *fstType, AbstractType *sndType) const {
    if (fstType == integerType && sndType == realType
        || fstType == realType && sndType == integerType
        || fstType == sndType)
    {
        return booleanType;
    }
    return nullptr;
}

void Semancer::checkRightSign(AbstractType *type) {
    if (type == nullptr || type == integerType || type == realType)
        return;
    ioModule->logError(211);
}

AbstractType *Semancer::checkAdditive(AbstractType *fstType, AbstractType *sndType, TokenCodes operation, int len) {
    if (operation == TokenCodes::plus || operation == TokenCodes::minus) {
        if ((fstType == integerType || fstType == realType)
            && (sndType == integerType || sndType == realType))
        {
            return fstType == realType
                    ? realType
                    : sndType == realType
                        ? realType
                        : integerType;
        }
        ioModule->logError(211, len);
    }
    if (operation == orsy) {
        if (fstType == booleanType && sndType == booleanType)
            return booleanType;
        ioModule->logError(210, len);
    }
    return nullptr;
}

AbstractType *Semancer::checkMultiplicative(AbstractType *fstType, AbstractType *sndType, TokenCodes operation, int len) {
    if (operation == divsy || operation == modsy) {
        if (fstType == integerType && sndType == integerType)
            return integerType;
        ioModule->logError(212);
    }
    if (operation == slash || operation == star) {
        if ((fstType == integerType || fstType == realType)
            && (sndType == integerType || sndType == realType))
        {
            return fstType == realType
                    ? realType
                    : sndType == realType
                        ? realType
                        : integerType;
        }
        if (operation == slash) ioModule->logError(214);
        if (operation == star) ioModule->logError(213);
    }
    if (operation == andsy) {
        if (fstType == booleanType && sndType == booleanType)
            return booleanType;
        ioModule->logError(210, len);
    }
    return nullptr;
}

AbstractType *Semancer::checkBoolean(AbstractType *type) const {
    return type == booleanType ? booleanType : nullptr;
}

Scope *Semancer::getLocalScope() const {
    return localScope;
}



