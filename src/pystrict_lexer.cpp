#include "pystrict_lexer.hpp"
#include <stdexcept>
#include <sstream>

namespace PyStrict {

PyStrictLexer::PyStrictLexer() {
    register_rules();
}

void PyStrictLexer::register_rules() {
    // Macro-patrones compatibles con RegexToNFA de DeSiGNAR (sin corchetes [])
    const std::string DIGIT = "(0|1|2|3|4|5|6|7|8|9)";
    const std::string LOWER = "(a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z)";
    const std::string UPPER = "(A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z)";
    const std::string ALPHA = "(" + LOWER + "|" + UPPER + "|_)";
    const std::string ALNUM = "(" + ALPHA + "|" + DIGIT + ")";

    // Carácter válido dentro de cadenas y comentarios de línea
    const std::string SYM_COMMON = "( |!|#|\\$|%|&|\\(|\\)|\\*|\\+|,|-|\\.|/|:|;|<|=|>|\\?|@|\\[|\\]|^|`|{|}|~)";
    const std::string STR_CHAR_DQ = "(" + ALNUM + "|" + SYM_COMMON + "|')";
    const std::string STR_CHAR_SQ = "(" + ALNUM + "|" + SYM_COMMON + "|\\\")";

    // 1. COMENTARIOS Y ESPACIOS (Se filtran luego, excepto NEWLINE si se usa en el parser)
    d_lexer.add_token("COMMENT_LINE", "#(" + STR_CHAR_DQ + "|\\\")*");
    d_lexer.add_token("NEWLINE", "\n");
    d_lexer.add_token("WHITESPACE", "( |\t|\r)+");

    // 2. PALABRAS RESERVADAS: Control de Flujo (Prioridad antes que ID)
    d_lexer.add_token("KW_IF", "if");
    d_lexer.add_token("KW_ELSE", "else");
    d_lexer.add_token("KW_ELIF", "elif");
    d_lexer.add_token("KW_WHILE", "while");
    d_lexer.add_token("KW_FOR", "for");
    d_lexer.add_token("KW_BREAK", "break");
    d_lexer.add_token("KW_CONTINUE", "continue");
    d_lexer.add_token("KW_RETURN", "return");

    // 3. PALABRAS RESERVADAS: Estructura y Módulos
    d_lexer.add_token("KW_DEF", "def");
    d_lexer.add_token("KW_CLASS", "class");
    d_lexer.add_token("KW_IMPORT", "import");
    d_lexer.add_token("KW_FROM", "from");
    d_lexer.add_token("KW_AS", "as");
    d_lexer.add_token("KW_PASS", "pass");

    // 4. TIPOS ESTRICTOS BASE (Categoría TYPE en la especificación)
    d_lexer.add_token("TYPE", "int|float|str|bool|void|list|dict");

    // 5. LÓGICA Y CONSTANTES
    d_lexer.add_token("KW_AND", "and");
    d_lexer.add_token("KW_OR", "or");
    d_lexer.add_token("KW_NOT", "not");
    d_lexer.add_token("KW_TRUE", "True");
    d_lexer.add_token("KW_FALSE", "False");
    d_lexer.add_token("KW_NONE", "None");

    // 6. OPERADORES COMPUESTOS Y SIMPLES (ARROW antes que OP_ARITH '-' y OP_REL '>')
    d_lexer.add_token("ARROW", "->");
    d_lexer.add_token("OP_REL", "==|!=|>=|<=|>|<");
    d_lexer.add_token("ASSIGN", "=");

    // 7. CONSTANTES NUMÉRICAS (FLOAT_LITERAL e INT_LITERAL)
    // Nota: Se registran antes de OP_ARITH para soportar el signo '-' opcional según tu PDF
    d_lexer.add_token("FLOAT_LITERAL", "-?" + DIGIT + "+\\." + DIGIT + "+");
    d_lexer.add_token("INT_LITERAL", "-?" + DIGIT + "+");

    // 8. OPERADORES ARITMÉTICOS (Escapando + y * para Thompson)
    d_lexer.add_token("OP_ARITH", "\\+|-|\\*|/|%");

    // 9. CONSTANTES DE CADENA (Comillas dobles o simples)
    d_lexer.add_token("STRING", "(\\\"" + STR_CHAR_DQ + "*\\\")|('" + STR_CHAR_SQ + "*')");

    // 10. SÍMBOLOS Y PUNTUACIÓN (Escapando paréntesis)
    d_lexer.add_token("L_PAREN", "\\(");
    d_lexer.add_token("R_PAREN", "\\)");
    d_lexer.add_token("L_BRACE", "{");
    d_lexer.add_token("R_BRACE", "}");
    d_lexer.add_token("L_BRACKET", "[");
    d_lexer.add_token("R_BRACKET", "]");
    d_lexer.add_token("COLON", ":");
    d_lexer.add_token("COMMA", ",");
    d_lexer.add_token("DOT", "\\.");

    // 11. IDENTIFICADORES (Registrado después de todas las keywords y tipos)
    d_lexer.add_token("ID", ALPHA + ALNUM + "*");
}

void PyStrictLexer::compute_line_col(const std::string& input, Designar::nat_t pos, int& line, int& col) const {
    line = 1;
    col = 1;
    for (Designar::nat_t i = 0; i < pos && i < input.size(); ++i) {
        if (input[i] == '\n') {
            line++;
            col = 1;
        } else {
            col++;
        }
    }
}

std::vector<EnrichedToken> PyStrictLexer::tokenize(const std::string& source) const {
    std::vector<EnrichedToken> result;
    
    // Invoca el motor de maximal munch de DeSiGNAR
    Designar::DynArray<Designar::Token> raw_tokens = d_lexer.tokenize(source);

    for (Designar::nat_t i = 0; i < raw_tokens.size(); ++i) {
        const Designar::Token& t = raw_tokens[i];
        
        // Descartar espacios en blanco y comentarios de una línea
        if (t.name == "WHITESPACE" || t.name == "COMMENT_LINE") {
            continue;
        }

        int line = 1, col = 1;
        compute_line_col(source, t.position, line, col);
        result.push_back({t.name, t.lexeme, t.position, line, col});
    }

    return result;
}

} // namespace PyStrict