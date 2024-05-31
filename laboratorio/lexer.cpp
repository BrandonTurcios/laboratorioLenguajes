#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <fstream>
#include <sstream>
#include <cstdlib>

using namespace std;
// Definir los tipos de tokens
enum TokenType
{
    Numero,
    Identificador,
    ParentesisAbrir,
    ParentesisCerrar,
    PalabraReservada,
    Operador,
    Comentario,
    String,
    ComillaSimple,
    Comma,
    ComillaGrave,
    Delimitador
};

// Estructura para los tokens
struct Token
{
    string value;
    TokenType type;
};
vector<pair<string, TokenType>> reservedWords = {
    {"ABS", PalabraReservada}, {"ACONS", PalabraReservada}, {"ACOS", PalabraReservada}, {"Alt-A", PalabraReservada},
    {"Alt-D", PalabraReservada}, {"Alt-H", PalabraReservada}, {"Alt-K", PalabraReservada}, {"AND", Operador},
    {"APPEND", PalabraReservada}, {"APPLY", PalabraReservada}, {"ASIN", PalabraReservada}, {"ASSOC", PalabraReservada},
    {"ATAN", PalabraReservada}, {"ATOM", PalabraReservada}, {"BUTLAST", PalabraReservada}, {"CAR", PalabraReservada},
    {"CASE", PalabraReservada}, {"CDR", PalabraReservada}, {"CLOSE", PalabraReservada}, {"COND", PalabraReservada},{"CONCATENATE", PalabraReservada},
    {"CONS", PalabraReservada}, {"CONSP", PalabraReservada}, {"Control-C", PalabraReservada}, {"Control-D", PalabraReservada},
    {"Control-E", PalabraReservada}, {"Control-L", PalabraReservada}, {"Control-Pausa", PalabraReservada},
    {"COPY-LIST", PalabraReservada}, {"COS", PalabraReservada}, {"DEFUN", PalabraReservada}, {"DELETE", PalabraReservada},{"DEFMACRO", PalabraReservada},
    {"DESCRIBE", PalabraReservada}, {"DO", PalabraReservada}, {"DO*", PalabraReservada}, {"DOLIST", PalabraReservada},
    {"DOS", PalabraReservada}, {"DOTIMES", PalabraReservada}, {"DRIBBLE", PalabraReservada}, {"EQ", Operador},
    {"EQUAL", Operador}, {"EVAL", PalabraReservada}, {"EVENP", PalabraReservada}, {"EVERY", PalabraReservada},
    {"EXIT", PalabraReservada}, {"EXP", PalabraReservada}, {"EXPT", PalabraReservada}, {"FIRST", PalabraReservada},
    {"FORMAT", PalabraReservada},{"FOR", PalabraReservada}, {"FROM", PalabraReservada} ,{"FUNCALL", PalabraReservada},
    {"GET", PalabraReservada}, {"GO", PalabraReservada}, {"IF", PalabraReservada}, {"IFN", PalabraReservada}, {"LAMBDA", PalabraReservada}, {"LAST", PalabraReservada},
    {"LENGTH", PalabraReservada}, {"LET", PalabraReservada}, {"LET*", PalabraReservada}, {"LIST", PalabraReservada},
    {"LIST*", PalabraReservada}, {"LISTP", PalabraReservada}, {"LOAD", PalabraReservada}, {"LOG", PalabraReservada},
    {"LOOP", PalabraReservada}, {"MAKE-LIST", PalabraReservada}, {"MAKUNBOUND", PalabraReservada}, {"MAPC", PalabraReservada},
    {"MAPCAR", PalabraReservada}, {"MAPLIST", PalabraReservada}, {"MAX", PalabraReservada}, {"MEMBER", PalabraReservada},
    {"MIN", PalabraReservada}, {"MINUSP", PalabraReservada}, {"MOD", PalabraReservada}, {"NCONC", PalabraReservada},
    {"NIL", PalabraReservada}, {"NOT", PalabraReservada}, {"NTH", PalabraReservada}, {"NTHCDR", PalabraReservada},
    {"NULL", PalabraReservada}, {"NUMBERP", PalabraReservada}, {"ODDP", PalabraReservada}, {"OPEN", PalabraReservada},
    {"OR", PalabraReservada}, {"PAIRLIS", PalabraReservada}, {"PLUSP", PalabraReservada}, {"PRIN1", PalabraReservada},
    {"PRINC", PalabraReservada}, {"PRINT", PalabraReservada}, {"PROG", PalabraReservada}, {"PROG1", PalabraReservada},{"PUSH", PalabraReservada},
    {"PROG2", PalabraReservada}, {"PROGN", PalabraReservada}, {"QUOTE", PalabraReservada}, {"RASSOC", PalabraReservada},
    {"READ", PalabraReservada}, {"READ-LINE", PalabraReservada}, {"REMOVE", PalabraReservada}, {"REMPROP", PalabraReservada},
    {"REST", PalabraReservada}, {"RETURN", PalabraReservada}, {"REVERSE", PalabraReservada}, {"RPLACA", PalabraReservada},
    {"RPLACD", PalabraReservada}, {"SECOND", PalabraReservada}, {"SET", PalabraReservada}, {"SETQ", PalabraReservada},
    {"SIN", PalabraReservada}, {"SOME", PalabraReservada}, {"SQRT", PalabraReservada}, {"STEP", PalabraReservada},
    {"SUBLIS", PalabraReservada}, {"SUBST", PalabraReservada}, {"SYMBOL-FUNCTION", PalabraReservada},
    {"SYMBOL-NAME", PalabraReservada}, {"SYMBOL-PLIST", PalabraReservada}, {"SYMBOL-PLIST", PalabraReservada},
    {"SYMBOL-PLIST", PalabraReservada}, {"SYMBOL-VALUE", PalabraReservada}, {"SYMBOLP", PalabraReservada},
    {"T", PalabraReservada}, {"TAN", PalabraReservada}, {"TERPRI", PalabraReservada}, {"THIRD", PalabraReservada},
    {"TIME", PalabraReservada}, {"TRACE", PalabraReservada}, {"UNLESS", PalabraReservada}, {"UNTRACE", PalabraReservada},
    {"WHEN", PalabraReservada}, {"WITH-OPEN-FILE", PalabraReservada}, {"ZEROP", PalabraReservada}
};

