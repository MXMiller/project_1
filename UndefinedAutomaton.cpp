#include "UndefinedAutomaton.h"

using namespace std;

void UndefinedAutomaton::S0(const std::string& input) {
    if ((isalnum(input[index]) || !isalpha(input[index]))
    & ((input[index] != ',') & (input[index] != '.') & (input[index] != '?')
    & (input[index] != '(') & (input[index] != ')') & (input[index] != ':')
    & (input[index] != '*') & (input[index] != '+') & (!isspace(input[index])))) {
        inputRead++;
    }
    else {
        Serr();
    }
}