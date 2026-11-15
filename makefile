# ==============================================================================
# Makefile para Práctica 02 (Organizado con carpeta src/)
# ==============================================================================

# Compilador y estándar C++17
CXX         = g++ -std=c++17

# Banderas de advertencia y depuración
WARN        = -Wall -Wextra -Wcast-align -Wno-sign-compare -Wno-write-strings -Wno-parentheses -Wfloat-equal -pedantic
FLAGS       = -DDEBUG -g -O0

# Ruta a DeSiGNAR 
DSG         = DeSiGNAR-main

# Nombre del ejecutable final y archivo fuente dentro de src/
TARGET      = practica_02
SRC_DIR     = src
SRC         = $(SRC_DIR)/practica_02.cpp

# Rutas de inclusión de cabeceras (-I) y enlazado de bibliotecas (-L)
INCLUDEPATH = -I$(DSG)/include
LIBLINK     = -L$(DSG)/build -lDesignar -lpthread

# ==============================================================================
# REGLAS DE COMPILACIÓN
# ==============================================================================

all: $(TARGET)

# Compila tomando el archivo desde la carpeta src/
$(TARGET): $(SRC)
	$(CXX) $(WARN) $(FLAGS) $(INCLUDEPATH) $< -o $@ $(LIBLINK)

# Compilar y ejecutar directamente en la terminal
run: $(TARGET)
	./$(TARGET)

# Limpiar ejecutable y archivos auxiliares
.PHONY: clean
clean:
	$(RM) $(TARGET) *.dot