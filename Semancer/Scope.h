#ifndef COMPILERPASCAL_SCOPE_H
#define COMPILERPASCAL_SCOPE_H

#pragma once
#include <map>
#include <vector>
#include <string>

#include "Identifier.h"
#include "Type.h"



using namespace std;

class Scope {
private:
    map<string, Identifier*> identifiers;
    vector<AbstractType*> types;
    Scope* outerScope;

public:
    explicit Scope(Scope* outerScope = nullptr) {
        this->outerScope = outerScope;
    };
    ~Scope();

    AbstractType* addType(Types type);
    bool addIdentifier(Identifier* identifier);
    Identifier* retrieveIdentifier(string& identName);

    const map<string, Identifier *> &getIdentifiers() const;

    const vector<AbstractType *> &getTypes() const;

    Scope *getOuterScope() const;
};


#endif //COMPILERPASCAL_SCOPE_H
