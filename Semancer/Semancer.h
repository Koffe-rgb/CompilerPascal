#ifndef COMPILERPASCAL_SEMANCER_H
#define COMPILERPASCAL_SEMANCER_H

#pragma once
#include "Scope.h"
#include "../Lexer/Codes.h"
#include "../IoModule/IoModule.h"

class Semancer {
private:
    Scope* localScope;
    IoModule* ioModule;

public:
    AbstractType* booleanType;
    AbstractType* integerType;
    AbstractType* realType;
    AbstractType* charType;
    AbstractType* nilType;

    Semancer(IoModule* ioModule) {
        this->ioModule = ioModule;
    };

    ~Semancer() = default;

    Scope* openScope();
    void closeScope();
    Scope* initGlobalScope();
    Identifier* searchIdentifier(Scope* scope, string& identName);
    AbstractType* searchType(Scope* scope, string& name);
    bool checkAssignmentTypes(AbstractType* varType, AbstractType* exprType) const;
    AbstractType* checkRelationOperation(AbstractType* fstType, AbstractType* sndType) const;
    void checkRightSign(AbstractType* type);
    AbstractType* checkAdditive(AbstractType* fstType, AbstractType* sndType, TokenCodes operation, int len);
    AbstractType* checkMultiplicative(AbstractType* fstType, AbstractType* sndType, TokenCodes operation, int len);
    AbstractType* checkBoolean(AbstractType* type) const;

    Scope *getLocalScope() const;
};


#endif //COMPILERPASCAL_SEMANCER_H
