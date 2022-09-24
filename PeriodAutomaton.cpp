#include "PeriodAutomaton.h"

using namespace std;

void PeriodAutomaton::S0(const std::string& input) {
    if (input[index] == '.') {
        inputRead++;
    }
    else {
        Serr();
    }
}