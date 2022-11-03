#include <vector>
#include "DatalogProgram.h"
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
        Relation newR = database->getRelCopy(queries.at(i)->getID());

        for(unsigned int j = 0; i < queries.at(i)->getParams().size(); j++){

        }
    }
}

string Interpreter::toString(){
    cout << endl << "       IN THE toString FUNCTION" << endl << endl;
}
