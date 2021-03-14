#ifndef COMPILERPASCAL_IOMODULE_H
#define COMPILERPASCAL_IOMODULE_H
#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

class IoModule {
private:
    int lineIdx;			// номер текущей строки
    int charIdx;			// номер текущей литеры
    ifstream codeSource;	// поток ввода
    string curLine;			// текущая строка


private:
    void readLine();		// прочитать следующую строку в curLine

public:
    vector<pair<int, pair<int, int>>> errCodesAndPos; // список возникших ошибок

    IoModule(const string& filePath) {
        lineIdx = 0;
        charIdx = 0;
        curLine = "";
        codeSource.open(filePath, ios::in);
    }

    virtual ~IoModule() = default;

    int getLineIdx() const;

    int getCharIdx() const;

    bool isOpen();	// проверяет открыт ли файл и прочитана ли последгяя строка до конца

    char peekChar(int offset = 0);	// посмотреть на n-ную литеру, от текущей, без изменения charIdx

    char getChar();	// получить текущую литеру и изменить charIdx, и lineIdx, если требуется

    void logError(int errCode);	// записать в лог информацию об ошибке, по коду

};


#endif //COMPILERPASCAL_IOMODULE_H
