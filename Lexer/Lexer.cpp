#include "Lexer.h"

void toLowerCase(string& str) {
    transform(str.begin(), str.end(), str.begin(),
              [](unsigned char c) { return std::tolower(c); });
}

AbstractToken *Lexer::scanNextToken() {
    curChar = ioModule->getChar();

    while (curChar == ' ' || curChar == '\n') {
        curChar = ioModule->getChar();
    }

    AbstractToken* token;

    switch (curChar) {
        case '\'': token = scanStringConstant(); break;
        case '<': token = scanLater(); break;
        case '>': token = scanGreater(); break;
        case ':': token = scanColon(); break;
        case '.': token = scanPoint(); break;
        case '*': token = scanStar(); break;
        case '(': token = scanLeftPar(); break;
        case '{': token = scanFlpar(); break;
        case '}': token = scanFrpar(); break;
        case ')': token = new KeywordToken(TokenCodes::rightpar); break;
        case ';': token = new KeywordToken(TokenCodes::semicolon); break;
        case '/': token = new KeywordToken(TokenCodes::slash); break;
        case '=': token = new KeywordToken(TokenCodes::equal); break;
        case ',': token = new KeywordToken(TokenCodes::comma); break;
        case '^': token = new KeywordToken(TokenCodes::arrow); break;
        case '[': token = new KeywordToken(TokenCodes::lbracket); break;
        case ']': token = new KeywordToken(TokenCodes::rbracket); break;
        case '+': token = new KeywordToken(TokenCodes::plus); break;
        case '-': token = new KeywordToken(TokenCodes::minus); break;
        case '\0': token = new KeywordToken(TokenCodes::endoffile); break;
        default:

            if (isdigit(curChar)) {
                token = scanNumberConstant();
            }
            else if (isalpha(curChar) || curChar == '_') {
                token = scanName();
            }
            else {
                ioModule->logError(6); // ошибка - запрещенный символ
                token = scanNextToken();
            }

            break;
    }

    return token;
}

AbstractToken *Lexer::scanLater() {
    char nextCh = ioModule->peekChar();

    AbstractToken* token;

    switch (nextCh) {
        case '=':
            token = new KeywordToken(TokenCodes::laterequal);
            ioModule->getChar();
            break;

        case '>':
            token = new KeywordToken(TokenCodes::latergreater);
            ioModule->getChar();
            break;

        default:
            token = new KeywordToken(TokenCodes::later);
            break;
    }

    return token;
}

AbstractToken *Lexer::scanGreater() {
    char nextCh = ioModule->peekChar();

    AbstractToken* token;

    if (nextCh == '=') {
        token = new KeywordToken(TokenCodes::greaterequal);
        ioModule->getChar();
    }
    else {
        token = new KeywordToken(TokenCodes::greater);
    }

    return token;
}

AbstractToken *Lexer::scanColon() {
    char nextCh = ioModule->peekChar();

    AbstractToken* token;

    if (nextCh == '=') {
        token = new KeywordToken(TokenCodes::assign);
        ioModule->getChar();
    }
    else {
        token = new KeywordToken(TokenCodes::colon);
    }

    return token;
}

AbstractToken *Lexer::scanPoint() {
    char nextCh = ioModule->peekChar();

    AbstractToken* token;

    if (nextCh == '.') {
        token = new KeywordToken(TokenCodes::twopoints);
        ioModule->getChar();
    }
    else {
        token = new KeywordToken(TokenCodes::point);
    }

    return token;
}

AbstractToken *Lexer::scanLeftPar() {
    char nextCh = ioModule->peekChar();

    AbstractToken* token;

    if (nextCh == '*') {
        char prev = curChar;
        curChar = ioModule->getChar();

        // пропуск коммента
        while ((prev != '*' || curChar != ')') && curChar != '\0') {
            prev = curChar;
            curChar = ioModule->getChar();
        }

        if (prev == '*' && curChar == ')') {
            token = scanNextToken();
        }
        else {
            ioModule->logError(86);		// коммент не закрыт
            token = new KeywordToken(TokenCodes::endoffile);
        }
    }
    else {
        token = new KeywordToken(TokenCodes::leftpar);
    }

    return token;
}

AbstractToken *Lexer::scanStar() {
    char nextCh = ioModule->peekChar();

    AbstractToken* token;

    if (nextCh == ')') {
        curChar = ioModule->getChar();
        ioModule->logError(85); // коммент не открыт
        token = new KeywordToken(TokenCodes::rcomment);
    }
    else {
        token = new KeywordToken(TokenCodes::star);
    }

    return token;
}

AbstractToken *Lexer::scanFlpar() {
    char nextCh = ioModule->peekChar();

    AbstractToken* token;

    while (curChar != '}' && curChar != '\0') {
        curChar = ioModule->getChar();
    }

    if (curChar == '}') {
        token = scanNextToken();
    }
    else {
        ioModule->logError(86);	// коммент не закрыт
        token = new KeywordToken(TokenCodes::endoffile);
    }

    return token;
}

