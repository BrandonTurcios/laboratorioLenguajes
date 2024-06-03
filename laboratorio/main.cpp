#include <iostream>
#include <fstream>
#include <sstream>
#include "Tokenizer.h"
#include "parser.h"
Token preveiewNext(std::vector<Token> & vect){
    Token element= vect[1];
    return element;


}

Token getNextToken(std::vector<Token> & vect){


    Token element=vect[0];
    vect.pop_back();
    return element;


}


int main()
{
    // Solicitar al usuario el nombre del archivo de entrada
    std::string fileName;
    std::cout << "Ingrese el nombre del archivo de entrada: ";
    std::cin >> fileName;

    // Leer el archivo de entrada y convertirlo en una cadena
    std::string sourceCode;
    {
        std::stringstream contents_stream;
        std::ifstream input(fileName, std::ios::in);
        if (!input)
        {
            std::cerr << "No se pudo abrir el archivo!" << std::endl;
            return EXIT_FAILURE;
        }
        contents_stream << input.rdbuf();
        sourceCode = contents_stream.str();
    }

    // Crear una instancia de Tokenizer
    Tokenizer tokenizer;

    // Tokenizar el c�digo fuente
    std::vector<Token> tokens = tokenizer.tokenize(sourceCode);

    // Obtener la lista de tokens con valores y tipos
    std::vector<std::pair<std::string, std::string>> tokenList = tokenizer.getTokenList(tokens);

    Parser parser=Parser(tokens);

    // Imprimir los tokens
    for (const auto& token : tokens)
    {
        std::cout<<"Type: "<< token.type<<"  value: "<<token.value<<std::endl;
        
       // std::cout << "Value: " << token.first << "   Type: " << token.second << std::endl;

    }
    parser.start();

    return 0;
}
