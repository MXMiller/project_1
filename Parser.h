#ifndef PROJECT_1_PARSER_H
#define PROJECT_1_PARSER_H
#include <vector>
#include "Automaton.h"
#include "Token.h"
#include "Lexer.h"

using namespace std;

class Parser
{
private:


    std::vector<Token*> tokens;

    // TODO: add any other private methods here (if needed)

public:
    Parser();
    ~Parser();

    void Run(std::vector<Token*> tokens);

    // TODO: add other public methods here

    string toString();
};

#endif //PROJECT_1_PARSER_H
