
#include "pystrict_lexer.hpp"
#include <iostream>

int main() {
    PyStrict::PyStrictLexer lexer;

    // Código de prueba Ejemplo 1 PDF de PyStrict
    std::string codigo_pystrict = 
        "# Calculo de factura con tipado estricto\n"
        "def calcular_total(precio: float, impuesto: float) -> float:\n"
        "    total: float = precio + (precio * impuesto)\n"
        "    return total\n\n"
        "precio_final: float = calcular_total(100.0, 0.16)\n";

    std::cout << "=== Tokenizando código PyStrict con DeSiGNAR ===\n\n";

    try {
        auto tokens = lexer.tokenize(codigo_pystrict);
        for (const auto& t : tokens) {
            std::string display_lexeme = (t.name == "NEWLINE") ? "\\n" : t.lexeme;
            std::cout << "[" << t.line << ":" << t.column << " @" << t.pos << "]\t"
                      << t.name << "(\"" << display_lexeme << "\")\n";
        }
    } catch (const std::runtime_error& e) {
        std::cerr << "[PyStrict Lexical Error] -> " << e.what() << std::endl;
        return 1;
    }

    return 0;
}