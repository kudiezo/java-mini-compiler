#ifndef TDA_LEXICO_H_INCLUDED
#define TDA_LEXICO_H_INCLUDED

/** TDA L�XICO **/
typedef struct lexico Lexico;
Lexico analex();

/** TDA PARA KEYWORDS **/
typedef struct keyword Keyword;
Keyword *iniListaKeywords();
Keyword *importarKeyWords();
void mostrarTodosKeywords(Keyword *listaKeywords);

/** OUTRAS DECLARA��ES **/
char lerCaracter(FILE *arquivoDeLeitura);
void zerarVetor();

/** TDA PARA GUARDAR ERROS L�XICOS **/
typedef struct lexerros Lexerros;
Lexerros *iniListaLexerros();

#endif // TDA_LEXICO_H_INCLUDED