AbstractToken *Lexer::scanFrpar() {
    ioModule->logError(85); // коммент не открыт
    return new KeywordToken(TokenCodes::frpar);
}

AbstractToken *Lexer::scanNumberConstant() {

    // ------------------INTEGER------------------
    int intConst = curChar - '0';
    bool isIntError = false;

    char nextChar = ioModule->peekChar();
    while (isdigit(nextChar)) {
        curChar = ioModule->getChar();
        int digit = curChar - '0';

        if (!isIntError && (intConst < MAX_INT / 10 ||
                            intConst < MAX_INT / 10 && digit <= MAX_INT % 10))
        {
            intConst = 10 * intConst + digit;
        }
        else {
            isIntError = true;
        }
        nextChar = ioModule->peekChar();
    }

    if (nextChar != '.') {
        if (isIntError) {
            ioModule->logError(203);	// переполнение int
        }
        auto* ic = new IntConstant(intConst);
        return new ConstantToken(ic, TokenCodes::intconst);
    }

    nextChar = ioModule->peekChar(1);
    if (!isdigit(nextChar)) {
        if (isalpha(nextChar)) {
            ioModule->logError(201);
        }
        auto* ic = new IntConstant(intConst);
        return new ConstantToken(ic, TokenCodes::intconst);
    }


    // ------------------FLOAT------------------
    ioModule->getChar();	// пропуск точки
    nextChar = ioModule->peekChar();

    if (!isdigit(nextChar)) {
        ioModule->logError(201); // должна идти цифра
        auto* fc = new FloatConstant(intConst);
        return new ConstantToken(fc, TokenCodes::floatconst);
    }

    int floatPartConst = 0;
    int radix = 1;
    bool isFloatError = false;

    while (isdigit(nextChar)) {
        curChar = ioModule->getChar();
        int digit = curChar - '0';

        if (!isFloatError && (floatPartConst < MAX_INT / 10 ||
                              floatPartConst < MAX_INT / 10 && digit <= MAX_INT % 10))
        {
            floatPartConst = 10 * floatPartConst + digit;
            radix *= 10;
        }
        else {
            isFloatError = true;
        }
        nextChar = ioModule->peekChar();
    }

    if (isIntError || isFloatError) {
        ioModule->logError(207);
    }

    auto* fc = new FloatConstant(intConst + (floatPartConst / (float)radix));
    return new ConstantToken(fc, TokenCodes::floatconst);
}

AbstractToken *Lexer::scanStringConstant() {
    // -----------------CHAR-----------------
    char charConst = ioModule->getChar();
    if (charConst == '\'' || charConst == '\n') {
        ioModule->logError(75); // ошибка в символьной константе

        auto* cc = new CharConstant(charConst);
        return new ConstantToken(cc, TokenCodes::charconst);
    }

    curChar = ioModule->getChar();
    if (curChar == '\'') {
        auto* cc = new CharConstant(charConst);
        return new ConstantToken(cc, TokenCodes::charconst);
    }

    if (curChar == '\n') {
        ioModule->logError(75); // ошибка в символьной константе

        auto* cc = new CharConstant(charConst);
        return new ConstantToken(cc, TokenCodes::charconst);
    }

    // -----------------STRING-----------------
    string strConst(1, charConst);
    int len = 1;
    bool isStrError = false;

    while (curChar != '\'') {
        strConst += curChar;
        len++;

        if (len > LEN_MAX) {
            isStrError = true;
        }

        curChar = ioModule->getChar();
        if (curChar == '\n') {
            ioModule->logError(75); // ошибка в символьной константе

            auto* sc = new StringConstant(strConst);
            return new ConstantToken(sc, TokenCodes::stringconst);
        }
    }

    if (isStrError) {
        ioModule->logError(76); // слишком длинная строковая константа
    }

    // TODO возможно нужно перевести указатель на след символ

    auto* sc = new StringConstant(strConst);
    return new ConstantToken(sc, TokenCodes::stringconst);
}

AbstractToken *Lexer::scanName() {
    int len = 1;
    string name(1, curChar);

    char nextChar = ioModule->peekChar();
    while ((isalpha(nextChar) || isdigit(nextChar) || nextChar == '_')
           && len <= LEN_MAX)
    {
        name += ioModule->getChar();
        len++;
        nextChar = ioModule->peekChar();
    }

    toLowerCase(name);
    if (KeywordsMap.count(name) == 1) {
        TokenCodes code = KeywordsMap.at(name);
        return new KeywordToken(code);
    }
    else {
        return new IdentifierToken(name);
    }
}

IoModule* Lexer::getIoModule() const {
    return ioModule;
}


