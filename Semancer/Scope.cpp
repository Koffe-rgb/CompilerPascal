#include "Scope.h"

AbstractType *Scope::addType(Types type) {
    AbstractType* newType;
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
    bool is_ident_unique = identifiers.contains(identifier->getIdentName());

    if (is_ident_unique) {
        identifiers[identifier->getIdentName()] = identifier;
    }
    return is_ident_unique;
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


