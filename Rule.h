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

    Predicate* headPredicate = new Predicate();
    vector<Predicate*> bodyPredicates;

public:
    Rule(){}
    ~Rule(){}

    string toString(){
        string output = "";
        return output;
    }

    void setHead(Predicate* input){
        headPredicate  = input;
    }

    void addBody(Predicate* input){
        bodyPredicates.push_back(input);
    }
};

#endif //PROJECT_1_RULE_H
