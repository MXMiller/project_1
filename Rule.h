#ifndef PROJECT_1_RULE_H
#define PROJECT_1_RULE_H
#include <vector>
#include "Automaton.h"
#include "Token.h"
#include "DatalogProgram.h"
#include "Predicate.h"

using namespace std;

class Rule
{
private:

    Predicate* head = new Predicate();
    vector<Predicate*> body;

public:
    Rule(){}
    ~Rule(){}
};

#endif //PROJECT_1_RULE_H
