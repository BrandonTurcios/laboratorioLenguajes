#include "parser.h"
#include "iostream"
Parser::Parser() {}
Parser::Parser(std::vector<Token> Tokens) { this->Tokens = Tokens; }
Token Parser::preveiewNext() {
  try {
    if (Tokens.size() <= 1) {
      throw std::out_of_range("Not enough elements in the vector");
    }
    Token element = Tokens[1];
    return element;
  } catch (const std::out_of_range &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return Token();
    exit(1);
  }
}

Token Parser::getNextToken() {

  try {
    if (Tokens.empty()) {
      throw std::out_of_range("No elements in the vector");
      exit(1);
    }

    Token element = Tokens[0];
    Tokens.erase(Tokens.begin());
    std::cout << "Current Token:  " << curr_token.value << std::endl;
    return element;
  } catch (const std::out_of_range &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    exit(1);
    return Token();
  }
}
bool Parser::defun() {
  if (curr_token.type == Identifier) {
    curr_token = getNextToken();
  } else {
    std::cout << "Error defun is waiting an identifier type not valid ="
              << curr_token.value << std::endl;
    exit(1);
  }
  if (params()) {
    curr_token = getNextToken();
  }
  // Body de la funcion
  if (curr_token.type == OpenParen) {
    curr_token = getNextToken();
    s_expression();

  } else {
  }

  return true;
}

bool Parser::algebraic_expression(){
  //En lisp no existen las expresion algebracias si que los oepradores son funciones
  //+ / * son funciones que se puede llamar.
  /*if(curr_token.type==Operator){
    curr_token=getNextToken();
  
  }else{
    std::cout<<"Error no es un expresion algebraica"<<curr_token.value<<"\n";
    return false;
  }*/
  //las funciones que retornar valores numericos se pueden anidar entonces:
  while(curr_token.type!=CloseParen){
    if(curr_token.type==OpenParen){
       curr_token=getNextToken();
       s_expression();
    }else if( curr_token.type==Number||curr_token.type==Identifier){
       curr_token=getNextToken();

    }else{
      return false;
    }
  }
  /*
    Una funcion numerica tambien puede tenre otras funciones que no sean operadores peor como identificadores y demas
    //pero esta es para expresion base
  */

  return true;
}
bool Parser::eval_list_backquote() {
  //EVALIST BACKQUOTE DEBE ACEPTAR LA MAYORIA DE TIPOS 
  //Esto se debe a que el backquote loq u hace es pasarlo a un literal
  if (curr_token.type == Identifier || curr_token.type == Macro ||
      curr_token.type == ReservedWord || curr_token.type ||
      curr_token.type == Operator || true) {
    // curr_token=getNextToken();
    while (curr_token.type != CloseParen) {
      if (curr_token.type == OpenParen) {
        curr_token = getNextToken();
        eval_list_backquote();
        curr_token = getNextToken();
      } else {
        curr_token = getNextToken();
      }
    }

  } else {

    // error
    std::cout << "Ha ocurrido un erro evaluando apr de la expression ="
              << curr_token.value << std::endl;
    exit(1);
  }

  return true;
}
bool Parser::eval_list() {
  /*La evalaucion de la lista solo se asegura que se siga la estructura de 
  s_expression=(atomic_simbol....s_expression)
  donde cualquiere lista debe empezar con un atomic_symbol*/
   std::cout
            << "El token es  ="
            << curr_token.value << std::endl;
  if (curr_token.type == Identifier || curr_token.type == Macro ||
      curr_token.type == ReservedWord||
      curr_token.type == Operator) {
      curr_token = getNextToken();
    
    while (curr_token.type != CloseParen) {
      if (curr_token.type == String || curr_token.type == Identifier ||
          curr_token.type == Number || curr_token.type == ReservedWord) {
        curr_token = getNextToken();

      } else if (curr_token.type == OpenParen) {
        /*En algunos casos puede existir un parentesis
        osea un s_expresion dentro de la lista por lo que se requiere
        de evaluarla completamente...
        param tampoco empieza con un simbolo*/
        curr_token = getNextToken();
        eval_list();
        curr_token = getNextToken();
      } else {
        std::cout
            << "Ha ocurrido un erro en  la expression dentro de la lista ="
            << curr_token.value << std::endl;
        exit(1);
      }
    }

  } else {

    // error
    std::cout << "Ha ocurrido un erro evaluando apr de la expression ="
              << curr_token.value << std::endl;
    exit(1);
  }

  return true;
}

