#ifndef COMPILERPASCAL_CODES_H
#define COMPILERPASCAL_CODES_H

#pragma once
#include <map>
#include <string>

using namespace std;


// перечисление кодов символов
enum TokenCodes {
    star = 21,		/* * */
    slash = 60,		/* / */
    equal = 16,		/* = */
    comma = 20,		/* , */
    semicolon = 14,	/* ; */
    colon = 5,		/* : */
    point = 61,		/* . */
    arrow = 62,		/* ^ */
    leftpar = 9,	/* ( */
    rightpar = 4,	/* ) */
    lbracket = 11,	/* [ */
    rbracket = 12,	/* ] */
    flpar = 63,		/* { */
    frpar = 64,		/* } */
    later = 65,		/* < */
    greater = 66,	/* > */
    laterequal = 67,	/* <= */
    greaterequal = 68,	/* >= */
    latergreater = 69,	/* <> */
    plus = 70,		/* + */
    minus = 71,		/* - */
    lcomment = 72,	/* (* */
    rcomment = 73,	/* *) */
    assign = 51,	/* := */
    twopoints = 74,	/* .. */
    ident = 2,
    intconst = 15,
    floatconst = 82,
    charconst = 83,
    stringconst = 84,
    endofline = 254, /* \n */
    endoffile = 253,  /* EOF */

    dosy = 54,
    ifsy = 56,
    insy = 22,
    ofsy = 8,
    orsy = 23,
    tosy = 55,

    andsy = 24,
    divsy = 25,
    endsy = 13,
    forsy = 26,
    modsy = 27,
    nilsy = 89,
    notsy = 28,
    setsy = 29,
    varsy = 30,

    casesy = 31,
    elsesy = 32,
    filesy = 57,
    gotosy = 33,
    onlysy = 90,
    thensy = 52,
    typesy = 34,
    unitsy = 35,
    usessy = 36,
    withsy = 37,

    arraysy = 38,
    beginsy = 17,
    constsy = 39,
    labelsy = 40,
    untilsy = 53,
    whilesy = 41,

    downtosy = 55,
    exportsy = 91,
    importsy = 92,
    modulesy = 93,
    packedsy = 42,
    recordsy = 43,
    repeatsy = 44,
    vectorsy = 45,
    stringsy = 46,

    forwardsy = 47,
    processsy = 48,
    programsy = 3,
    segmentsy = 49,

    functionsy = 77,
    separatesy = 78,

    interfacesy = 79,
    proceduresy = 80,
    qualifiedsy = 94,

    implementationsy = 81
};

const map<TokenCodes, string> toStringMap = {
        {star, "*"},
        {slash, "/"},
        {TokenCodes::equal, "="},
        {comma, ","},
        {semicolon, ";"},
        {colon, ":"},
        {point, "."},
        {arrow, "^"},
        {leftpar, "("},
        {rightpar, ")"},
        {lbracket, "["},
        {rbracket, "]"},
        {flpar, "{"},
        {frpar, "}"},
        {later, "<"},
        {TokenCodes::greater, ">"},
        {laterequal, "<="},
        {greaterequal, ">="},
        {latergreater, "<>"},
        {TokenCodes::plus, "+"},
        {TokenCodes::minus, "-"},
        {lcomment, "(*"},
        {rcomment, "*)"},
        {assign, ":="},
        {twopoints, ".."},
        {endofline, "\n"},
        {endoffile, "\0"},

        {dosy, "do"},
        {ifsy, "if"},
        {insy, "in"},
        {ofsy, "of"},
        {orsy, "or"},
        {tosy, "to"},
        {andsy, "and"},
        {divsy, "div"},
        {endsy, "end"},
        {forsy, "for"},
        {modsy, "mod"},
        {nilsy, "nil"},
        {notsy, "not"},
        {setsy, "set"},
        {varsy, "var"},
        {casesy, "case"},
        {elsesy, "else"},
        {filesy, "file"},
        {gotosy, "goto"},
        {onlysy, "only"},
        {thensy, "then"},
        {typesy, "type"},
        {unitsy, "unit"},
        {usessy, "uses"},
        {withsy, "with"},
        {arraysy, "array"},
        {beginsy, "begin"},
        {constsy, "const"},
        {labelsy, "label"},
        {untilsy, "until"},
        {whilesy, "while"},
        {downtosy, "downto"},
        {exportsy, "export"},
        {importsy, "import"},
        {modulesy, "module"},
        {packedsy, "packed"},
        {recordsy, "record"},
        {repeatsy, "repeat"},
        {vectorsy, "vector"},
        {stringsy, "string"},
        {forwardsy, "forward"},
        {processsy, "process"},
        {programsy, "program"},
        {segmentsy, "segment"},
        {functionsy, "function"},
        {separatesy, "separate"},
        {interfacesy, "interface"},
        {proceduresy, "procedure"},
        {qualifiedsy, "qualified"},
        {implementationsy, "implementation"}
};

