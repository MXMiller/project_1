#include "Token.h"

using namespace std;

Token::Token(TokenType type, std::string description, int line) {
    this->t = type;
    value = description;
    lineNum = line;
}

string Token::getType() {
    if(this->t == TokenType::COLON){
        return "COLON";
    }else if(this->t == TokenType::COLON_DASH){
        return "COLON_DASH";
    }else if(this->t == TokenType::PERIOD){
        return "PERIOD";
    }else if(this->t == TokenType::COMMA){
        return "COMMA";
    }else if(this->t == TokenType::Q_MARK){
        return "Q_MARK";
    }else if(this->t == TokenType::LEFT_PAREN){
        return "LEFT_PAREN";
    }else if(this->t == TokenType::RIGHT_PAREN){
        return "RIGHT_PAREN";
    }else if(this->t == TokenType::MULTIPLY){
        return "MULTIPLY";
    }else if(this->t == TokenType::ADD){
        return "ADD";
    }else if(this->t == TokenType::SCHEMES){
        return "SCHEMES";
    }else if(this->t == TokenType::FACTS){
        return "FACTS";
    }else if(this->t == TokenType::RULES){
        return "RULES";
    }else if(this->t == TokenType::QUERIES){
        return "QUERIES";
    }else if(this->t == TokenType::ID){
        return "ID";
    }else if(this->t == TokenType::STRING){
        return "STRING";
    }else if(this->t == TokenType::COMMENT){
        return "COMMENT";
    }else if(this->t == TokenType::ENDOFFILE){
        return "EOF";
    }else{
        return "UNDEFINED";
    }
}

TokenType Token::getTokenType() {
    return this->t;
}

string Token::getVal() {
    return value;
}

int Token::getLine() {
    return lineNum;
}


