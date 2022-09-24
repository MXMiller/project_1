#ifndef PROJECT_1_LEFT_PARENAUTOMATON_H
#define PROJECT_1_LEFT_PARENAUTOMATON_H

#include "Automaton.h"

using namespace std;

class Left_ParenAutomaton : public Automaton
{
public:
    Left_ParenAutomaton() : Automaton(TokenType::LEFT_PAREN) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif //PROJECT_1_LEFT_PARENAUTOMATON_H