const map<string, TokenCodes> KeywordsMap = {
        {"do", dosy},
        {"if", ifsy},
        {"in", insy},
        {"of", ofsy},
        {"or", orsy},
        {"to", tosy},
        {"and", andsy},
        {"div", divsy},
        {"end", endsy},
        {"for", forsy},
        {"mod", modsy},
        {"nil", nilsy},
        {"not", notsy},
        {"set", setsy},
        {"var", varsy},
        {"case", casesy},
        {"else", elsesy},
        {"file", filesy},
        {"goto", gotosy},
        {"only", onlysy},
        {"then", thensy},
        {"type", typesy},
        {"unit", unitsy},
        {"uses", usessy},
        {"with", withsy},
        {"array", arraysy},
        {"begin", beginsy},
        {"const", constsy},
        {"label", labelsy},
        {"until", untilsy},
        {"while", whilesy},
        {"downto", downtosy},
        {"export", exportsy},
        {"import", importsy},
        {"module", modulesy},
        {"packed", packedsy},
        {"record", recordsy},
        {"repeat", repeatsy},
        {"vector", vectorsy},
        {"string", stringsy},
        {"forward", forwardsy},
        {"process", processsy},
        {"program", programsy},
        {"segment", segmentsy},
        {"function", functionsy},
        {"separate", separatesy},
        {"interface", interfacesy},
        {"procedure", proceduresy},
        {"qualified", qualifiedsy},
        {"implementation", implementationsy}
};

