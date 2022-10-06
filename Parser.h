#ifndef PROJECT_1_PARSER_H
#define PROJECT_1_PARSER_H
#include <vector>
#include "Automaton.h"
#include "Token.h"
#include "DatalogProgram.h"

using namespace std;

class Parser
{
private:

    DatalogProgram* datalog = new DatalogProgram();
    std::vector<Token*> tokens;

public:
    Parser();
    ~Parser();

    void Run(std::vector<Token*> inputTokens);

    string toString();
};

#endif //PROJECT_1_PARSER_H
