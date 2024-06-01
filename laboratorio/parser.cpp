#include "parser.h"
#include "iostream"
Parser::Parser(){

}
Parser::Parser(std::vector<Token> Tokens){
    this->Tokens=Tokens;


    
}
Token Parser::preveiewNext(){
     try {
        if (Tokens.size() <= 1) {
            throw std::out_of_range("Not enough elements in the vector");
        }
        Token element = Tokens[1];
        return element;
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return Token(); 
    }


}

Token Parser::getNextToken(){
    
    try {
        if (Tokens.empty()) {
            throw std::out_of_range("No elements in the vector");
        }
        std::cout<<"Current Token:  "<<curr_token.value<<std::endl;
        Token element = Tokens[0];
        Tokens.erase(Tokens.begin());
        return element;
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return Token();
    }


}
bool Parser::defun(){
    if(curr_token.type==Identifier){
        curr_token=getNextToken();
    }else{
        std::cout<<"Error defun is waiting an identifier type not valid =" <<curr_token.value<<std::endl;
        exit(1);
    }
    //Este codigo evalua una lista de parametros
    if(curr_token.type==OpenParen){
        curr_token=getNextToken();
        if(curr_token.type==Identifier){
            while(curr_token.type!=CloseParen){
                if(curr_token.type==Identifier){
                    curr_token=getNextToken();

                }else{
                    //
                     std::cout<<"Error se esperamba que na la lista solo existan definiciones de parametros = "<<curr_token.value<<std::endl;
                    exit(1);
                }
            }
            //Termino
            //rest is an S_Expression

        }else{
            //lo que se que sea ese toquyen no es un argumento.
           std::cout<<"lo que se que sea ese toquyen no es un argumento =  "<<curr_token.value<<std::endl;
                    exit(1);
        }

           
        
 
    }
    return true;

}
bool Parser::s_expression(){
    //despues de un (
    if(curr_token.type==Macro){
        if(curr_token.value=="DEFUN"){
            curr_token=getNextToken();
            defun();
            curr_token=getNextToken();
            if(curr_token.type==CloseParen){
                curr_token=getNextToken();
                
            }


            
        }
    }else if(curr_token.type==Identifier){
        curr_token=getNextToken();

    }else{
        std::cout<<"Symbol Error Expression shosudl star with a symbol = "<<curr_token.value<<std::endl;
         exit(1);
        
    }

    std::cout<<"End";
    return true;
  

}

void Parser::start(){
    curr_token=getNextToken();
    if(curr_token.type==OpenParen){
        curr_token=getNextToken();
        s_expression();
        
    }
}