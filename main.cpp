#include <string>
#include "IoModule/IoModule.h"
#include "Lexer/Lexer.h"

using namespace std;

const string path = "../pascal.txt";

void testLexer() {
    auto* io = new IoModule(path);
    auto* lexer = new Lexer(io);

    while (io->isOpen()) {
        cout << lexer->scanNextToken()->toString() << endl;
    }

    for (auto err : io->errCodesAndPos) {
        auto pos = err.second;
        cout << "Error: code=" << err.first << ", pos={ " << pos.second << ", " << pos.first << " }" << endl;
    }

    delete lexer;
}

int main() {
    testLexer();
    return 0;
}