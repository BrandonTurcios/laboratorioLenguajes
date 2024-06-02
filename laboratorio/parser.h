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
    bool def_macro();
    bool params();
    bool iterator_do();
    bool eval_list_backquote();
    void start();
    bool number();
    bool params_backquote();
    bool algebraic_expression();
    bool conditions();
    
    Token preveiewNext();
    Token getNextToken();
    

private:
    std::vector<Token> Tokens;
    Token curr_token;
    bool defun();
    bool eval_list();
    
};

#endif // TOKENIZER_H
