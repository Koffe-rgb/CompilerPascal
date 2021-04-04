#include <string>
#include <iostream>
#include "IoModule/IoModule.h"
#include "Lexer/Lexer.h"
#include "Syntaxer/Syntaxer.h"

using namespace std;

void test() {
    setlocale(LC_ALL, "Russian");
    string path = "../pascal.txt";

    auto* compiler = new Syntaxer(path);

    compiler->start();
    if (compiler->hasErrors()) {
        compiler->printErrors();
    } else {
        cout << "Ошибок не обнаружено\n";
    }

    delete compiler;
}

int main() {
    test();
    return 0;
}