const vector<pair<string, TokenType>> operators = {
    {"+", Operador}, {"-", Operador}, {"*", Operador}, {"/", Operador}, {"/=", Operador},
    {"=", Operador}, {">=", Operador}, {"<=", Operador}, {">", Operador}, {"<", Operador},
    {"1+", Operador}
};

const vector<pair<string, TokenType>> demiliters = {
   {":", Delimitador}
};

bool isNumero(const string& str)
{
    for (char ch : str)
    {
        if (!isdigit(ch))
            return false;
    }
    return true;
}


TokenType identifyToken(const string& str)
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

   
    if (isNumero(str))
        return Numero;

    return Identificador;
}

string extractToken(stringstream& sourceStream, char delimiter)
{
    string token;
    getline(sourceStream, token, delimiter);
    return token;
}

string tokenTypeToString(TokenType type)
{
    switch (type)
    {
    case Numero: return "Numero";
    case Identificador: return "Identificador";
    case ParentesisAbrir: return "ParentesisAbrir";
    case ParentesisCerrar: return "ParentesisCerrar";
    case PalabraReservada: return "PalabraReservada";
    case Operador: return "Operador";
    case Comentario: return "Comentario";
    case String: return "String";
    case ComillaSimple: return "ComillaSimple";
    case Comma: return "Comma";
    case ComillaGrave: return "ComillaGrave"; // Agregado para representar la comilla grave
    default: return "Desconocido";
    }
}

vector<Token> tokenize(const string& sourceCode)
{
    vector<Token> tokens;
    stringstream sourceStream(sourceCode);
    char ch;

    while (sourceStream.get(ch))
    {
        if (ch == '(')
        {
            tokens.push_back({ "(", ParentesisAbrir });
        }
        else if (ch == ')')
        {
            tokens.push_back({ ")", ParentesisCerrar });
        }
        else if (ch == ';')
        {
            string comment = extractToken(sourceStream, '\n');
            tokens.push_back({ ";" + comment, Comentario });
        }
        else if (ch == '"')
        {
            string str = extractToken(sourceStream, '"');
            tokens.push_back({ "\"" + str + "\"", String });
        }
        else if (ch == '\'')
        {
            tokens.push_back({ "'", ComillaSimple });
        }
        else if (ch == ',')
        {
            tokens.push_back({ ",", Comma });
        }
        else if (ch == '`') 
        {
            tokens.push_back({ "`", ComillaGrave });
        }
        else if (!isspace(ch))
        {
            string token(1, ch);
            while (sourceStream.peek() != EOF && !isspace(sourceStream.peek()) && sourceStream.peek() != '(' && sourceStream.peek() != ')' && sourceStream.peek() != ',' && sourceStream.peek() != ';' && sourceStream.peek() != '`')
            {
                token += sourceStream.get();
            }
            TokenType type = identifyToken(token);
            tokens.push_back({ token, type });
        }
    }

    return tokens;
}

int main()
{
    string fileName;
    cout << "Ingrese el nombre del archivo de entrada: ";
    cin >> fileName;

    string sourceCode;
    {
        stringstream contents_stream;
        ifstream input(fileName, ios::in);
        if (!input)
        {
            cerr << "No se pudo abrir el archivo!" << endl;
            return EXIT_FAILURE;
        }
        contents_stream << input.rdbuf();
        sourceCode = contents_stream.str();
    }

   
    vector<Token> tokens = tokenize(sourceCode);


    for (const Token& token : tokens)
    {
        cout << "Value: " << token.value << "   Type: " << tokenTypeToString(token.type) << endl;
    }

    return 0;
}
