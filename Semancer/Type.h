#ifndef COMPILERPASCAL_TYPE_H
#define COMPILERPASCAL_TYPE_H

#pragma once
#include <string>
#include <vector>

using namespace std;

enum Types {
    UNKNOWN_TYPE,
    SCALAR_TYPE = 401,
    LIMITED_TYPE,
    ENUM_TYPE,
    ARRAY_TYPE,
    REFERENCE_TYPE,
    SET_TYPE,
    FILE_TYPE,
    RECORD_TYPE
};

class AbstractType {
protected:
    Types typeCode = UNKNOWN_TYPE;
public:
    Types getTypeCode() const {
        return typeCode;
    }
    virtual ~AbstractType() = default;
};

class ScalarType : public AbstractType {
public:
    ScalarType() {
        this->typeCode = SCALAR_TYPE;
    }
};

class EnumType : public AbstractType {
private:
    vector<string> symbols;
public:
    EnumType() {
        this->typeCode = ENUM_TYPE;
    }
    ~EnumType() override {
        symbols.clear();
    }
    void addSymbol(const string& symbol) {
        symbols.push_back(symbol);
    }
};


#endif //COMPILERPASCAL_TYPE_H
