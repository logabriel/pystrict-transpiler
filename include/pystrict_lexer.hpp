#ifndef PYSTRICT_LEXER_HPP
#define PYSTRICT_LEXER_HPP

#include <lexer.hpp>
#include <string>
#include <vector>

namespace PyStrict {

struct EnrichedToken {
    std::string name;      // Categoría (ej. "KW_DEF", "TYPE", "ID")
    std::string lexeme;    // Texto original reconocido
    Designar::nat_t pos;   // Offset en el archivo original
    int line;              // Línea (1-indexed)
    int column;            // Columna (1-indexed)
};

class PyStrictLexer {
private:
    Designar::Lexer d_lexer;
    void register_rules();
    void compute_line_col(const std::string& input, Designar::nat_t pos, int& line, int& col) const;

public:
    PyStrictLexer();
    
    // Tokeniza el código fuente filtrando espacios y comentarios
    std::vector<EnrichedToken> tokenize(const std::string& source) const;
};

} // namespace PyStrict

#endif // PYSTRICT_LEXER_HPP