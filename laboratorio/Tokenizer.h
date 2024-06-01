#pragma once
#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>

// Definir los tipos de tokens
enum TokenType
{
    Number,
    Identifier,
    OpenParen,
    CloseParen,
    ReservedWord,
    Operator,
    Comment,
    String,
    Macro,
    Quote,
    Comma,
    Backquote,
    Colon
};

// Estructura para los tokens
struct Token
{
    std::string value;
    TokenType type;
};

class Tokenizer
{
public:
    Tokenizer();
    std::vector<Token> tokenize(const std::string& sourceCode);
    std::string tokenTypeToString(TokenType type);
    std::vector<std::pair<std::string, std::string>> getTokenList(const std::vector<Token>& tokens);


private:
    std::vector<std::pair<std::string, TokenType>> reservedWords;
    std::vector<std::pair<std::string, TokenType>> operators;

    bool isNumber(const std::string& str);
    TokenType identifyToken(const std::string& str);
    std::string extractToken(std::stringstream& sourceStream, char delimiter);
};

#endif // TOKENIZER_H
