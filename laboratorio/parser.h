#pragma once
#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include "Tokenizer.h"
// Estructura para los tokens

class Parser
{
public:
    Parser();
    Parser(std::vector<Token> Tokens);
    bool s_expression();
    void start();
    Token preveiewNext();
    Token getNextToken();
    

private:
    std::vector<Token> Tokens;
    Token curr_token;
    bool defun();
    bool eval_list();
    
};

#endif // TOKENIZER_H
