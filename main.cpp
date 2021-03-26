#include <string>
#include <iostream>
#include "IoModule/IoModule.h"
#include "Lexer/Lexer.h"
#include "Syntaxer/Syntaxer.h"

using namespace std;

void test() {
    setlocale(LC_ALL, "Russian");
    string path = "../pascal.txt";

    auto* sntxr = new Syntaxer(path);

    sntxr->start();
    if (sntxr->hasErrors()) {
        sntxr->printErrors();
    } else {
        cout << "Ошибок не обнаружено\n";
    }

    delete sntxr;
}

int main() {
    test();
    return 0;
}