#include <vector>
#include "DatalogProgram.h"
#include "Parser.h"
#include "Predicate.h"
#include "Interpreter.h"
#include "Relation.h"
#include "Header.h"
#include "Tuple.h"

using namespace std;

void Interpreter::interpretSchemes(){

    cout << endl << "       IN THE interpretSchemes FUNCTION" << endl << endl;

    vector<Predicate*> schemes = program->getSchemes();

    for(unsigned int i  = 0; i < schemes.size(); i++){
        Header* header = new Header();

        header->setColName(schemes.at(i)->getParams());

        Relation* r = new Relation(schemes.at(i)->getID(), *header);

        database->addRel(r);
    }
}

void Interpreter::interpretFacts(){

    cout << endl << "       IN THE interpretFacts FUNCTION" << endl << endl;

    vector<Predicate*> facts = program->getFacts();

    for(unsigned int i  = 0; i < facts.size(); i++){
        Tuple* tuple = new Tuple();

        tuple->setRowVals(facts.at(i)->getParams());

        Relation* r = database->getRel(facts.at(i)->getID());

        r->addTuple(tuple);
    }
}

void Interpreter::interpretQueries(){

    cout << endl << "       IN THE interpretQueries FUNCTION" << endl << endl;

    vector<Predicate*> queries = program->getQueries();

    for(unsigned int i  = 0; i < queries.size(); i++){
        evaluatePredicate(queries.at(i));
    }
}

Relation Interpreter::evaluatePredicate(Predicate* query){

    Relation newR = database->getRelCopy(query->getID());

    vector<int> matchIndexes;
    vector<int> varIndexes;

    for(unsigned int j = 0; j < query->getParams().size(); j++){

        Parameter p = query->getParam(j);

        if(p.isCon() == true){ // parameter is a constant
            newR.select(j, query->getParam(j));
        }
        else if(p.isCon() == false){ // parameter is a variable
            string first = query->getParam(j);

            for(int k = 0; k < query->getParams().size(); k++){
                if(query->getParam(j) == query->getParam(k)){
                    newR.select(j, k);
                    matchIndexes.push_back(k);
                } else {
                    varIndexes.push_back(j);
                }
            }
        }
    }

    //use matchIndexes project out a column for each variable from the relation
    //use varIndexes to rename the relations header column names to query variables

    return newR;
}

string Interpreter::toString(){
    cout << endl << "       IN THE toString FUNCTION" << endl << endl;

    string output = "";

    return output;
}
