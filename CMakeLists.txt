cmake_minimum_required(VERSION 3.23)
project(project_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(project_1
        Automaton.h
        ColonAutomaton.cpp
        ColonAutomaton.h
        ColonDashAutomaton.cpp
        ColonDashAutomaton.h
        Lexer.cpp
        Lexer.h
        main.cpp
        Token.cpp
        Token.h PeriodAutomaton.cpp PeriodAutomaton.h CommaAutomaton.cpp CommaAutomaton.h Q_MarkAutomaton.h Q_MarkAutomaton.cpp Left_ParenAutomaton.cpp Left_ParenAutomaton.h Right_ParenAutomaton.h Right_ParenAutomaton.cpp MultiplyAutomaton.h MultiplyAutomaton.cpp AddAutomaton.h AddAutomaton.cpp SchemesAutomaton.h SchemesAutomaton.cpp FactsAutomaton.h FactsAutomaton.cpp RulesAutomaton.h RulesAutomaton.cpp QueriesAutomaton.h QueriesAutomaton.cpp IdAutomaton.h IdAutomaton.cpp StringAutomaton.h StringAutomaton.cpp CommentAutomaton.h CommentAutomaton.cpp EOFAutomaton.h EOFAutomaton.cpp UndefinedAutomaton.h UndefinedAutomaton.cpp Parser.h Parser.cpp)
