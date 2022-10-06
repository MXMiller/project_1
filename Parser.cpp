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

    if(tokens.at(i)->getTokenType() == TokenType::ID){
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

    Predicate* scheme = new Predicate();

    match(TokenType::ID, i);
    scheme->setID(tokens.at(i)->getVal());
    i++;
    match(TokenType::LEFT_PAREN, i);
    i++;
    match(TokenType::ID, i);
    scheme->addParam(tokens.at(i)->getVal());
    i++;
    idList(scheme);
    match(TokenType::RIGHT_PAREN, i);
    i++;

    datalog->addScheme(scheme);

    return *scheme;
}
Predicate Parser::fact(){
    //cout << "       IN fact FUNCTION" << endl;

    Predicate* fact = new Predicate();

    match(TokenType::ID, i);
    fact->setID(tokens.at(i)->getVal());
    i++;
    match(TokenType::LEFT_PAREN, i);
    i++;
    match(TokenType::STRING, i);
    fact->addParam(tokens.at(i)->getVal());
    i++;
    stringList(fact);
    match(TokenType::RIGHT_PAREN, i);
    i++;
    match(TokenType::PERIOD, i);
    i++;

    datalog->addFact(fact);

    return *fact;
}
Rule Parser::rule(){
    //cout << "       IN rule FUNCTION" << endl;

    Rule* rule = new Rule();

    headPredicate(rule);
    match(TokenType::COLON_DASH, i);
    i++;
    predicate(rule);
    if(tokens.at(i)->getTokenType() != TokenType::PERIOD){
        predicateList(rule);
    }
    match(TokenType::PERIOD, i);
    i++;

    datalog->addRule(rule);

    return *rule;
}
Predicate Parser::query(){
    //cout << "       IN query FUNCTION" << endl;

    Predicate* query = new Predicate();

    predicate(query);
    match(TokenType::Q_MARK, i);
    i++;

    datalog->addQuery(query);

    return *query;
}

void Parser::headPredicate(Rule* rule){
    //cout << "       IN headPredicate FUNCTION" << endl;

    Predicate* head = new Predicate();

    match(TokenType::ID, i);
    head->setID(tokens.at(i)->getVal());
    i++;
    match(TokenType::LEFT_PAREN, i);
    i++;
    match(TokenType::ID, i);
    head->addParam(tokens.at(i)->getVal());
    i++;
    idList(head);
    match(TokenType::RIGHT_PAREN, i);
    i++;

    rule->setHead(head);
}
void Parser::predicate(Rule* rule){
    //cout << "       IN predicate FUNCTION" << endl;

    Predicate* body = new Predicate();

    match(TokenType::ID, i);
    body->setID(tokens.at(i)->getVal());
    i++;
    match(TokenType::LEFT_PAREN, i);
    i++;
    parameter(body);
    if(tokens.at(i)->getTokenType() != TokenType::RIGHT_PAREN){
        parameterList(body);
    }
    match(TokenType::RIGHT_PAREN, i);
    i++;

    rule->addBody(body);
}
void Parser::predicate(Predicate* query){
    //cout << "       IN predicate FUNCTION" << endl;

    match(TokenType::ID, i);
    query->setID(tokens.at(i)->getVal());
    i++;
    match(TokenType::LEFT_PAREN, i);
    i++;
    parameter(query);
    if(tokens.at(i)->getTokenType() != TokenType::RIGHT_PAREN){
        parameterList(query);
    }
    match(TokenType::RIGHT_PAREN, i);
    i++;
}

void Parser::predicateList(Rule* rule){
    //cout << "       IN predicateList FUNCTION" << endl;

    match(TokenType::COMMA, i);
    i++;
    predicate(rule);

    if(tokens.at(i)->getTokenType() == TokenType::COMMA){
        predicateList(rule);
    }
}
void Parser::parameterList(Predicate* input){
    //cout << "       IN parameterList FUNCTION" << endl;

    match(TokenType::COMMA, i);
    i++;
    parameter(input);

    if(tokens.at(i)->getTokenType() == TokenType::COMMA){
        parameterList(input);
    }
}
void Parser::stringList(Predicate* fact){
    //cout << "       IN stringList FUNCTION" << endl;

    match(TokenType::COMMA, i);
    i++;
    match(TokenType::STRING, i);
    fact->addParam(tokens.at(i)->getVal());
    i++;

    if(tokens.at(i)->getTokenType() == TokenType::COMMA){
        stringList(fact);
    }
}
void Parser::idList(Predicate* input){
    //cout << "       IN idList FUNCTION" << endl;

    match(TokenType::COMMA, i);
    i++;
    match(TokenType::ID, i);
    input->addParam(tokens.at(i)->getVal());
    i++;

    if(tokens.at(i)->getTokenType() == TokenType::COMMA){
        idList(input);
    }
}
void Parser::parameter(Predicate* input){
    //cout << "       IN parameter FUNCTION" << endl;

    if((tokens.at(i)->getTokenType()) == TokenType::STRING){
        //cout << endl << "match: " << tokens.at(i)->getType() << endl;
        input->addParam(tokens.at(i)->getVal());
        i++;
    }else if((tokens.at(i)->getTokenType()) == TokenType::ID){
        //cout << endl << "match: " << tokens.at(i)->getType() << endl;
        input->addParam(tokens.at(i)->getVal());
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
        cout << toString();
    }
    catch (Token* token) {
        // Block of code to handle errors
        cout << "Failure!" << endl;
        cout << "  (" << token->getType() << ",\"" << token->getVal() << "\"," << token->getLine() << ")" << endl;
    }

    return datalog;
}

string Parser::toString() {
    return datalog->toString();
}