bool Parser::params(){
    // Este codigo evalua una lista de parametros
  //Los parametros puede esrcibirse la siguiente forma
  // (atomic_symbol ...atomic_symbol), todo eso es valido
  // Este codigo evalua una lista de parametros
  //Los parametros puede esrcibirse la siguiente forma
  // (s_expressions...), todo eso es valido
  //Ya no se ne necesita recursion ese es que se utliza par aevaluar defun 
  if (curr_token.type == OpenParen) {
    curr_token = getNextToken();
    if (curr_token.type == Identifier) {
      while (curr_token.type != CloseParen) {
        if (curr_token.type == Identifier) {
          curr_token = getNextToken();
        } else {
          //
          std::cout << "Error se esperamba que na la lista solo existan "
                       "definiciones de parametros = "
                    << curr_token.value << std::endl;
          exit(1);
        }
      }
      // Termino
      // rest is an S_Expression
    } else {
      std::cout << "lo que se que sea ese toquyen no es un argumento =  "
                << curr_token.value << std::endl;
      exit(1);
    }
  }
  return true;
}
bool Parser::macro_params() {

  // Este codigo evalua una lista de parametros
  //Los parametros puede esrcibirse la siguiente forma
  // (s_expressions...), todo eso es valido
  if (curr_token.type == OpenParen) {
    curr_token = getNextToken();
    if (curr_token.type == Identifier || curr_token.type == OpenParen) {
      while (curr_token.type != CloseParen) {
        if (curr_token.type == Identifier) {
          curr_token = getNextToken();

        } else if (curr_token.type == OpenParen) {
          macro_params();
          if (curr_token.type == CloseParen) {
            curr_token = getNextToken();
          }
        } else {
          //
          std::cout << "Error se esperamba que na la lista solo existan "
                       "definiciones de parametros = "
                    << curr_token.value << std::endl;
          exit(1);
        }
      }
      // Termino
      // rest is an S_Expression

    } else if (curr_token.type == OpenParen) {
      macro_params();
      //

    } else {
      std::cout << "lo que se que sea ese toquyen no es un argumento =  "
                << curr_token.value << std::endl;
      exit(1);
    }
  }
  return true;
}
bool Parser::params_backquote() {

  // Este codigo evalua una lista de parametros
  if (curr_token.type == OpenParen) {
    curr_token = getNextToken();
    if (curr_token.type == Identifier || curr_token.type == OpenParen ||
        curr_token.type == Comma || curr_token.type == Operator || true) {
      while (curr_token.type != CloseParen) {
        if (curr_token.type == Identifier || curr_token.type == Comma || true) {
          curr_token = getNextToken();

        } else if (curr_token.type == OpenParen) {
          params_backquote();
          if (curr_token.type == CloseParen) {
            curr_token = getNextToken();
          }
        } else {
          //
          std::cout << "Error se esperamba que na la lista solo existan "
                       "definiciones de parametros = "
                    << curr_token.value << std::endl;
          exit(1);
        }
      }
      // Termino
      // rest is an S_Expression

    } else if (curr_token.type == OpenParen) {
      params_backquote();

    } else {
      std::cout << "lo que se que sea ese toquyen no es un argumento Bquote =  "
                << curr_token.value << std::endl;
      exit(1);
    }

  } else {
    std::cout << "lo que se que sea ese toquyen no es un argumento Bquote =  "
              << curr_token.value << std::endl;
    exit(1);
  }
  return true;
}


bool Parser::conditions(){
  return true;
}
    
