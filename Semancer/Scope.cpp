#include "Scope.h"

AbstractType *Scope::addType(Types type) {
    AbstractType* newType = nullptr;
    switch (type) {
        case UNKNOWN_TYPE: break;
        case SCALAR_TYPE:
            newType = new ScalarType();
            types.push_back(newType);
            break;
        case ENUM_TYPE:
            newType = new EnumType();
            types.push_back(newType);
            break;
        default: break;
    }
    return newType;
}

bool Scope::addIdentifier(Identifier* identifier) {
    string name = identifier->getIdentName();
    bool contains = identifiers.contains(identifier->getIdentName());

    if (!contains) {
        identifiers[identifier->getIdentName()] = identifier;
        return true;
    }
    return false;
}

Identifier *Scope::retrieveIdentifier(string& identName) {
    if (identifiers.contains(identName)) {
        return identifiers[identName];
    }
    return nullptr;
}

const map<string, Identifier *> &Scope::getIdentifiers() const {
    return identifiers;
}

const vector<AbstractType *> &Scope::getTypes() const {
    return types;
}

Scope *Scope::getOuterScope() const {
    return outerScope;
}

Scope::~Scope() {
    for (const auto& ident : identifiers) {
        delete ident.second;
    }
    identifiers.clear();

    for (auto & type : types) {
        delete type;
        type = nullptr;
    }
    types.clear();

    delete outerScope;
}


