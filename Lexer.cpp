#include "Lexer.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "PeriodAutomaton.h"
#include "CommaAutomaton.h"
#include "Q_MarkAutomaton.h"
#include "Left_ParenAutomaton.h"
#include "Right_ParenAutomaton.h"
#include "MultiplyAutomaton.h"
#include "AddAutomaton.h"
#include "SchemesAutomaton.h"
#include "FactsAutomaton.h"
#include "RulesAutomaton.h"
#include "QueriesAutomaton.h"
#include "IdAutomaton.h"
#include "StringAutomaton.h"
#include "CommentAutomaton.h"
#include "UndefinedAutomaton.h"
#include "EOFAutomaton.h"

using namespace std;

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    // TODO: need to clean up the memory in `automata` and `tokens`
}

void Lexer::CreateAutomata() {
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    automata.push_back(new PeriodAutomaton());
    automata.push_back(new CommaAutomaton());
    automata.push_back(new Q_MarkAutomaton());
    automata.push_back(new Left_ParenAutomaton());
    automata.push_back(new Right_ParenAutomaton());
    automata.push_back(new MultiplyAutomaton());
    automata.push_back(new AddAutomaton());
    automata.push_back(new SchemesAutomaton());
    automata.push_back(new FactsAutomaton());
    automata.push_back(new RulesAutomaton());
    automata.push_back(new QueriesAutomaton());
    automata.push_back(new IdAutomaton());
    automata.push_back(new StringAutomaton());
    automata.push_back(new CommentAutomaton());
    automata.push_back(new UndefinedAutomaton());
    automata.push_back(new EOFAutomaton());
}

void Lexer::Run(std::string& input) {
    // TODO: convert this pseudo-code with the algorithm into actual C++ code

    int lineNum = 1;

    // While there are more characters to tokenize

    while(!input.empty()){

        int maxRead = 0;
        Automaton* maxAutomaton = automata.at(0);

        for(unsigned int i = 0; i < automata.size(); i++) {
            int numRead = automata.at(i)->Start(input);

            if (numRead > maxRead) {
                maxRead = numRead;
                maxAutomaton = automata.at(i);
            }
        }

        if (maxRead > 0) {
            Token* newToken = maxAutomaton->CreateToken(input.substr(0, maxRead), lineNum);
            lineNum = lineNum + maxAutomaton->NewLinesRead();
            tokens.push_back(newToken);
        } else if (input.at(0) == '\n'){
            lineNum++;
            maxRead = 1;
        } else if (isspace(input.at(0))){
            maxRead = 1;
        } else {
            maxRead = 1;
        }

        //testing if substr does what its supposed too
        /*
        if(maxRead <= input.size()){
            input = input.substr(maxRead);
        }
        */
        input = input.substr(maxRead);
    }
    //add end of file token to all tokens
    Token* eofToken = new Token(TokenType::ENDOFFILE, "", lineNum);
    tokens.push_back(eofToken);
}

string Lexer::toString() {
    string output = "";

    //its showing symbols because

    for(unsigned int i = 0; i < tokens.size(); i++){
        output.push_back('(');
        output.append((tokens.at(i)->getType()) + ',' + '"');
        output.append(tokens.at(i)->getVal() + '"' + ',');
        output += to_string(tokens.at(i)->getLine());
        output.append(")\n");
    }

    output.append("Total Tokens = ");
    output += to_string(tokens.size());

    return output;
}
