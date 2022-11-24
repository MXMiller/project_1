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
        output.append(headPredicate->toString());
        output.append(" :- ");
        for(unsigned int i = 0; i < bodyPredicates.size(); i++){
            output.append(bodyPredicates.at(i)->toString());
            if(i < bodyPredicates.size() - 1){
                output.append(",");
            } else {
                output.append(".");
            }
        }
        return output;
    }

    void setHead(Predicate* input){
        headPredicate  = input;
    }

    Predicate* getHead(){
        return headPredicate;
    }

    void addBody(Predicate* input){
        bodyPredicates.push_back(input);
    }

    vector<Predicate*> getBody(){
        return bodyPredicates;
    }
};

#endif //PROJECT_1_RULE_H
