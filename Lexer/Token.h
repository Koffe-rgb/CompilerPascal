#ifndef COMPILERPASCAL_TOKEN_H
#define COMPILERPASCAL_TOKEN_H

#pragma once
#include <string>
#include <utility>
#include "Codes.h"
#include "Constants.h"

using namespace std;

class AbstractToken {
public:
    enum class TokenTypes {
        IDENTIFIER,
        CONSTANT,
        KEYWORD
    };

protected:
    TokenTypes type;
    TokenCodes code;

public:
    AbstractToken(TokenTypes type, TokenCodes code) {
        this -> type = type;
        this -> code = code;
    }
    TokenTypes getType() { return this->type; }
    TokenCodes getCode() { return this->code; }

    virtual string toString() {
        return toStringMap.at(code);
    }

    virtual ~AbstractToken() = default;;
};


class IdentifierToken : public AbstractToken {
private:
    string identName;

public:
    explicit IdentifierToken(string identName) : AbstractToken(TokenTypes::IDENTIFIER, TokenCodes::ident)
    {
        this -> identName = std::move(identName);
    }

    string getIdentName() { return this -> identName; }

    string toString() override {
        return identName;
    }

    ~IdentifierToken() override = default;;
};


class ConstantToken : public AbstractToken {
private:
    AbstractConstant* constant;

public:
    ConstantToken(AbstractConstant* constant, TokenCodes code) : AbstractToken(TokenTypes::CONSTANT, code)
    {
        this -> constant = constant;
    }

    AbstractConstant* getConstant() {
        return this -> constant;
    }

    string toString() override {
        return constant->toString();
    }

    ~ConstantToken() override {
        delete constant;
    }
};


class KeywordToken : public AbstractToken {

public:
    explicit KeywordToken(TokenCodes tokenCode) : AbstractToken(TokenTypes::KEYWORD, tokenCode)
    {
    }

    ~KeywordToken() override = default;
};

#endif //COMPILERPASCAL_TOKEN_H
