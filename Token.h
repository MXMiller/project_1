#ifndef TOKEN_H
#define TOKEN_H
#include <string>

using namespace std;

enum class TokenType {
    COLON,
    COLON_DASH,
    PERIOD,
    COMMA,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    COMMENT,
    ENDOFFILE,
    UNDEFINED
};

class Token
{
private:
    TokenType t;
    string value;
    int lineNum = 0;

public:
    Token(TokenType type, std::string description, int line);

    string getType();
    TokenType getTokenType();
    string getVal();
    int getLine();
};

#endif // TOKEN_H

