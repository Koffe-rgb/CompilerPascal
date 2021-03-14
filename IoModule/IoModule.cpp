#include "IoModule.h"

void IoModule::readLine() {
    if (codeSource.is_open()) {
        lineIdx++;
        getline(codeSource, curLine);
        if (codeSource.eof()) {
            codeSource.close();
        }
    }
}

char IoModule::getChar() {
    char chr;
    if (charIdx < curLine.size()) {
        chr = curLine[charIdx++];
    } else {
        readLine();

        charIdx = 0;
        if (isOpen()) {
            chr = '\n';
        } else {
            chr = '\0';
        }
    }

    return chr;
}

bool IoModule::isOpen() {
    bool flag = true;
    if (!codeSource.is_open()) {
        flag = charIdx < curLine.size();
    }
    return flag;
}

char IoModule::peekChar(int offset) {
    return charIdx + offset < curLine.size() ?
           curLine[charIdx + offset] :
           '\n';
}

void IoModule::logError(int errCode) {
    pair<int, int> pos = pair<int, int>(charIdx, lineIdx);
    pair<int, pair<int, int>> ecp = pair<int, pair<int, int>>(errCode, pos);
    errCodesAndPos.push_back(ecp);
}

int IoModule::getLineIdx() const {
    return lineIdx;
}

int IoModule::getCharIdx() const {
    return charIdx;
}
