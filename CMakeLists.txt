cmake_minimum_required(VERSION 3.17)
project(CompilerPascal)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        CompilerPascal main.cpp
        Headers/Token.h Headers/Constants.h
        Headers/Codes.h
        IoModule/IoModule.cpp IoModule/IoModule.h
        Lexer/Lexer.cpp Lexer/Lexer.h
        #Syntaxer/Syntaxer.cpp Syntaxer/Syntaxer.h
        #Headers/Type.cpp Headers/Type.h
)