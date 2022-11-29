#include <vector>
#include <algorithm>
#include "DatalogProgram.h"
#include "Predicate.h"
#include "Interpreter.h"
#include "Relation.h"
#include "Header.h"
#include "Tuple.h"

using namespace std;

void Interpreter::interpretSchemes(){

    //cout << endl << "       IN THE interpretSchemes FUNCTION" << endl << endl;

    vector<Predicate*> schemes = program->getSchemes();

    for(unsigned int i  = 0; i < schemes.size(); i++){
        Header* header = new Header();

        header->setColName(schemes.at(i)->getParams());

        Relation* r = new Relation(schemes.at(i)->getID(), *header);

        database->addRel(r);
    }
}

void Interpreter::interpretFacts(){

    //cout << endl << "       IN THE interpretFacts FUNCTION" << endl << endl;

    vector<Predicate*> facts = program->getFacts();

    for(unsigned int i  = 0; i < facts.size(); i++){
        Tuple* tuple = new Tuple();

        vector<Parameter*> vp = facts.at(i)->getParams();
        vector<string> vs;

        for(unsigned int i = 0; i < vp.size(); i++){
            vs.push_back(vp.at(i)->getParam());
        }

        tuple->setRowVals(vs);

        Relation* r = database->getRel(facts.at(i)->getID());

        r->addTuple(*tuple);
    }
}

void Interpreter::interpretRules(){
    cout << "Rule Evaluation" << endl;

    vector<Rule*> rules = program->getRules();

    //while something do this. Keep track of how many times it does it.
    int numNewTuples = 0;
    int n = 0;

    set<Tuple> allTuples;

    do{
        numNewTuples = 0;

        set<Tuple> newTuples;

        for(unsigned int i = 0; i < rules.size(); i++){
            cout << rules.at(i)->toString() << endl;

            Relation result = evaluateRules(rules.at(i));

            Relation* r = database->getRel(result.getName());

            numNewTuples += r->unionR(result, n);
        }

        n++;
    }while(numNewTuples > 0);

    cout << "\nSchemes populated after " << n << " passes through the Rules.\n\n";
}

Relation Interpreter::evaluateRules(Rule* rule){

    Predicate* head = rule->getHead();
    vector<Predicate*> body = rule->getBody();
    vector<Relation> relations;

    for(unsigned int j = 0; j < body.size(); j++){
        Relation r = evaluatePredicate(body.at(j));
        relations.push_back(r);
    }

    Relation result = relations.at(0);
    if(relations.size() > 1){
        for(unsigned int j = 1; j < relations.size(); j++){
            result = result.Join(result, relations.at(j));
        }
    }

    vector<string> headColNames;

    for(unsigned int i = 0; i < head->getParams().size(); i++){
        headColNames.push_back(head->getParam(i));
    }

    vector<int> headCols;

    for(int i = 0; i < headColNames.size(); i++){
        for(unsigned int j = 0; j < result.getHeader().getSize(); j++){
            if(headColNames.at(i) == result.getHeader().getColName(j)->getParam()){
                headCols.push_back(j);
            }
        }
    }

    result = result.project(headCols);

    vector<string> varIndexes;

    Relation* r = database->getRel(rule->getHead()->getID());
    Header h = r->getHeader();

    for(int i = 0; i < h.getSize(); i++){
        varIndexes.push_back(h.getColName(i)->getParam());
    }

    result = result.rename(varIndexes);

    result.setName(head->getID());

    return result;
}

void Interpreter::interpretQueries(){

    cout << "Query Evaluation" << endl;

    vector<Predicate*> queries = program->getQueries();

    for(unsigned int i  = 0; i < queries.size(); i++){
        Relation result = evaluatePredicate(queries.at(i));

        toStringQ(result, queries.at(i));
    }
}

Relation Interpreter::evaluatePredicate(Predicate* query){

    Relation newR = database->getRelCopy(query->getID());

    vector<int> varFirst;
    vector<string> varIndexes;

    for(unsigned int i = 0; i < query->getParams().size(); i++){

        Parameter p = query->getParam(i);
        if(query->getParamCon(i) == true){
            p.setConstant();
        }

        if(p.isCon() == true){ // parameter is a constant
            newR = newR.select1(i, query->getParam(i));

            varIndexes.push_back(query->getParam(i));
        } else { // parameter is a variable
            string first = query->getParam(i);

            varFirst.push_back(i);

            for(unsigned int j = 0; j < query->getParams().size(); j++){
                if(query->getParam(i) == query->getParam(j)){
                    newR = newR.select2(i, j);
                    if(find(varIndexes.begin(), varIndexes.end(), query->getParam(i)) == varIndexes.end()){
                        varIndexes.push_back(query->getParam(i));
                    }
                } else {
                    //if it's not already in the vector
                    if(find(varIndexes.begin(), varIndexes.end(), query->getParam(i)) == varIndexes.end()){
                        varIndexes.push_back(query->getParam(i));
                    }
                }
            }
        }
    }

    //use varFirst project out a column for each variable from the relation
    Relation newR2 = newR.project(varFirst);

    //use varIndexes to rename the relations header column names to query variables
        //varIndexes is empty when it should have stuff in it.
    Relation newR3 = newR2.rename(varIndexes);

    return newR3;
}

void Interpreter::toStringQ(Relation relation, Predicate* query){
    //cout << endl << "       IN THE toString FUNCTION" << endl << endl;

    string output = "";

    //output the query stuff
    output += query->getID() + "(";

    for(int i = 0; i < query->getSize(); i++){
        output += query->getParam(i);
        if(i < query->getSize() - 1){
            output += ",";
        }
    }

    output += ")?";

    //output the relations stuff

    set<Tuple> tuples = relation.getTuples();

    if(tuples.size() > 0){ //if there's more than 1 tuple

        output += " Yes(";
        output += to_string(tuples.size());
        output += ")";

        //output the tuples
        for(set<Tuple>::iterator t = tuples.begin(); t != tuples.end(); ++t){
            Tuple curr = *t;

            if(curr.getSize() != 0){
                output += "\n  ";
            }

            int j = 0;
            set<string> visited;

            for(int i = 0; i < curr.getSize(); i++){
                if(query->getParamCon(j) == true){
                    j++;
                }

                if(visited.find(query->getParam(j)) == visited.end()){
                    output += query->getParam(j) + "=" + curr.getRowVal(i);
                    visited.insert(query->getParam(j));
                    output += ", ";
                }

                j++;
            }

            if(j != 0){
                output.erase(output.end() - 2, output.end());
            }
        }

    } else { //if there's no tuples
        output += " No";
    }

    output += "\n";

    cout << output;
}
