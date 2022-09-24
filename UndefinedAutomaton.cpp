#include "UndefinedAutomaton.h"

using namespace std;

void UndefinedAutomaton::S0(const std::string& input) {
    if ((isalnum(input[index]) || !isalpha(input[index]))
        & ((input[index] != ',') & (input[index] != '.') & (input[index] != '?')
        & (input[index] != '(') & (input[index] != ')') & (input[index] != ':')
        & (input[index] != '*') & (input[index] != '+') & (!isspace(input[index])))) {
        inputRead++;
    } else if(input[index] == '\''){
        //inputRead++;
        //index++;
        //S1(input);
    }else {
        Serr();
    }
}

void UndefinedAutomaton::S1(const std::string& input) {
    if(input[index] == '\''){
        Serr();
    } else {
        if(index <= static_cast<int>(input.size())){
            inputRead++;
            index++;
            S1(input);
        }
    }
}
