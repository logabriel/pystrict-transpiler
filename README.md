*PyStrict Transpiler*

PyStrict Transpiler es un proyecto en desarrollo construido en C++17 que traduce un subconjunto estáticamente tipado de Python (PyStrict) a código compilable.

Actualmente, el proyecto ha completado su primera fase: el Analizador Léxico (Scanner), implementado haciendo uso del motor de expresiones regulares y autómatas de la biblioteca DeSiGNAR.

- Estado Actual: Analizador Léxico

El lexer actual (PyStrictLexer) es capaz de:

Reconocer palabras reservadas de control de flujo (if, while, for, etc.) y definición de estructuras (def, class).

Identificar tipos estrictos requeridos por el lenguaje (int, float, str, bool, void, list, dict).

Procesar operadores aritméticos, relacionales y de asignación (incluyendo el token de retorno ->).

Ignorar de forma inteligente los comentarios de una sola línea (#) y los espacios en blanco, manteniendo el conteo exacto de líneas y columnas para el manejo de futuros errores sintácticos.

Enriquecer los tokens devolviendo una estructura EnrichedToken con el lexema original, la categoría, y su ubicación exacta en el código fuente.


- Estructura del Proyecto

pystrict-transpiler/
├── Docs/                  # Documentación del proyecto (Especificaciones en PDF)
├── examples/              # Códigos de prueba y ejemplos de uso
│   └── ejemplo_lexer.cpp  # Programa principal de prueba del analizador léxico
├── include/               # Cabeceras (.hpp)
│   └── pystrict_lexer.hpp # Definición de la clase PyStrictLexer y EnrichedToken
├── src/                   # Código fuente (.cpp)
│   └── pystrict_lexer.cpp # Implementación de las reglas léxicas
└── Makefile               # Reglas de compilación automatizadas


🛠️ Requisitos Previos

Para compilar y ejecutar este proyecto, tu entorno (Linux o WSL) debe contar con:

Compilador C++: Soporte para el estándar C++17 (ej. g++).

GNU Make: Para la orquestación de la compilación.

Biblioteca DeSiGNAR (v4.0.0): Requerida para el motor de tokens (lexer.hpp).

⚙️ Compilación y Ejecución

Configurar la ruta de DeSiGNAR:
Antes de compilar, abre el archivo Makefile y asegúrate de que la variable DSG apunte al directorio correcto donde tienes instalada la biblioteca en tu sistema.

# Ejemplo en Makefile:
DSG = /ruta/absoluta/a/tu/DeSiGNAR-4.0.0


Compilar el ejemplo del Lexer:
Ejecuta el siguiente comando en la terminal para construir el binario de prueba:

make example


Ejecutar la prueba:
Para correr el tokenizador sobre el código PyStrict de prueba (cálculo de factura):

make run-example


Salida Esperada

Al ejecutar el programa de prueba, verás el flujo de tokens reconocidos con su respectiva posición [línea:columna @offset]:

=== Tokenizando código PyStrict con DeSiGNAR ===

[2:1 @41]	KW_DEF("def")
[2:5 @45]	ID("calcular_total")
[2:19 @59]	L_PAREN("(")
[2:20 @60]	ID("precio")
[2:26 @66]	COLON(":")
...


- Roadmap (Próximos Pasos)

Dado que la meta es un transpilador completo, el proyecto evolucionará para incluir:

[x] Módulo Léxico: Tokenización y filtrado de caracteres.

[ ] Módulo Sintáctico (Parser): Análisis LL(1) / LR(1) y generación del Árbol de Sintaxis Abstracta (AST).

[ ] Módulo Semántico: Verificación estricta de tipos.

[ ] Generación de Código: Traducción del AST validado a C++ o lenguaje destino.

- Autores

Desarrollado como proyecto para la asignatura de Compiladores en la facultad de ingenieria de la Universidad de Los Andes

Equipo Byte Force - Luis Ordóñez v-29520623 & Gabriel Pérez v-26587279.