bool Parser::s_expression() {
  // despues de un (
  if (curr_token.type == Macro) {
    if (curr_token.value == "DEFUN") {
      curr_token = getNextToken();
      defun();
      curr_token = getNextToken();
    }
    // Palabras reservadas
  } else if (curr_token.type == ReservedWord) {
    if (curr_token.value == "DEFMACRO") {
      curr_token = getNextToken();
      def_macro();
      // curr_token=getNextToken();

    } else if (curr_token.value == "DO") {
      std::cout << "Evaluando do \n";
      curr_token = getNextToken();
      iterator_do();
      //  curr_token=getNextToken();

    } else {
      eval_list();
    }
  } else if(curr_token.type==Operator){
    curr_token=getNextToken();
    algebraic_expression();
  
  }else if (curr_token.type == Identifier) {

    eval_list();


  } else {
    eval_list();
  }

  std::cout << "End   " << curr_token.value << "\n";

  return true;
}

bool Parser::number() {
  if (curr_token.type == Number ||curr_token.type==Identifier||curr_token.type ==Operator) {
    curr_token = getNextToken();
  } else if(curr_token.type==OpenParen) {
    // Cualquier lista vlaida que retorne un numero se sabe que lo retorna por
    // la deifnicon de la funcion.

    curr_token = getNextToken();
    s_expression();
    curr_token = getNextToken();
    // Eval aritmetica....
  }else{
  std::cout << "Se espera una expresion aritmetcia o un numer : "
                      << curr_token.value << "\n";
            exit(1);
  }
  return true;
}
bool Parser::iterator_do() {
  if (curr_token.type == OpenParen) { 
    curr_token = getNextToken();
    if (curr_token.type == OpenParen) {
      curr_token = getNextToken();
      if (curr_token.type == Identifier) {
        curr_token = getNextToken();
        number();


        if (curr_token.type == OpenParen) {
           curr_token = getNextToken();
           number();
      
          if (curr_token.type == Identifier) {
            curr_token = getNextToken();
            // No opcional
          } else {
            std::cout << "Errro No hya valor de incremento 5 "
                      << curr_token.value << "\n";
            exit(1);
          }
        curr_token = getNextToken();
        curr_token = getNextToken();
          

        } else {
          std::cout << "Faltan Argumentos en el do 3: " << curr_token.value
                    << "\n";
          exit(1);
        }

      } else {
        std::cout << "Faltan Argumentos en el do 2" << curr_token.value << "\n";
        exit(1);
      }
    } else {
      std::cout << "Faltan Argumentos en el do 1" << curr_token.value << "\n";
      exit(1);
    }
  } else {

    std::cout << "Erro en ciclo Do faltan parametros (arg.. arga2..)"
              << curr_token.value << std::endl;
    exit(1);
  }
  
   curr_token = getNextToken();
    std::cout << "Faltan Argumentos en el do 1" << curr_token.value << "\n";
  if (curr_token.type == OpenParen) {
    eval_list_backquote();
    curr_token = getNextToken();

  } else {
  }
  return true;
}
bool Parser::def_macro() {
  if (curr_token.type == Identifier) {
    curr_token = getNextToken();
  } else {
    std::cout << "Error defun is waiting an identifier type not valid ="
              << curr_token.value << std::endl;
    exit(1);
  }
  macro_params();
  curr_token = getNextToken();

  if (curr_token.value == "`") {
    curr_token = getNextToken();
    eval_list_backquote();

  } else {
    std::cout << "Error en la defincion de defmacro, se espera Body = "
              << curr_token.value << std::endl;
  }

  return true;
}
void Parser::start() {
  curr_token = getNextToken();
  while (Tokens.size() > 0) {
    // std::cout<<"Current Token:  "<<curr_token.value<<std::endl;
    if (curr_token.type == OpenParen) {
      curr_token = getNextToken();
      s_expression();
      curr_token = getNextToken();
    } else {
      std::cout << "Ha ocurriod un erro talvaez la expresion no comenzo con ("
                << curr_token.value << std::endl;
      exit(1);
    } //
  }

  if (curr_token.type != CloseParen) {
    std::cout << "Ha ocurriod un erro talvaez la expresion no comenzo con ("
              << curr_token.value << std::endl;
    exit(1);
  }
}