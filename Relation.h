#ifndef PROJECT_1_RELATION_H
#define PROJECT_1_RELATION_H
#include <vector>
#include <map>
#include "DatalogProgram.h"
#include "Predicate.h"
#include "Rule.h"
#include "Header.h"
#include "Tuple.h"

using namespace std;

class Relation
{
private:
    string name;
    Header colNames;
    set<Tuple> tuples;

public:
    Relation() = default;
    Relation(string name, Header colNames){
        this->name = name;
        this->colNames = colNames;
    }
    ~Relation(){}

    string getName(){
        return name;
    }

    Header getHeader(){
        return colNames;
    }

    set<Tuple> getTuples(){
        return tuples;
    }

    void setName(string input){
        name = input;
    }

    void setHeader(Header input){
        colNames = input;
    }

    void setTuples(set<Tuple> input){
        tuples = input;
    }

    void addTuple(Tuple newTuple){
        tuples.insert(newTuple);
    }

    bool addTupleB(Tuple newTuple){
        return tuples.insert(newTuple).second;
    }

    Relation select1(int columnI, string val);
    Relation select2(int columnI1, int columnI2);
    Relation project(vector<int> columns);
    Relation rename(vector<string> newColNames);

    Relation Join(Relation r1, Relation r2);
    Header combineHeaders(Header h1, Header h2, vector<map<int, int>> colPairs);
    bool isJoinable(Tuple t1, Tuple t2, vector<map<int, int>> colPairs);
    Tuple combineTuples(Tuple t1, Tuple t2, vector<map<int, int>> colPairs);

    int unionR(Relation result, int n);

    void toStringT(Tuple tuple, Header colNames);
};

#endif //PROJECT_1_RELATION_H
