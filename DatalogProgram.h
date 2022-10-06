#ifndef PROJECT_1_DATALOGPROGRAM_H
#define PROJECT_1_DATALOGPROGRAM_H
#include <vector>
#include <set>
#include "Automaton.h"
#include "Token.h"
#include "Predicate.h"
#include "Rule.h"

using namespace std;

class DatalogProgram
{
private:

    vector<Predicate*> schemes;
    vector<Predicate*> facts;
    vector<Rule*> rules;
    vector<Predicate*> queries;

    set<string> domain;

public:
    DatalogProgram(){}
    ~DatalogProgram(){}

    string toString(){
        string output = "";

        //SCHEMES:
        output.append("Schemes(");
        output += to_string(getSize(schemes));
        output.append("):\n");
        for(unsigned int i = 0; i < schemes.size(); i++){
            output.append("  " + schemes.at(i)->toString() + "\n");
        }

        //FACTS
        output.append("Facts(");
        output += to_string(getSize(facts));
        output.append("):\n");
        for(unsigned int i = 0; i < facts.size(); i++){
            output.append("  " + facts.at(i)->toString() + "\n");
        }

        //RULES
        output.append("Rules(");
        output += to_string(getSize(rules));
        output.append("):\n");
        for(unsigned int i = 0; i < rules.size(); i++){
            output.append("  " + rules.at(i)->toString() + "\n");
        }

        //QUERIES
        output.append("Queries(");
        output += to_string(getSize(queries));
        output.append("):\n");
        for(unsigned int i = 0; i < queries.size(); i++){
            output.append("  " + queries.at(i)->toString() + "\n");
        }

        //DOMAIN

        fillDomain();

        //set<int>::iterator itr;

        output.append("Domain(");
        output += to_string(domain.size());
        output.append("):\n");
        for(auto itr : domain){
            output.append("  " + itr + "\n");
        }

        return output;
    }

    void addScheme(Predicate* scheme){
        schemes.push_back(scheme);
    }

    void addFact(Predicate* fact){
        facts.push_back(fact);
    }

    void addRule(Rule* rule){
        rules.push_back(rule);
    }
    void addQuery(Predicate* query){
        queries.push_back(query);
    }

    int getSize(vector<Predicate*> input){ return input.size(); }
    int getSize(vector<Rule*> input){ return input.size(); }

    void fillDomain(){
        for(unsigned int i = 0; i < facts.size(); i++){ //for each fact
            for(int j = 0; j < facts.at(i)->getSize(); j++){ //for each parameter in that fact
                string s = facts.at(i)->getParam(j);
                domain.insert(s);
            }
        }
    }
};

#endif //PROJECT_1_DATALOGPROGRAM_H
