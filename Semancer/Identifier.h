#ifndef COMPILERPASCAL_IDENTIFIER_H
#define COMPILERPASCAL_IDENTIFIER_H

#pragma once
#include <string>

#include "Type.h"

using namespace std;

enum IdentClass {
    PROG_CLASS = 300,
    TYPE_CLASS,
    CONST_CLASS,
    VAR_CLASS,
    PROC_CLASS,
    FUNC_CLASS
};

class Identifier {
private:
    string identName;
    IdentClass identClass;
    AbstractType* type;
    bool is_const;
public:

    Identifier(string& identName, IdentClass identClass, AbstractType* type) {
        this->identClass = identClass;
        this->identName = identName;
        this->type = type;
        this->is_const = false;
    };

    Identifier(string& identName, IdentClass identClass, AbstractType* type, bool is_const) {
        this->identClass = identClass;
        this->identName = identName;
        this->type = type;
        this->is_const = is_const;
    };

    virtual ~Identifier() = default;


    const string &getIdentName() const {
        return identName;
    }

    IdentClass getIdentClass() const {
        return identClass;
    }

    AbstractType *getType() const {
        return type;
    }

    bool isConstant() const {
        return is_const;
    }

    void setType(AbstractType *type) {
        Identifier::type = type;
    }

    void setIsConst(bool isConst) {
        is_const = isConst;
    }
};


#endif //COMPILERPASCAL_IDENTIFIER_H
