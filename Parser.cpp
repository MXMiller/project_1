#include "Parser.h"

using namespace std;

Parser::Parser(std::vector<Token*> inputTokens) {
    tokens = inputTokens;
}

Parser::~Parser() {
    // TODO: need to clean up the memory in `automata` and `tokens`
}

void Parser::match(TokenType type, int i){
    if((tokens.at(i)->getTokenType()) == type){
        //cout << endl << "match: " << tokens.at(i)->getType() << endl;
    }else{
        //cout << endl << "   fail: " << tokens.at(i)->getType() << endl;
        throw (tokens.at(i));
    }
}

void Parser::datalogProgram(){
    //cout << "       IN datalogProgram FUNCTION" << endl;

    match(TokenType::SCHEMES, i++);
    match(TokenType::COLON, i++);
    scheme();
    schemeList();
    match(TokenType::FACTS, i++);
    match(TokenType::COLON, i++);
    factList();
    match(TokenType::RULES, i++);
    match(TokenType::COLON, i++);
    ruleList();
    match(TokenType::QUERIES, i++);
    match(TokenType::COLON, i++);
    query();
    queryList();
    match(TokenType::ENDOFFILE, i++);
}

void Parser::schemeList(){
    //cout << "       IN schemeList FUNCTION" << endl;
    scheme();

    if(tokens.at(i)->getTokenType() == TokenType::ID){
        schemeList();
    }
}
void Parser::factList(){
    //cout << "       IN factList FUNCTION" << endl;
    fact();

    if(tokens.at(i)->getTokenType() == TokenType::ID){
        factList();
    }
}
void Parser::ruleList(){
    //cout << "       IN ruleList FUNCTION" << endl;
    rule();

    if(tokens.at(i)->getTokenType() == TokenType::RULES){
        ruleList();
    }
}
void Parser::queryList(){
    //cout << "       IN queryList FUNCTION" << endl;
    query();

    if(tokens.at(i)->getTokenType() == TokenType::ID){
        queryList();
    }
}

Predicate Parser::scheme(){
    //cout << "       IN scheme FUNCTION" << endl;

    Predicate* p = new Predicate();

    match(TokenType::ID, i++);
    match(TokenType::LEFT_PAREN, i++);
    match(TokenType::ID, i++);
    idList();
    match(TokenType::RIGHT_PAREN, i++);

    return *p;
}
Predicate Parser::fact(){
    //cout << "       IN fact FUNCTION" << endl;

    Predicate* p = new Predicate();

    match(TokenType::ID, i++);
    match(TokenType::LEFT_PAREN, i++);
    match(TokenType::STRING, i++);
    stringList();
    match(TokenType::RIGHT_PAREN, i++);
    match(TokenType::PERIOD, i++);

    return *p;
}
Rule Parser::rule(){
    //cout << "       IN rule FUNCTION" << endl;

    Rule* r = new Rule();

    headPredicate();
    match(TokenType::COLON_DASH, i++);
    predicate();
    if(tokens.at(i)->getTokenType() != TokenType::PERIOD){
        predicateList();
    }
    match(TokenType::PERIOD, i++);

    return *r;
}
Predicate Parser::query(){
    //cout << "       IN query FUNCTION" << endl;

    Predicate* p = new Predicate();

    predicate();
    match(TokenType::Q_MARK, i++);

    return *p;
}

void Parser::headPredicate(){
    //cout << "       IN headPredicate FUNCTION" << endl;

    match(TokenType::ID, i++);
    match(TokenType::LEFT_PAREN, i++);
    match(TokenType::ID, i++);
    idList();
    match(TokenType::RIGHT_PAREN, i++);
}
void Parser::predicate(){
    //cout << "       IN predicate FUNCTION" << endl;

    match(TokenType::ID, i++);
    match(TokenType::LEFT_PAREN, i++);
    parameter();
    if(tokens.at(i)->getTokenType() != TokenType::RIGHT_PAREN){
        parameterList();
    }
    match(TokenType::RIGHT_PAREN, i++);
}

void Parser::predicateList(){
    //cout << "       IN predicateList FUNCTION" << endl;

    match(TokenType::COMMA, i++);
    predicate();

    if(tokens.at(i)->getTokenType() == TokenType::COMMA){
        predicateList();
    }
}
void Parser::parameterList(){
    //cout << "       IN parameterList FUNCTION" << endl;

    match(TokenType::COMMA, i++);
    parameter();

    if(tokens.at(i)->getTokenType() == TokenType::COMMA){
        parameterList();
    }
}
void Parser::stringList(){
    //cout << "       IN stringList FUNCTION" << endl;

    match(TokenType::COMMA, i++);
    match(TokenType::STRING, i++);

    if(tokens.at(i)->getTokenType() == TokenType::COMMA){
        stringList();
    }
}
void Parser::idList(){
    //cout << "       IN idList FUNCTION" << endl;

    match(TokenType::COMMA, i++);
    match(TokenType::ID, i++);

    if(tokens.at(i)->getTokenType() == TokenType::COMMA){
        idList();
    }
}
void Parser::parameter(){
    //cout << "       IN parameter FUNCTION" << endl;

    if((tokens.at(i)->getTokenType()) == TokenType::STRING){
        //cout << endl << "match: " << tokens.at(i)->getType() << endl;
        i++;
    }else if((tokens.at(i)->getTokenType()) == TokenType::ID){
        //cout << endl << "match: " << tokens.at(i)->getType() << endl;
        i++;
    }else{
        //cout << endl << "   fail: " << tokens.at(i)->getType() << endl;
        throw (tokens.at(i));
    }
}

DatalogProgram* Parser::parse(){

    //cout << "I am in the parser" << endl;

    //1. WIP check syntax. make sure you have the right things in the right order
    //2. write classes and data structures
    //3. write code to create data structures

    try {
        datalogProgram();
        cout << "Success!" << endl;
    }
    catch (Token* token) {
        // Block of code to handle errors
        cout << "Failure!" << endl;
        cout << "  (" << token->getType() << ",'" << token->getVal() << "'," << token->getLine() << ")" << endl;
    }

    return datalog;
}

string Parser::toString() {

    string output = "";

    //output the list of schemes, facts, rules, queries, and domain
    /*
    for(unsigned int i = 0; i < tokens.size(); i++){
        output.push_back('(');
        output.append((tokens.at(i)->getType()) + ',' + '"');
        output.append(tokens.at(i)->getVal() + '"' + ',');
        output += to_string(tokens.at(i)->getLine());
        output.append(")\n");
    }

    output.append("Total Tokens = ");
    output += to_string(tokens.size());
    */

    return output;
}

