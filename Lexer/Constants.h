#ifndef COMPILERPASCAL_CONSTANTS_H
#define COMPILERPASCAL_CONSTANTS_H

#pragma once
#include <string>
#include <utility>

using namespace std;

class AbstractConstant {
public:
    enum class ConstTypes {
        INT,
        FLOAT,
        CHAR,
        STRING
    };

protected:
    ConstTypes type;

public:
    explicit AbstractConstant(ConstTypes type) { this -> type = type; }
    ConstTypes getType() { return this -> type; }
    virtual ~AbstractConstant() = default;;
    virtual string toString() = 0;
};



class IntConstant : public AbstractConstant {
private:
    int value;

public:
    explicit IntConstant(int value) : AbstractConstant(ConstTypes::INT) {
        this -> value = value;
    }
    int getValue() const { return this -> value; }
    ~IntConstant() override = default;;
    string toString() override {
        return to_string(value);
    }
};



class FloatConstant : public AbstractConstant {
private:
    float value;

public:
    explicit FloatConstant(float value) : AbstractConstant(ConstTypes::FLOAT) {
        this -> value = value;
    }
    float getValue() const { return this -> value; }
    ~FloatConstant() override = default;;
    string toString() override {
        return to_string(value);
    }
};



class CharConstant : public AbstractConstant {
private:
    char value;

public:
    explicit CharConstant(char value) : AbstractConstant(ConstTypes::CHAR) {
        this -> value = value;
    }
    char getValue() const { return this -> value; }
    ~CharConstant() override = default;;
    string toString() override {
        return string(1, value);
    }
};



class StringConstant : public AbstractConstant {
private:
    string value;

public:
    explicit StringConstant(string value) : AbstractConstant(ConstTypes::STRING) {
        this -> value = std::move(value);
    }
    string getValue() { return this -> value; }
    ~StringConstant() override = default;;
    string toString() override {
        return value;
    }
};

#endif //COMPILERPASCAL_CONSTANTS_H
