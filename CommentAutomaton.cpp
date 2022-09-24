#include "CommentAutomaton.h"

using namespace std;

void CommentAutomaton::S0(const std::string& input) {
    if (input[index] == '#') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void CommentAutomaton::S1(const std::string& input) {
    if(input[index] == '\n'){

    } else if (input[index] == '|'){
        inputRead++;
        index++;
        S2(input);
    } else {
        inputRead++;
        index++;
        S1(input);
    }
}

void CommentAutomaton::S2(const std::string& input) {
    if (input[index] == '\n') {
        this->newLines++;
        inputRead++;
        index++;
        S2(input);
    } else if (input[index] == '|'){
        inputRead++;
        index++;
        S3(input);
    } else if (isalpha(input[index]) || isalnum(input[index]) || isspace(input[index]) || input[index] == '\n') {
        inputRead++;
        index++;
        S2(input);
    } else {
        this->type = TokenType::UNDEFINED;
    }
}

void CommentAutomaton::S3(const std::string& input) {
    if (input[index] == '#'){
        inputRead++;
    } else if (isalpha(input[index]) || isalnum(input[index]) || isspace(input[index])) {
        inputRead++;
        index++;
        S3(input);
    } else {
        this->type = TokenType::UNDEFINED;
    }
}
