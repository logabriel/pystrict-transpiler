# ==============================================================================
# Makefile para PyStrict Transpiler (Con soporte para examples/)
# ==============================================================================

# Compilador y estándar C++17
CXX         = g++ -std=c++17

# Banderas de advertencia y depuración
WARN        = -Wall -Wextra -Wcast-align -Wno-sign-compare -Wno-write-strings -Wno-parentheses -Wfloat-equal -pedantic
FLAGS       = -DDEBUG -g -O0

# Ruta a DeSiGNAR 
DSG         = DeSiGNAR-main

# Directorios del proyecto
SRC_DIR     = src
INC_DIR     = include
EX_DIR      = examples

# Código común del Lexer (necesario tanto para el ejecutable principal como para ejemplos)
LEXER_SRC   = $(SRC_DIR)/pystrict_lexer.cpp

# Ejecutable (src/ejemplo_lexer.cpp)
TARGET      = pystrict
MAIN_SRCS   = $(SRC_DIR)/ejemplo_lexer.cpp $(LEXER_SRC)

# Ejecutable de ejemplo (examples/main.cpp)
EX_TARGET   = pystrict_example
EX_SRCS     = $(EX_DIR)/ejemplo_lexer.cpp $(LEXER_SRC)

# Rutas de inclusión de cabeceras (-I) y enlazado de bibliotecas (-L)
INCLUDEPATH = -I$(INC_DIR) -I$(DSG)/include
LIBLINK     = -L$(DSG)/build -lDesignar -lpthread

# ==============================================================================
# REGLAS DE COMPILACIÓN
# ==============================================================================

all: $(TARGET)

# 1. Compilar el proyecto principal (src/main.cpp)
$(TARGET): $(MAIN_SRCS)
	$(CXX) $(WARN) $(FLAGS) $(INCLUDEPATH) $^ -o $@ $(LIBLINK)

# Ejecutar el proyecto principal
run: $(TARGET)
	./$(TARGET)

# 2. Compilar el ejemplo en examples/main.cpp
example: $(EX_TARGET)

$(EX_TARGET): $(EX_SRCS)
	$(CXX) $(WARN) $(FLAGS) $(INCLUDEPATH) $^ -o $@ $(LIBLINK)

# Compilar y ejecutar directamente examples/main.cpp
run-example: $(EX_TARGET)
	./$(EX_TARGET)

# 3. Regla opcional para practica_02.cpp
practica_02: $(SRC_DIR)/practica_02.cpp
	$(CXX) $(WARN) $(FLAGS) $(INCLUDEPATH) $< -o $@ $(LIBLINK)

# Limpiar todos los ejecutables y archivos auxiliares
.PHONY: all run example run-example clean
clean:
	$(RM) $(TARGET) $(EX_TARGET) practica_02 *.dot