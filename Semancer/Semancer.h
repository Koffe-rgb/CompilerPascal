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
    AbstractType* booleanType = nullptr;
    AbstractType* integerType = nullptr;
    AbstractType* realType = nullptr;
    AbstractType* charType = nullptr;
    AbstractType* stringType = nullptr;
    AbstractType* nilType = nullptr;

    explicit Semancer(IoModule* ioModule) {
        this->ioModule = ioModule;
        localScope = new Scope();
    };

    ~Semancer() {
        closeScopes(localScope);
    };

    Scope* openScope();
    void closeScopes(Scope* scope);
    void initGlobalScope();
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
