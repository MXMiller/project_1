#include <vector>
#include <map>
#include "DatalogProgram.h"
#include "Header.h"
#include "Tuple.h"
#include "Relation.h"


Relation Relation::select1(int columnI, string val){

    Relation* selectR = new Relation(name, colNames);

    for(set<Tuple>::iterator i = tuples.begin(); i != tuples.end(); ++i){

        Tuple curr = *i;

        if(curr.getRowVal(columnI) == val){
            selectR->addTuple(curr);
        }
    }

    return *selectR;
}

Relation Relation::select2(int columnI1, int columnI2){

    Relation* selectR = new Relation(name, colNames);

    for(set<Tuple>::iterator i = tuples.begin(); i != tuples.end(); ++i){

        Tuple curr = *i;

        if(curr.getRowVal(columnI1) == curr.getRowVal(columnI2)){
            selectR->addTuple(curr);
        }
    }

    return *selectR;
}

Relation Relation::project(vector<int> columns){

    Header newHeader;
    vector<Parameter*> newC;

    //get the right column headers

    for(int i = 0; i < colNames.getSize(); i++){
        for(unsigned int j = 0; j < columns.size(); j++){
            if(i == columns.at(j)){
                //found one of the columns
                newC.push_back(colNames.getColName(i));
            }
        }
    }

    newHeader.setColName(newC);
    Relation projectR = *(new Relation(name, newHeader));

    //get the right column values

    for(set<Tuple>::iterator t = tuples.begin(); t != tuples.end(); t++){

        Tuple curr = *t;
        Tuple newT;

        vector<string> newVals;

        for(int i = 0; i < curr.getSize(); i++){

            for(unsigned int j = 0; j < columns.size(); j++){
                //what is the first thing supposed to be?
                if(i == columns.at(j)){
                    //found one of the columns
                    string tupleVal = curr.getRowVal(i);
                    newVals.push_back(tupleVal);
                }
            }
        }

        newT.setRowVals(newVals);

        projectR.addTuple(newT);
    }

    return projectR;
}

Relation Relation::rename(vector<string> newColNames){

    //the tuples that are sent into this function aren't the right tuples
    Header blank;

    Relation renameR = *(new Relation(name, blank));
    renameR.setTuples(this->getTuples());
    renameR.setName(name);

    vector<Parameter*> newN;

    for(unsigned int i = 0; i < newColNames.size(); i++){
        Parameter* newP = new Parameter(newColNames.at(i));
        if(newP->isCon() == false){
            newN.push_back(newP);
        }
    }

    Header newHeader;
    newHeader.setColName(newN);
    renameR.setHeader(newHeader);

    return renameR;
}

Relation Relation::Join(Relation r1, Relation r2){

    //combine headers

    vector<map<int, int>> colPairs;

    for(int i = 0; i < r1.colNames.getSize(); i++){

        string col1 = r1.colNames.getColName(i)->getParam();

        for(int j = 0; j < r2.colNames.getSize(); j++){

            string col2 = r2.colNames.getColName(j)->getParam();

            if(col1 == col2){
                map<int, int> newPair;
                newPair.insert(pair<int, int>(i, j));
                colPairs.push_back(newPair);
            }
        }
    }

    Header header = combineHeaders(r1.colNames, r2.colNames, colPairs);

    Relation joinR = *(new Relation(name, header));

    //combine tuples
    Tuple newTuple;
    bool joinable;

    for(set<Tuple>::iterator i = r1.tuples.begin(); i != r1.tuples.end(); ++i){

        Tuple curr1 = *i;

        for(set<Tuple>::iterator j = r2.tuples.begin(); j != r2.tuples.end(); ++j){

            Tuple curr2 = *j;

            joinable = isJoinable(curr1, curr2, colPairs);

            if(joinable){
                newTuple = combineTuples(curr1, curr2, colPairs);
                joinR.addTuple(newTuple);
            }
        }
    }

    return joinR;
}

Header Relation::combineHeaders(Header h1, Header h2, vector<map<int, int>> colPairs){

    vector<Parameter*> newColNames;

    for(int i = 0; i < h1.getSize(); i++){
        newColNames.push_back(h1.getColName(i));
    }

    for(int i = 0; i < h2.getSize(); i++){

        bool isIn = false;

        for(unsigned int j = 0; j < colPairs.size(); j++){
            if(i == colPairs.at(j)[1]){
               isIn = true;
            }
        }

        if(!isIn){
            newColNames.push_back(h2.getColName(i));
        }
    }

    Header newHeader;
    newHeader.setColName(newColNames);

    return newHeader;
}

bool Relation::isJoinable(Tuple t1, Tuple t2, vector<map<int, int>> colPairs){
    bool joinable = true;

    for(unsigned int i = 0; i < colPairs.size(); i++){
        map<int, int>::iterator it = colPairs.at(i).begin();
        if(t1.getRowVal(it->first) != t2.getRowVal(it->second)){
            joinable = false;
        }
    }

    return joinable;
}

Tuple Relation::combineTuples(Tuple t1, Tuple t2, vector<map<int, int>> colPairs){
    Tuple newTuple;

    vector<string> vals;

    for(int i = 0; i < t1.getSize(); i++){
        vals.push_back(t1.getRowVal(i));
    }

    for(int i = 0; i < t2.getSize(); i++){

        bool isIn = false;

        for(unsigned int j = 0; j < colPairs.size(); j++){
            if(i == colPairs.at(j)[2]){
                isIn = true;
            }
        }

        if(!isIn){
            vals.push_back(t2.getRowVal(i));
        }
    }

    newTuple.setRowVals(vals);

    return newTuple;
}

int Relation::unionR(Relation result, int n){
    int numNewTuples = 0;

    for(set<Tuple>::iterator i = result.tuples.begin(); i != result.tuples.end(); ++i){
        Tuple curr = *i;

        bool isNew = this->tuples.insert(curr).second;

        if(n == 0){
            toStringT(curr, result.getHeader());
            if(isNew){
                numNewTuples++;
            }
        } else {
            if(isNew){
                toStringT(curr, result.getHeader());
                numNewTuples++;
            }
        }
    }

    return numNewTuples;
}

void Relation::toStringT(Tuple tuple, Header colNames) {
    string output = "  ";

    for(int i = 0; i < tuple.getSize(); i++){
        output += colNames.getColName(i)->getParam() + "=" + tuple.getRowVal(i);
        if(i != tuple.getSize() - 1){
            output += ", ";
        }
    }

    output += "\n";

    cout << output;
}
