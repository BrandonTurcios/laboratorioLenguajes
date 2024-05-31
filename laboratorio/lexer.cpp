//#include <iostream>
//#include <string>
//#include <vector>
//#include <cctype>
//#include <fstream>
//#include <sstream>
//#include <cstdlib>
//
//using namespace std;
//// Definir los tipos de tokens
//enum TokenType
//{
//    Number,
//    Identifier,
//    OpenParen,
//    CloseParen,
//    PalabraReservada,
//    Operador,
//    Comment,
//    String,
//    Macro,
//    Quote,
//    Comma,
//    Backquote,
//    Colon // Nuevo tipo de token para el delimitador de dos puntos
//};
//
//// Estructura para los tokens
//struct Token
//{
//    std::string value;
//    TokenType type;
//};
//
//vector<pair<string, TokenType>> reservedWords = {
//    {"ABS", PalabraReservada}, {"ACONS", PalabraReservada}, {"ACOS", PalabraReservada}, {"Alt-A", PalabraReservada},
//    {"Alt-D", PalabraReservada}, {"Alt-H", PalabraReservada}, {"Alt-K", PalabraReservada}, {"AND", PalabraReservada},
//    {"APPEND", PalabraReservada}, {"APPLY", PalabraReservada}, {"ASIN", PalabraReservada}, {"ASSOC", PalabraReservada},
//    {"ATAN", PalabraReservada}, {"ATOM", PalabraReservada}, {"BUTLAST", PalabraReservada}, {"CAR", PalabraReservada},
//    {"CASE", PalabraReservada}, {"CDR", PalabraReservada}, {"CLOSE", PalabraReservada}, {"COND", PalabraReservada},{"CONCATENATE", PalabraReservada},
//    {"CONS", PalabraReservada}, {"CONSP", PalabraReservada}, {"Control-C", PalabraReservada}, {"Control-D", PalabraReservada},
//    {"Control-E", PalabraReservada}, {"Control-L", PalabraReservada}, {"Control-Pausa", PalabraReservada},
//    {"COPY-LIST", PalabraReservada}, {"COS", PalabraReservada}, {"DEFUN", PalabraReservada}, {"DELETE", PalabraReservada},{"DEFMACRO", PalabraReservada},
//    {"DESCRIBE", PalabraReservada}, {"DO", PalabraReservada}, {"DO*", PalabraReservada}, {"DOLIST", PalabraReservada},
//    {"DOS", PalabraReservada}, {"DOTIMES", PalabraReservada}, {"DRIBBLE", PalabraReservada}, {"EQ", PalabraReservada},
//    {"EQUAL", PalabraReservada}, {"EVAL", PalabraReservada}, {"EVENP", PalabraReservada}, {"EVERY", PalabraReservada},
//    {"EXIT", PalabraReservada}, {"EXP", PalabraReservada}, {"EXPT", PalabraReservada}, {"FIRST", PalabraReservada},
//    {"FORMAT", PalabraReservada},{"FOR", PalabraReservada}, {"FROM", PalabraReservada} ,{"FUNCALL", PalabraReservada},
//    {"GET", PalabraReservada}, {"GO", PalabraReservada}, {"IF", PalabraReservada}, {"IFN", PalabraReservada}, {"LAMBDA", PalabraReservada}, {"LAST", PalabraReservada},
//    {"LENGTH", PalabraReservada}, {"LET", PalabraReservada}, {"LET*", PalabraReservada}, {"LIST", PalabraReservada},
//    {"LIST*", PalabraReservada}, {"LISTP", PalabraReservada}, {"LOAD", PalabraReservada}, {"LOG", PalabraReservada},
//    {"LOOP", PalabraReservada}, {"MAKE-LIST", PalabraReservada}, {"MAKUNBOUND", PalabraReservada}, {"MAPC", PalabraReservada},
//    {"MAPCAR", PalabraReservada}, {"MAPLIST", PalabraReservada}, {"MAX", PalabraReservada}, {"MEMBER", PalabraReservada},
//    {"MIN", PalabraReservada}, {"MINUSP", PalabraReservada}, {"MOD", PalabraReservada}, {"NCONC", PalabraReservada},
//    {"NIL", PalabraReservada}, {"NOT", PalabraReservada}, {"NTH", PalabraReservada}, {"NTHCDR", PalabraReservada},
//    {"NULL", PalabraReservada}, {"NUMBERP", PalabraReservada}, {"ODDP", PalabraReservada}, {"OPEN", PalabraReservada},
//    {"OR", PalabraReservada}, {"PAIRLIS", PalabraReservada}, {"PLUSP", PalabraReservada}, {"PRIN1", PalabraReservada},
//    {"PRINC", PalabraReservada}, {"PRINT", PalabraReservada}, {"PROG", PalabraReservada}, {"PROG1", PalabraReservada},{"PUSH", PalabraReservada},
//    {"PROG2", PalabraReservada}, {"PROGN", PalabraReservada}, {"QUOTE", PalabraReservada}, {"RASSOC", PalabraReservada},
//    {"READ", PalabraReservada}, {"READ-LINE", PalabraReservada}, {"REMOVE", PalabraReservada}, {"REMPROP", PalabraReservada},
//    {"REST", PalabraReservada}, {"RETURN", PalabraReservada}, {"REVERSE", PalabraReservada}, {"RPLACA", PalabraReservada},
//    {"RPLACD", PalabraReservada}, {"SECOND", PalabraReservada}, {"SET", PalabraReservada}, {"SETQ", PalabraReservada},
//    {"SIN", PalabraReservada}, {"SOME", PalabraReservada}, {"SQRT", PalabraReservada}, {"STEP", PalabraReservada},
//    {"SUBLIS", PalabraReservada}, {"SUBST", PalabraReservada}, {"SYMBOL-FUNCTION", PalabraReservada},
//    {"SYMBOL-NAME", PalabraReservada}, {"SYMBOL-PLIST", PalabraReservada}, {"SYMBOL-PLIST", PalabraReservada},
//    {"SYMBOL-PLIST", PalabraReservada}, {"SYMBOL-VALUE", PalabraReservada}, {"SYMBOLP", PalabraReservada},
//    {"T", PalabraReservada}, {"TAN", PalabraReservada}, {"TERPRI", PalabraReservada}, {"THIRD", PalabraReservada},
//    {"TIME", PalabraReservada}, {"TRACE", PalabraReservada}, {"UNLESS", PalabraReservada}, {"UNTRACE", PalabraReservada},
//    {"WHEN", PalabraReservada}, {"WITH-OPEN-FILE", PalabraReservada}, {"ZEROP", PalabraReservada}
//};
//
//const vector<pair<string, TokenType>> operators = {
//    {"+", Operador}, {"-", Operador}, {"*", Operador}, {"/", Operador}, {"/=", Operador},
//    {"=", Operador}, {">=", Operador}, {"<=", Operador}, {">", Operador}, {"<", Operador},
//    {"1+", Operador}
//};
//
//
//// Función para verificar si una cadena es un número
//bool isNumber(const std::string& str)
//{
//    for (char ch : str)
//    {
//        if (!isdigit(ch))
//            return false;
//    }
//    return true;
//}
//
//// Función para identificar el tipo de token
//TokenType identifyToken(const std::string& str)
//{
//    // Verificar si la palabra es una palabra reservada
//    for (const auto& pair : reservedWords)
//    {
//        if (str == pair.first)
//            return pair.second;
//    }
//
//    // Verificar si es un operador
//    for (const auto& pair : operators)
//    {
//        if (str == pair.first)
//            return pair.second;
//    }
//
//    // Si no es una palabra reservada, un operador, ni un número, considerarla un identificador
//    if (isNumber(str))
//        return Number;
//
//    return Identifier;
//}
//
//// Función para manejar cadenas y comentarios
//std::string extractToken(std::stringstream& sourceStream, char delimiter)
//{
//    std::string token;
//    std::getline(sourceStream, token, delimiter);
//    return token;
//}
//
//// Función para convertir el tipo de token a una cadena
//std::string tokenTypeToString(TokenType type)
//{
//    switch (type)
//    {
//    case Number: return "Number";
//    case Identifier: return "Identifier";
//    case OpenParen: return "OpenParen";
//    case CloseParen: return "CloseParen";
//    case PalabraReservada: return "PalabraReservada";
//    case Operador: return "Operador";
//    case Comment: return "Comment";
//    case String: return "String";
//    case Macro: return "Macro";
//    case Quote: return "Quote";
//    case Comma: return "Comma";
//    case Backquote: return "Backquote";
//    case Colon: return "Colon"; // Agregado para representar el delimitador de dos puntos
//    default: return "Unknown";
//    }
//}
//
//// Función para tokenizar el código fuente
//std::vector<Token> tokenize(const std::string& sourceCode)
//{
//    std::vector<Token> tokens;
//    std::stringstream sourceStream(sourceCode);
//    char ch;
//
//    while (sourceStream.get(ch))
//    {
//        if (ch == '(')
//        {
//            tokens.push_back({ "(", OpenParen });
//        }
//        else if (ch == ')')
//        {
//            tokens.push_back({ ")", CloseParen });
//        }
//        else if (ch == ';')
//        {
//            std::string comment = extractToken(sourceStream, '\n');
//            tokens.push_back({ ";" + comment, Comment });
//        }
//        else if (ch == '"')
//        {
//            std::string str = extractToken(sourceStream, '"');
//            tokens.push_back({ "\"" + str + "\"", String });
//        }
//        else if (ch == '\'')
//        {
//            tokens.push_back({ "'", Quote });
//        }
//        else if (ch == ',')
//        {
//            tokens.push_back({ ",", Comma });
//        }
//        else if (ch == '`')
//        {
//            tokens.push_back({ "`", Backquote });
//        }
//        else if (ch == ':')
//        {
//            tokens.push_back({ ":", Colon });
//            std::string token;
//            while (sourceStream.peek() != EOF && !isspace(sourceStream.peek()) && sourceStream.peek() != '(' && sourceStream.peek() != ')' && sourceStream.peek() != ',' && sourceStream.peek() != ';' && sourceStream.peek() != '`' && sourceStream.peek() != ':')
//            {
//                token += sourceStream.get();
//            }
//            if (!token.empty())
//            {
//                TokenType type = identifyToken(token);
//                tokens.push_back({ token, type });
//            }
//        }
//        else if (!isspace(ch))
//        {
//            std::string token(1, ch);
//            while (sourceStream.peek() != EOF && !isspace(sourceStream.peek()) && sourceStream.peek() != '(' && sourceStream.peek() != ')' && sourceStream.peek() != ',' && sourceStream.peek() != ';' && sourceStream.peek() != '`' && sourceStream.peek() != ':')
//            {
//                token += sourceStream.get();
//            }
//            TokenType type = identifyToken(token);
//            tokens.push_back({ token, type });
//        }
//    }
//
//    return tokens;
//}
//
//int main()
//{
//    // Solicitar al usuario el nombre del archivo de entrada
//    std::string fileName;
//    std::cout << "Ingrese el nombre del archivo de entrada: ";
//    std::cin >> fileName;
//
//    // Leer el archivo de entrada y convertirlo en una cadena
//    std::string sourceCode;
//    {
//        std::stringstream contents_stream;
//        std::ifstream input(fileName, std::ios::in);
//        if (!input)
//        {
//            std::cerr << "No se pudo abrir el archivo!" << std::endl;
//            return EXIT_FAILURE;
//        }
//        contents_stream << input.rdbuf();
//        sourceCode = contents_stream.str();
//    }
//
//    // Tokenizar el código fuente
//    std::vector<Token> tokens = tokenize(sourceCode);
//
//    // Imprimir los tokens
//    for (const Token& token : tokens)
//    {
//        std::cout << "Value: " << token.value << "   Type: " << tokenTypeToString(token.type) << std::endl;
//    }
//
//    return 0;
//}
