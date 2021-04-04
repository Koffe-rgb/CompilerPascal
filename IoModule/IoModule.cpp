#include "IoModule.h"

void IoModule::readLine() {
    if (codeSource.is_open()) {
        lineIdx++;
        getline(codeSource, curLine);
        if (codeSource.eof()) {
            codeSource.close();
        }
    } else {
        endOfFileReached = true;
    }
}

char IoModule::getChar() {
    char chr;
    if (charIdx < curLine.size()) {
        chr = curLine[charIdx++];
    } else {
        readLine();

        if (!endOfFileReached) {
            charIdx = 0;
            chr = '\n';
        } else {
            chr = '\0';
        }
    }

    return chr;
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

void IoModule::logError(int errCode, int len) {
    pair<int, int> pos = pair<int, int>(charIdx - len, lineIdx);
    pair<int, pair<int, int>> ecp = pair<int, pair<int, int>>(errCode, pos);
    errCodesAndPos.push_back(ecp);
}


const vector<pair<int, pair<int, int>>> &IoModule::getErrCodesAndPos() const {
    return errCodesAndPos;
}