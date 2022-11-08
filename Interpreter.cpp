#include <vector>
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

        tuple->setRowVals(facts.at(i)->getParams());

        Relation* r = database->getRel(facts.at(i)->getID());

        r->addTuple(*tuple);
    }
}

void Interpreter::interpretQueries(){

    //cout << endl << "       IN THE interpretQueries FUNCTION" << endl << endl;

    vector<Predicate*> queries = program->getQueries();

    for(unsigned int i  = 0; i < queries.size(); i++){
        Relation result = evaluatePredicate(queries.at(i));

        toString(result, queries.at(i));
    }
}

Relation Interpreter::evaluatePredicate(Predicate* query){

    Relation newR = database->getRelCopy(query->getID());

    vector<int> varFirst;
    vector<string> varIndexes;

    for(unsigned int i = 0; i < query->getParams().size(); i++){

        Parameter p = query->getParam(i);

        if(p.isCon() == true){ // parameter is a constant
            newR = newR.select1(i, query->getParam(i));
        }
        else if(p.isCon() == false){ // parameter is a variable
            string first = query->getParam(i);

            varFirst.push_back(i);

            for(unsigned int j = 0; j < query->getParams().size(); j++){
                if(query->getParam(i) == query->getParam(j)){
                    newR = newR.select2(i, j);
                } else {
                    varIndexes.push_back(query->getParam(i));
                }
            }
        }
    }

    //use varFirst project out a column for each variable from the relation
    Relation newR2 = newR.project(varFirst);

    //use varIndexes to rename the relations header column names to query variables

    //the getTuples() function destroys newR2's tuples for some reason
    //set<Tuple*> theTuples = newR2.getTuples();

    Relation newR3  = newR2.rename(varIndexes);

    return newR3;
}

void Interpreter::toString(Relation relation, Predicate* query){
    //cout << endl << "       IN THE toString FUNCTION" << endl << endl;

    string output = "";

    //output the query stuff
    output += query->getID() + "(";

    for(unsigned int i = 0; i < query->getSize(); i++){
        output += query->getParam(i);
        if(i < query->getSize() - 1){
            output += ",";
        }
    }

    output += ")? ";

    //is the query true?



    //output the relations stuff

    output += "\n  ";

    for(unsigned int i = 0; i < query->getSize(); i++){ //maybe use the relation size
        if(query->getParams().at(i)->isCon() == false){ //and it is a YES

            for(set<Tuple>::iterator t = relation.getTuples().begin(); t != relation.getTuples().end(); t++){
                Tuple curr = *t;
                for(unsigned int j = 0; j < curr.getSize(); j++){
                    output += query->getParam(i) + "=" + curr.getRowVal(j);
                }
            }

            if(i < query->getSize() - 1){
                output += ",";
            }
        }
    }

    output += "\n";

    cout << output;
}
