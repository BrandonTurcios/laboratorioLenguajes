#include "Tokenizer.h"
#include <cctype>

// Constructor que inicializa las listas de palabras reservadas y operadores
Tokenizer::Tokenizer()
{
    reservedWords = {
        {"ABS", ReservedWord}, {"ACONS", ReservedWord}, {"ACOS", ReservedWord}, {"Alt-A", ReservedWord},
    {"Alt-D", ReservedWord}, {"Alt-H", ReservedWord}, {"Alt-K", ReservedWord}, {"AND", ReservedWord},
    {"APPEND", ReservedWord}, {"APPLY", ReservedWord}, {"ASIN", ReservedWord}, {"ASSOC", ReservedWord},
    {"ATAN", ReservedWord}, {"ATOM", ReservedWord}, {"BUTLAST", ReservedWord}, {"CAR", ReservedWord},
    {"CASE", ReservedWord}, {"CDR", ReservedWord}, {"CLOSE", ReservedWord}, {"COND", ReservedWord},{"CONCATENATE", ReservedWord},
    {"CONS", ReservedWord}, {"CONSP", ReservedWord}, {"Control-C", ReservedWord}, {"Control-D", ReservedWord},
    {"Control-E", ReservedWord}, {"Control-L", ReservedWord}, {"Control-Pausa", ReservedWord},
    {"COPY-LIST", ReservedWord}, {"COS", ReservedWord}, {"DEFUN",Macro}, {"DELETE", ReservedWord},{"DEFMACRO", ReservedWord},
    {"DESCRIBE", ReservedWord}, {"DO", ReservedWord}, {"DO*", ReservedWord}, {"DOLIST", ReservedWord},
    {"DOS", ReservedWord}, {"DOTIMES", ReservedWord}, {"DRIBBLE", ReservedWord}, {"EQ", ReservedWord},
    {"EQUAL", ReservedWord}, {"EVAL", ReservedWord}, {"EVENP", ReservedWord}, {"EVERY", ReservedWord},
    {"EXIT", ReservedWord}, {"EXP", ReservedWord}, {"EXPT", ReservedWord}, {"FIRST", ReservedWord},
    {"FORMAT", ReservedWord},{"FOR", ReservedWord}, {"FROM", ReservedWord} ,{"FUNCALL", ReservedWord},
    {"GET", ReservedWord}, {"GO", ReservedWord}, {"IF", ReservedWord}, {"IFN", ReservedWord}, {"LAMBDA", ReservedWord}, {"LAST", ReservedWord},
    {"LENGTH", ReservedWord}, {"LET", ReservedWord}, {"LET*", ReservedWord}, {"LIST", ReservedWord},
    {"LIST*", ReservedWord}, {"LISTP", ReservedWord}, {"LOAD", ReservedWord}, {"LOG", ReservedWord},
    {"LOOP", ReservedWord}, {"MAKE-LIST", ReservedWord}, {"MAKUNBOUND", ReservedWord}, {"MAPC", ReservedWord},
    {"MAPCAR", ReservedWord}, {"MAPLIST", ReservedWord}, {"MAX", ReservedWord}, {"MEMBER", ReservedWord},
    {"MIN", ReservedWord}, {"MINUSP", ReservedWord}, {"MOD", ReservedWord}, {"NCONC", ReservedWord},
    {"NIL", ReservedWord}, {"NOT", ReservedWord}, {"NTH", ReservedWord}, {"NTHCDR", ReservedWord},
    {"NULL", ReservedWord}, {"NUMBERP", ReservedWord}, {"ODDP", ReservedWord}, {"OPEN", ReservedWord},
    {"OR", ReservedWord}, {"PAIRLIS", ReservedWord}, {"PLUSP", ReservedWord}, {"PRIN1", ReservedWord},
    {"PRINC", ReservedWord}, {"PRINT", ReservedWord}, {"PROG", ReservedWord}, {"PROG1", ReservedWord},{"PUSH", ReservedWord},
    {"PROG2", ReservedWord}, {"PROGN", ReservedWord}, {"QUOTE", ReservedWord}, {"RASSOC", ReservedWord},
    {"READ", ReservedWord}, {"READ-LINE", ReservedWord}, {"REMOVE", ReservedWord}, {"REMPROP", ReservedWord},
    {"REST", ReservedWord}, {"RETURN", ReservedWord}, {"REVERSE", ReservedWord}, {"RPLACA", ReservedWord},
    {"RPLACD", ReservedWord}, {"SECOND", ReservedWord}, {"SET", ReservedWord}, {"SETQ", ReservedWord},
    {"SIN", ReservedWord}, {"SOME", ReservedWord}, {"SQRT", ReservedWord}, {"STEP", ReservedWord},
    {"SUBLIS", ReservedWord}, {"SUBST", ReservedWord}, {"SYMBOL-FUNCTION", ReservedWord},
    {"SYMBOL-NAME", ReservedWord}, {"SYMBOL-PLIST", ReservedWord}, {"SYMBOL-PLIST", ReservedWord},
    {"SYMBOL-PLIST", ReservedWord}, {"SYMBOL-VALUE", ReservedWord}, {"SYMBOLP", ReservedWord},
    {"T", ReservedWord}, {"TAN", ReservedWord}, {"TERPRI", ReservedWord}, {"THIRD", ReservedWord},
    {"TIME", ReservedWord}, {"TRACE", ReservedWord}, {"UNLESS", ReservedWord}, {"UNTRACE", ReservedWord},
    {"WHEN", ReservedWord}, {"WITH-OPEN-FILE", ReservedWord}, {"ZEROP", ReservedWord}
    };

    operators = {
        {"+", Operator}, {"-", Operator}, {"*", Operator}, {"/", Operator}, {"/=", Operator},
    {"=", Operator}, {">=", Operator}, {"<=", Operator}, {">", Operator}, {"<", Operator},
    {"1+", Operator}
    };
}

