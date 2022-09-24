#include "CommaAutomaton.h"

using namespace std;

void CommaAutomaton::S0(const std::string& input) {
    if (input[index] == ',') {
        inputRead++;
    }
    else {
        Serr();
    }
}