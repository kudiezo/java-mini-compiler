#include "TDA_lexico.h"
#include <string.h>

int qtdLexerros = 0;

struct lexico {
    char *lexema;
    char *token;
    char *tipoDado;
    char *valorAtribuido;
    int linha;
};

struct keyword {
    char word[50];
    struct keyword *next;
};
Keyword *iniListaKeywords() {
    return NULL;
}
Keyword *insereKeyWord(Keyword *listaKeywords, char word[]) {
    Keyword *novo;
    novo = (Keyword*) malloc(sizeof(Keyword));
    strcpy(novo->word, word);
    novo->next = listaKeywords;
    return novo;
}
Keyword *importarKeyWords() {
    Keyword *listaKeywords = iniListaKeywords();
    char palavra[50];

    FILE *arquivoKeywords = fopen("keywords.txt", "r");
    if(arquivoKeywords == NULL)
        printf("Nao foi possivel abrir o arquivo que contém as palavras-chave.");

    // realiza a leitura do arquivo palavra por palavra
    while (fscanf(arquivoKeywords, "%s", palavra) != EOF) {
        listaKeywords = insereKeyWord(listaKeywords, palavra);
    }
    fclose(arquivoKeywords);
    return listaKeywords;
}
void mostrarTodosKeywords(Keyword *listaKeywords) {
    Keyword *aux;
    for(aux = listaKeywords; aux != NULL; aux = aux->next) {
        printf("%s ", aux->word);
    }
}

/** Lista para guardar os erros léxicos (Lista Circular Simples) **/
struct lexerros {
    char lexema[250];
    char token[100];
    int linha;
    char *descricao;
    struct lexerros *next;
};
Lexerros *iniListaLexerros() {
    return NULL;
}
Lexerros *insereErro(Lexerros *listaLexerros, char lexema[], char token[], int linha, char *descricao) {
    Lexerros *novo;
    novo = (Lexerros*) malloc(sizeof(Lexerros));
    strcpy(novo->lexema, lexema);
    strcpy(novo->token, token);
    novo->linha = linha;
    novo->descricao = descricao;
    novo->next = NULL;
    if(listaLexerros == NULL) {
        listaLexerros = novo;
        qtdLexerros++;
        return listaLexerros;
    }
    Lexerros *aux = listaLexerros;
    while(aux->next != NULL) {
        aux = aux->next;
    }
    aux->next = novo;
    qtdLexerros++;
    return listaLexerros;
}
void mostrarTodosLexerros(Lexerros *listaLexerros) {
    Lexerros *aux = listaLexerros;
    if(listaLexerros != NULL) {
        do {
            printf("\n Linha %d: %s '%s' \n", aux->linha, aux->descricao, aux->lexema);
            aux = aux->next;
        } while(aux != NULL);
    }
}


/**
* Função que lê apenas um caracter do arquivo e o retorna
*/
char lerCaracter(FILE *arquivoDeLeitura) {
    char caracter;
    fread(&caracter, sizeof(char), 1, arquivoDeLeitura);
    return caracter;
}

void voltaCaractere(FILE *arquivo) {
    fseek(arquivo, -1, SEEK_CUR);
}

/**
* Verifica se a id (word) passada está na lista das keywords.
* Retorna 1, se estiver, e 0 caso não esteja
*/
int verificarKeyword(Keyword *listaKeywords, char word[]) {
    while(listaKeywords != NULL) {
        if(strcmp(listaKeywords->word, word) == 0)
           return 1;
        listaKeywords = listaKeywords->next;
    }
    return 0;
}



