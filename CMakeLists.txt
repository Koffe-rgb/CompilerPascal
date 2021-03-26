cmake_minimum_required(VERSION 3.17)
project(CompilerPascal)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        CompilerPascal main.cpp

        IoModule/IoModule.cpp IoModule/IoModule.h

        Lexer/Constants.h
        Lexer/Token.h
        Lexer/Codes.h
        Lexer/Lexer.cpp Lexer/Lexer.h

        Syntaxer/Sets.h
        Syntaxer/Syntaxer.cpp Syntaxer/Syntaxer.h

        Semancer/Type.h
        Semancer/Identifier.h
        Semancer/Scope.cpp Semancer/Scope.h
        Semancer/Semancer.cpp Semancer/Semancer.h
)