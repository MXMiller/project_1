#include "Q_MarkAutomaton.h"

using namespace std;

void Q_MarkAutomaton::S0(const std::string& input) {
    if (input[index] == '?') {
        inputRead++;
    }
    else {
        Serr();
    }
}