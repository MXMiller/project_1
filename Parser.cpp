#include "Parser.h"

using namespace std;

Parser::Parser(std::vector<Token*> inputTokens) {
    tokens = inputTokens;
}

Parser::~Parser() {
    // TODO: need to clean up the memory in `automata` and `tokens`
}

/*
Predicate Parser::scheme(){

}

Predicate Parser::fact(){

}

Rule Parser::rule(){

}

Predicate Parser::query(){

}
*/

DatalogProgram* Parser::parse(){

    cout << "I am in Parser.cpp" << endl;

    for(unsigned int i = 0; i < tokens.size(); i++) {
        Token* currToken = tokens.at(i);
    }

    return datalog;
}

string Parser::toString() {
    string output = "";

    //output the list of schemes, facts, rules, queries, and domain

    for(unsigned int i = 0; i < tokens.size(); i++){
        output.push_back('(');
        output.append((tokens.at(i)->getType()) + ',' + '"');
        output.append(tokens.at(i)->getVal() + '"' + ',');
        output += to_string(tokens.at(i)->getLine());
        output.append(")\n");
    }

    output.append("Total Tokens = ");
    output += to_string(tokens.size());


    return output;
}