// таблица описания ошибок
const map<int, string> ErrorTable = {
        {1,  "ошибка в простом типе"},
        {2,  "должно идти имя"},
        {3,  "должно быть служебное слово PROGRAM"},
        {4,  "должен идти символ ‘)’"},
        {5,  "должен идти символ ‘:’"},
        {6,  "запрещенный символ"},
        {7,  "ошибка в списке параметров"},
        {8,  "должно идти OF"},
        {9,  "должен идти символ ‘(‘"},
        {10,  "ошибка в типе"},
        {11,  "должен идти символ ‘[‘"},
        {12,  "должен идти символ ‘]’"},
        {13,  "должно идти слово END"},
        {14,  "должен идти символ ‘;’"},
        {15,  "должно идти целое"},
        {16,  "должен идти символ ‘=’"},
        {17,  "должно идти слово BEGIN"},
        {18,  "ошибка в разделе описаний"},
        {19,  "ошибка в списке полей"},
        {20,  "должен идти символ ‘,’"},
        {50,  "ошибка в константе"},
        {51,  "должен идти символ ‘:=’"},
        {52,  "должно идти слово THEN"},
        {53,  "должно идти слово UNTIL"},
        {54,  "должно идти слово DO"},
        {55,  "должно идти слово TO или DOWNTO"},
        {56,  "должно идти слово IF"},
        {58,  "должно идти слово TO или DOWNTO"},
        {61,  "должен идти символ ‘.’"},
        {74,  "должен идти символ ‘..’"},
        {75,  "ошибка в символьной константе"},
        {76,  "слишком длинная строковая константа"},
        {85,  "комментарий не открыт"},
        {86,  "комментарий не закрыт"},
        {100,  "использование имени не соответствует описанию"},
        {101,  "имя описано повторно"},
        {102,  "нижняя граница превосходит верхнюю"},
        {104,  "имя не описано"},
        {105,  "недопустимое рекурсивное определение"},
        {108,  "файл здесь использовать нельзя"},
        {109,  "тип не должен быть REAL"},
        {111,  "несовместимость с типом дискриминанта"},
        {112,  "недопустимый ограниченный тип"},
        {114,  "тип основания не должен быть REAL или INTEGER"},
        {115,  "файл должен быть текстовым"},
        {116,  "ошибка в типе параметра стандартной процедуры"},
        {117,  "неподходящее опережающее описание"},
        {118,  "недопустимый тип пpизнака ваpиантной части записи"},
        {119,  "опережающее описание: повторение списка параметровне допускается"},
        {120,  "тип результата функции должен быть скалярным, ссылочнымили ограниченным"},
        {121,  "параметр-значение не может быть файлом"},
        {122,  "опережающее описание функции: повторять тип результата нельзя"},
        {123,  "в описании функции пропущен тип результата"},
        {124,  "F-формат только для REAL"},
        {125,  "ошибка в типе параметра стандартной функции"},
        {126,  "число параметров не согласуется с описанием"},
        {127,  "недопустимая подстановка параметров"},
        {128,  "тип результата функции не соответствует описанию"},
        {130,  "выражение не относится к множественному типу"},
        {131,  "элементы множества не должны выходить из диапазона 0 .. 255"},
        {135,  "тип операнда должен быть BOOLEAN"},
        {137,  "недопустимые типы элементов множества"},
        {138,  "переменная не есть массив"},
        {139,  "тип индекса не соответствует описанию"},
        {140,  "переменная не есть запись"},
        {141,  "переменная должна быть файлом или ссылкой"},
        {142,  "недопустимая подстановка параметров"},
        {143,  "недопустимый тип параметра цикла"},
        {144,  "недопустимый тип выражения"},
        {145,  "конфликт типов"},
        {147,  "тип метки не совпадает с типом выбирающего выражения"},
        {149,  "тип индекса не может быть REAL или INTEGER"},
        {152,  "в этой записи нет такого поля"},
        {156,  "метка варианта определяется несколько раз"},
        {165,  "метка определяется несколько раз"},
        {166,  "метка описывается несколько раз"},
        {167,  "неописанная метка180"},
        {168,  "неопределенная метка"},
        {169,  "ошибка в основании множества (в базовом типе)"},
        {170,  "тип не может быть упакован"},
        {177,  "здесь не допускается присваивание имени функции"},
        {182,  "типы не совместны"},
        {183,  "запрещенная в данном контексте операция"},
        {184,  "элемент этого типа не может иметь знак"},
        {186,  "несоответствие типов для операции отношения"},
        {189,  "конфликт типов параметров"},
        {190,  "повторное опережающее описание"},
        {191,  "ошибка в конструкторе множества"},
        {193,  "лишний индекс для доступа к элементу массива"},
        {194,  "указано слишком мало индексов для доступа к элементу массива"},
        {195,  "выбирающая константа вне границ описанного диапазона"},
        {196,  "недопустимый тип выбирающей константы"},
        {197,  "параметры процедуры (функции) должны бытьпараметрами-значениями"},
        {198,  "несоответствие количества параметров параметра-процедуры (функции)"},
        {199,  "несоответствие типов параметров параметра-процедуры(функции)"},
        {200,  "тип парамера-функции не соответствует описанию"},
        {201,  "ошибка в вещественной константе: должна идти цифра"},
        {203,  "целая константа превышает предел"},
        {204,  "деление на нуль"},
        {206,  "слишком маленькая вещественная константа"},
        {207,  "слишком большая вещественная константа"},
        {208,  "недопустимые типы операндов операции IN"},
        {209,  "вторым операндом IN должно быть множество"},
        {210,  "операнды AND, NOT, OR должны быть булевыми"},
        {211,  "недопустимые типы операндов операции + или —"},
        {212,  "операнды DIV и MOD должны быть целыми"},
        {213,  "недопустимые типы операндов операции *"},
        {214,  "недопустимые типы операндов операции /"},
        {215,  "первым операндом IN должно быть выражение базовоготипа множества"},
        {216,  "опережающее описание есть, полного нет"},
        {305,  "индексное значение выходит за границы"},
        {306,  "присваиваемое значение выходит за границы"},
        {307,  "выражение для элемента множества выходит за пределы"},
        {308,  "выражение выходит за допустимые пределы"}
};

#endif //COMPILERPASCAL_CODES_H