// Funci�n para verificar si una cadena es un n�mero
bool Tokenizer::isNumber(const std::string& str)
{
    for (char ch : str)
    {
        if (!isdigit(ch))
            return false;
    }
    return true;
}

// Funci�n para identificar el tipo de token
TokenType Tokenizer::identifyToken(const std::string& str)
{
    for (const auto& pair : reservedWords)
    {
        if (str == pair.first)
            return pair.second;
    }

    for (const auto& pair : operators)
    {
        if (str == pair.first)
            return pair.second;
    }

    if (isNumber(str))
        return Number;

    return Identifier;
}

// Funci�n para manejar cadenas y comentarios
std::string Tokenizer::extractToken(std::stringstream& sourceStream, char delimiter)
{
    std::string token;
    std::getline(sourceStream, token, delimiter);
    return token;
}

// Funci�n para convertir el tipo de token a una cadena
std::string Tokenizer::tokenTypeToString(TokenType type)
{
    switch (type)
    {
    case Number: return "Number";
    case Identifier: return "Identifier";
    case OpenParen: return "OpenParen";
    case CloseParen: return "CloseParen";
    case ReservedWord: return "ReservedWord";
    case Operator: return "Operator";
    case Comment: return "Comment";
    case String: return "String";
    case Macro: return "Macro";
    case Quote: return "Quote";
    case Comma: return "Comma";
    case Backquote: return "Backquote";
    case Colon: return "Colon";
    default: return "Unknown";
    }
}

// Funci�n para tokenizar el c�digo fuente
std::vector<Token> Tokenizer::tokenize(const std::string& sourceCode)
{
    std::vector<Token> tokens;
    std::stringstream sourceStream(sourceCode);
    char ch;

    while (sourceStream.get(ch))
    {
        if (ch == '(')
        {
            tokens.push_back({ "(", OpenParen });
        }
        else if (ch == ')')
        {
            tokens.push_back({ ")", CloseParen });
        }
        else if (ch == ';')
        {
            std::string comment = extractToken(sourceStream, '\n');
            tokens.push_back({ ";" + comment, Comment });
        }
        else if (ch == '"')
        {
            std::string str = extractToken(sourceStream, '"');
            tokens.push_back({ "\"" + str + "\"", String });
        }
        else if (ch == '\'')
        {
            tokens.push_back({ "'", Quote });
        }
        else if (ch == ',')
        {
            tokens.push_back({ ",", Comma });
        }
        else if (ch == '`')
        {
            tokens.push_back({ "`", Backquote });
        }
        else if (ch == ':')
        {
            tokens.push_back({ ":", Colon });
            std::string token;
            while (sourceStream.peek() != EOF && !isspace(sourceStream.peek()) && sourceStream.peek() != '(' && sourceStream.peek() != ')' && sourceStream.peek() != ',' && sourceStream.peek() != ';' && sourceStream.peek() != '`' && sourceStream.peek() != ':')
            {
                token += sourceStream.get();
            }
            if (!token.empty())
            {
                TokenType type = identifyToken(token);
                tokens.push_back({ token, type });
            }
        }
        else if (!isspace(ch))
        {
            std::string token(1, ch);
            while (sourceStream.peek() != EOF && !isspace(sourceStream.peek()) && sourceStream.peek() != '(' && sourceStream.peek() != ')' && sourceStream.peek() != ',' && sourceStream.peek() != ';' && sourceStream.peek() != '`' && sourceStream.peek() != ':')
            {
                token += sourceStream.get();
            }
            TokenType type = identifyToken(token);
            tokens.push_back({ token, type });
        }
    }

    return tokens;
}

// Funci�n para obtener la lista de tokens con sus valores y tipos
std::vector<std::pair<std::string, std::string>> Tokenizer::getTokenList(const std::vector<Token>& tokens)
{
    std::vector<std::pair<std::string, std::string>> tokenList;
    for (const Token& token : tokens)
    {
        tokenList.push_back({ token.value, tokenTypeToString(token.type) });
    }
    return tokenList;
}


