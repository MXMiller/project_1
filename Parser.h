#ifndef PROJECT_1_PARSER_H
#define PROJECT_1_PARSER_H
#include <vector>
#include "Automaton.h"
#include "Token.h"
#include "DatalogProgram.h"
#include "Predicate.h"
#include "Rule.h"

using namespace std;

class Parser
{
private:

    DatalogProgram* datalog = new DatalogProgram();

    std::vector<Token*> tokens;

    int i = 0;

public:
    Parser(std::vector<Token*> inputTokens);
    ~Parser();

    DatalogProgram* parse();

    string toString();

    void match(TokenType type, int i);

    //DATALOG GRAMMAR

    void datalogProgram();

    void schemeList();
    void factList();
    void ruleList();
    void queryList();

    Predicate scheme();
    Predicate fact();
    Rule rule();
    Predicate query();

    void headPredicate();
    void predicate();

    void predicateList();
    void parameterList();
    void stringList();
    void idList();
    void parameter();

};

#endif //PROJECT_1_PARSER_H
