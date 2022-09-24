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
    if ((input[index] == '|') & (index == 1)) {
        inputRead++;
        index++;
        S2(input);
    } else if(input[index] == '\n'){

    } else {
        inputRead++;
        index++;
        S1(input);
    }
}

void CommentAutomaton::S2(const std::string& input) {
    if(index >= (input.size())){
        this->type = TokenType::UNDEFINED;
    } else if ((input[index] == '|') & (input[index + 1] == '#')){
        inputRead++;
        inputRead++;
    } else if(input[index] == '\n'){
        inputRead++;
        index++;
        S2(input);
    } else {
        inputRead++;
        index++;
        S2(input);
    }
}

