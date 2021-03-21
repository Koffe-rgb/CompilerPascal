#include <string>
#include <iostream>
#include "IoModule/IoModule.h"
#include "Lexer/Lexer.h"
#include "Syntaxer/Syntaxer.h"

using namespace std;

const string path = "../pascal.txt";

void testLexer() {
    setlocale(LC_ALL, "Russian");

    auto* io = new IoModule(path);
    auto* lex = new Lexer(io);
    auto* sntxr = new Syntaxer(lex);

    sntxr->start();
    for (auto err : io->getErrCodesAndPos()) {
        auto pos = err.second;
        const auto& a = ErrorTable.at(err.first);
        printf("Строка %d, позиция %d, (код %d): %s\n", pos.second, pos.first, err.first, a.c_str());
    }
}

int main() {
    testLexer();
    return 0;
}