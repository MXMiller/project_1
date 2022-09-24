#include "ColonDashAutomaton.h"

using namespace std;

void ColonDashAutomaton::S0(const std::string& input) {
    if (input[index] == ':') {
        //cout << "i read a COLON" << endl;
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void ColonDashAutomaton::S1(const std::string& input) {
    if (input[index] == '-') {
        //cout << "i read a COLON-DASH" << endl;
        inputRead++;
    }
    else {
        Serr();
    }
}