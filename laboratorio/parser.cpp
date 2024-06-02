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
   
        Token element = Tokens[0];
        Tokens.erase(Tokens.begin());
        std::cout<<"Current Token:  "<<curr_token.value<<std::endl;
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
    if(params()){
        curr_token=getNextToken();
    }
    if(curr_token.type==OpenParen){
        curr_token=getNextToken();
        eval_list();
    
    }else{

    }
   

    return true;

}
bool Parser::eval_list_backquote(){
 if(curr_token.type==Identifier||curr_token.type==Macro||curr_token.type==ReservedWord||curr_token.type||curr_token.type==Operator||true){
        //curr_token=getNextToken();
        while(curr_token.type!=CloseParen){
            if(curr_token.type==OpenParen){
                curr_token=getNextToken();
                eval_list_backquote();
                curr_token=getNextToken();
            }else{
                curr_token=getNextToken();
            }
         
        }

    }else{

        //error
        std::cout<<"Ha ocurrido un erro evaluando apr de la expression ="<<curr_token.value<<std::endl;
        exit(1);
    }
        
    return true;

}
bool Parser::eval_list(){
    if(curr_token.type==Identifier||curr_token.type==Macro||curr_token.type==ReservedWord||curr_token.type||curr_token.type==Operator){
        curr_token=getNextToken();
        while(curr_token.type!=CloseParen){
            if(curr_token.type==String||curr_token.type==Identifier||curr_token.type==Number||curr_token.type==ReservedWord){
                curr_token=getNextToken();

            }else if(curr_token.type==OpenParen){
                curr_token=getNextToken();
                eval_list();
                curr_token=getNextToken();
            }else{
                 std::cout<<"Ha ocurrido un erro en  la expression dentro de la lista ="<<curr_token.value<<std::endl;
                 exit(1);
                
            }
        }

    }else{

        //error
        std::cout<<"Ha ocurrido un erro evaluando apr de la expression ="<<curr_token.value<<std::endl;
        exit(1);
    }
        
    return true;


}
bool Parser::params(){

    //Este codigo evalua una lista de parametros
    if(curr_token.type==OpenParen){
        curr_token=getNextToken();
        if(curr_token.type==Identifier || curr_token.type==OpenParen){
            while(curr_token.type!=CloseParen){
                if(curr_token.type==Identifier){
                    curr_token=getNextToken();

                }else if(curr_token.type==OpenParen){
                    params();
                    if(curr_token.type==CloseParen){
                        curr_token=getNextToken();
                    }
                }
                else{
                    //
                     std::cout<<"Error se esperamba que na la lista solo existan definiciones de parametros = "<<curr_token.value<<std::endl;
                    exit(1);
                }
            }
            //Termino
            //rest is an S_Expression

        }else if (curr_token.type==OpenParen){
            params();
       
        }else{
                std::cout<<"lo que se que sea ese toquyen no es un argumento =  "<<curr_token.value<<std::endl;
                exit(1);
        }
        
 
    }
    return true;
}
bool Parser::params_backquote(){

    //Este codigo evalua una lista de parametros
    if(curr_token.type==OpenParen){
        curr_token=getNextToken();
        if(curr_token.type==Identifier || curr_token.type==OpenParen||curr_token.type==Comma||curr_token.type==Operator||true){
            while(curr_token.type!=CloseParen){
                if(curr_token.type==Identifier||curr_token.type==Comma||true){
                    curr_token=getNextToken();

                }else if(curr_token.type==OpenParen){
                    params_backquote();
                    if(curr_token.type==CloseParen){
                        curr_token=getNextToken();
                    }
                }
                else{
                    //
                     std::cout<<"Error se esperamba que na la lista solo existan definiciones de parametros = "<<curr_token.value<<std::endl;
                    exit(1);
                }
            }
            //Termino
            //rest is an S_Expression

        }else if (curr_token.type==OpenParen){
            params_backquote();
       
        }else{
                std::cout<<"lo que se que sea ese toquyen no es un argumento Bquote =  "<<curr_token.value<<std::endl;
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
            
        }
        //Palabras reservadas
    }else if(curr_token.type==ReservedWord){
        if(curr_token.value=="DEFMACRO"){
            curr_token=getNextToken();
            def_macro();
            //curr_token=getNextToken();
       
        }else if(curr_token.value=="DO"){
            std::cout<<"Evaluando do \n";
            curr_token=getNextToken();
            iterator_do();
            curr_token=getNextToken();
            
            
        }
    }else if(curr_token.type==Identifier){
        curr_token=getNextToken();

    
    }else{
       eval_list();

        
    }

    std::cout<<"End";
    return true;
  

}
bool Parser::iterator_do(){
    if(curr_token.type==OpenParen){
        params();
        curr_token=getNextToken();
    }else{
    
        std::cout<<"Erro en ciclo Do faltan parametros (arg.. arga2..)"<<curr_token.value<<std::endl;
    }
    if(curr_token.type==OpenParen){
    
        curr_token=getNextToken();
        eval_list();
        

    }else{

    }
    return true;

}
bool Parser::def_macro(){
    if(curr_token.type==Identifier){
            curr_token=getNextToken();
    }else{
        std::cout<<"Error defun is waiting an identifier type not valid =" <<curr_token.value<<std::endl;
        exit(1);
    }
    params();
    curr_token=getNextToken();

    if(curr_token.value=="`"){
        curr_token=getNextToken();
        eval_list_backquote();

    }
    else{
        std::cout<<"Error en la defincion de defmacro, se espera Body = " <<curr_token.value<<std::endl;
    }

    return true;
}
void Parser::start(){
    curr_token=getNextToken();
    while (Tokens.size()>0){
        std::cout<<"Current Token:  "<<curr_token.value<<std::endl;
         if(curr_token.type==OpenParen){
            curr_token=getNextToken();
            s_expression();
            curr_token=getNextToken();
         }else{
            std::cout<<"Ha ocurriod un erro talvaez la expresion no comenzo con (" <<curr_token.value<<std::endl;
            exit(1);
         }
        
    }

    

}