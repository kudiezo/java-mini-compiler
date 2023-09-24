#include <stdio.h>
#include <stdlib.h>
#include "implementacao_TDA_lexico.c"
#include "token.h"

char c;
int estado = 0;
char vetor[500];//vetor que vai guardando sequ�ncia de caracteres lidos
int cont = 0;//Controlador do vetor
int linha = 1;//Controlador da linha de leitura do arquivo de c�digo fonte
//Vari�vel para o arquivo do c�digo fonte e para o arquivo que cont�m as keywords
FILE *arquivoCodFonte, *arquivoKeywords;
Lexico lexico;//Estrutura que vai guardar o lexema, token e a linha em que se encontra
Keyword *keywords;//lista para as keywords
Lexerros *listaLexerros;//lista para guardar os erros l�xicos encontrados
char *descricaoErro;//Vetor para escrever a descricao de eventuais erros l�xicos

/**
* Fun��o "estado 0", de onde come�a a valida��o da leitura
* caracter por caracter. A valida��o recome�a aqui sempre que
* for reconhecido um token
*/
void estado_0() {
    if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_' || c == '$') {
        vetor[cont] = c;
        cont++;
        estado = 1;
    }
    else if(c == '/') {
        vetor[cont] = c;
        cont++;
        estado = 3;
    }
    else if(c >= '0' && c <= '9') {
        vetor[cont] = c;
        cont++;
        estado = 10;
    }
    else if(c == '+') {
        vetor[cont] = c;
        cont++;
        estado = 14;
    }
    else if(c == '-') {
        vetor[cont] = c;
        cont++;
        estado = 18;
    }
    else if(c == '*') {
        vetor[cont] = c;
        cont++;
        estado = 22;
    }
    else if(c == '=') {
        vetor[cont] = c;
        cont++;
        estado = 26;
    }
    else if(c == '^') {
        vetor[cont] = c;
        cont++;
        estado = 29;
    }
    else if(c == '|') {
        vetor[cont] = c;
        cont++;
        estado = 32;
    }
    else if(c == '&') {
        vetor[cont] = c;
        cont++;
        estado = 35;
    }
    else if(c == '!') {
        vetor[cont] = c;
        cont++;
        estado = 39;
    }
    else if(c == '%') {
        vetor[cont] = c;
        cont++;
        estado = 42;
    }
    else if(c == '<') {
        vetor[cont] = c;
        cont++;
        estado = 45;
    }
    else if(c == '>') {
        vetor[cont] = c;
        cont++;
        estado = 51;
    }
    else if(c == '"') {
        vetor[cont] = c;
        cont++;
        estado = 57;
    }
    else if(c == '\'') {
        vetor[cont] = c;
        cont++;
        estado = 59;
    }
    else if(c == '(') {
        vetor[cont] = c;
        cont++;
        estado = 62;
    }
    else if(c == ')') {
        vetor[cont] = c;
        cont++;
        estado = 63;
    }
    else if(c == '{') {
        vetor[cont] = c;
        cont++;
        estado = 64;
    }
    else if(c == '}') {
        vetor[cont] = c;
        cont++;
        estado = 65;
    }
    else if(c == '[') {
        vetor[cont] = c;
        cont++;
        estado = 66;
    }
    else if(c == ']') {
        vetor[cont] = c;
        cont++;
        estado = 67;
    }
    else if(c == '~') {
        vetor[cont] = c;
        cont++;
        estado = 68;
    }
    else if(c == ':') {
        vetor[cont] = c;
        cont++;
        estado = 69;
    }
    else if(c == ';') {
        vetor[cont] = c;
        cont++;
        estado = 70;
    }
    else if(c == ',') {
        vetor[cont] = c;
        cont++;
        estado = 71;
    }
    else if(c == '.') {
        vetor[cont] = c;
        cont++;
        estado = 72;
    } else if(c == '\n') {
        linha++;
    }
    else if(c != ' ') {
        vetor[cont] = c;
        cont++;
        estado = 77;
    }
}
/**
* Aqui come�am as defini��es das fun��es de todos os "estados"
* subsequentes ao "estado 0"
*/
void estado_1() {
    while((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_' || (c >= '0' && c <= '9') || c == '$') {
        vetor[cont] = c;
        cont++;
        c = lerCaracter(arquivoCodFonte);
    }
    estado = 2;
    if(c != ' ' || c != '\n')
        voltaCaractere(arquivoCodFonte);
}
void estado_2() {
    lexico.lexema = vetor;
    lexico.token = TK_ID;
    if(verificarKeyword(keywords, vetor) == 1)
        lexico.token = TK_KEYWORD;
}
void estado_3() {
    if(c == '/') {
        vetor[cont] = c;
        cont++;
        estado = 4;
    }
    else if(c == '*') {
        vetor[cont] = c;
        cont++;
        estado = 6;
    }
    else if(c == '=') {
        vetor[cont] = c;
        cont++;
        estado = 25;
    }
    else {
        estado = 9;
        if(c != ' ' || c != '\n')
            voltaCaractere(arquivoCodFonte);
    }
}
void estado_4() {
    while(c != '\n') {
        vetor[cont] = c;
        cont++;
        c = lerCaracter(arquivoCodFonte);
    }
    voltaCaractere(arquivoCodFonte);
    estado = 5;
}
void estado_5() {
    lexico.lexema = vetor;
    lexico.token = TK_COMENTARIO;
}
void estado_6() {
    if(c == '\n')
        linha++;
    while(c != '*' && !feof(arquivoCodFonte)) {
        vetor[cont] = c;
        cont++;
        c = lerCaracter(arquivoCodFonte);
        if(c == '\n')
            linha++;
    }
    if(feof(arquivoCodFonte)) {
        voltaCaractere(arquivoCodFonte);
        linha--;
        estado = 79;
        return;
    }
    vetor[cont] = c;
    cont++;
    estado = 7;
}
void estado_7() {
    if(feof(arquivoCodFonte)) {
        voltaCaractere(arquivoCodFonte);
        linha--;
        estado = 79;
    }
    if(c == '/') {
        vetor[cont] = c;
        cont++;
        estado = 8;
    } else if(c == '\n') linha++;
    else {
        vetor[cont] = c;
        cont++;
        estado = 6;
    }
}
void estado_8() {
    lexico.lexema = vetor;
    lexico.token = TK_BLOCO_COMENTARIO;
}
void estado_9() {
    lexico.lexema = vetor;
    lexico.token = TK_OP_DIVISAO;
}
void estado_10() {
    while(c >= '0' && c <= '9') {
        vetor[cont] = c;
        cont++;
        c = lerCaracter(arquivoCodFonte);
    }
    if(c == '.') {
        vetor[cont] = c;
        cont++;
        estado = 11;
    } else {
        estado = 13;
        if(c != ' ' || c != '\n')
            voltaCaractere(arquivoCodFonte);
    }

}
void estado_11() {
    if(!(c >= '0' && c <= '9')) {
        estado = 76;
        voltaCaractere(arquivoCodFonte);
        return;
    }
    while(c >= '0' && c <= '9') {
        vetor[cont] = c;
        cont++;
        c = lerCaracter(arquivoCodFonte);
    }
    voltaCaractere(arquivoCodFonte);
    estado = 12;
}
void estado_12() {
    lexico.lexema = vetor;
    lexico.token = TK_NUM_REAL;
}
void estado_13() {
    lexico.lexema = vetor;
    lexico.token = TK_NUM_INTEIRO;
}
void estado_14() {
    if(c == '+') {
        vetor[cont] = c;
        cont++;
        estado = 15;
    } else if(c == '='){
        vetor[cont] = c;
        cont++;
        estado = 16;
    } else {
        estado = 17;
        if(c != ' ' || c != '\n')
            voltaCaractere(arquivoCodFonte);
    }
}
void estado_15() {
    lexico.lexema = vetor;
    lexico.token = TK_OP_INCREMENTO;
}
void estado_16() {
    lexico.lexema = vetor;
    lexico.token = TK_OP_SOMA_ATRIBUICAO;
}
void estado_17() {
    lexico.lexema = vetor;
    lexico.token = TK_OP_MAIS;
}
void estado_18() {
    if(c == '-') {
        vetor[cont] = c;
        cont++;
        estado = 19;
    } else if(c == '='){
        vetor[cont] = c;
        cont++;
        estado = 20;
    } else {
        estado = 21;
        if(c != ' ' || c == '\n' || c != '\n')
            voltaCaractere(arquivoCodFonte);
    }
}
void estado_19() {
    lexico.lexema = vetor;
    lexico.token = TK_OP_DECREMENTO;
}
void estado_20() {
    lexico.lexema = vetor;
    lexico.token = TK_OP_SUBTRACAO_ATRIBUICAO;
}
void estado_21() {
    lexico.lexema = vetor;
    lexico.token = TK_OP_MENOS;
}
void estado_22() {
    if(c == '=') {
        vetor[cont] = c;
        cont++;
        estado = 23;
    } else {
        estado = 24;
        if(c != ' ' || c == '\n')
            voltaCaractere(arquivoCodFonte);
    }
}
void estado_23() {
    lexico.lexema = vetor;
    lexico.token = TK_OP_MULTIPLICACAO_ATRIBUICAO;
}
void estado_24() {
    lexico.lexema = vetor;
    lexico.token = TK_OP_MULTIPLICACAO;
}
void estado_25() {
    lexico.lexema = vetor;
    lexico.token = TK_OP_DIVISAO_ATRIBUICAO;
}
void estado_26() {
    if(c == '=') {
        vetor[cont] = c;
        cont++;
        estado = 27;
    } else {
        estado = 28;
        if(c != ' ' || c != '\n')
            voltaCaractere(arquivoCodFonte);
    }
}
void estado_27() {
    lexico.lexema = vetor;
    lexico.token = TK_OP_IGUAL;
}
void estado_28() {
    lexico.lexema = vetor;
    lexico.token = TK_OP_ATRIBUICAO;
}
void estado_29() {
    if(c == '=') {
        vetor[cont] = c;
        cont++;
        estado = 30;
    } else {
        estado = 31;
        if(c != ' ' || c != '\n')
            voltaCaractere(arquivoCodFonte);
    }
}
void estado_30() {
    lexico.lexema = vetor;
    lexico.token = TK_OP_XOR_BIT_A_BIT_ATRIBUICAO;
}
void estado_31() {
    lexico.lexema = vetor;
    lexico.token = TK_OP_XOR_BIT_A_BIT;
}
void estado_32() {
    if(c == '=') {
        vetor[cont] = c;
        cont++;
        estado = 33;
    } else if(c == '|') {
        vetor[cont] = c;
        cont++;
        estado = 73;
    }
    else {
        estado = 34;
        if(c != ' ' || c != '\n')
            voltaCaractere(arquivoCodFonte);
    }
}
void estado_33() {
    lexico.lexema = vetor;
    lexico.token = TK_OP_OR_BIT_A_BIT_ATRIBUICAO;
}
void estado_34() {
    lexico.lexema = vetor;
    lexico.token = TK_OP_OR_BIT_A_BIT;
}
void estado_35() {
    if(c == '=') {
        vetor[cont] = c;
        cont++;
        estado = 36;
    } else if(c == '&') {
        vetor[cont] = c;
        cont++;
        estado = 37;
    } else {
        estado = 38;
        if(c != ' ' || c != '\n')
            voltaCaractere(arquivoCodFonte);
    }
}
void estado_36() {
    lexico.lexema = vetor;
    lexico.token = TK_OP_AND_BIT_A_BIT_ATRIBUICAO;
}
void estado_37() {
    lexico.lexema = vetor;
    lexico.token = TK_OP_AND;
}
void estado_38() {
    lexico.lexema = vetor;
    lexico.token = TK_OP_AND_BIT_A_BIT;
}
void estado_39() {
    if(c == '=') {
        vetor[cont] = c;
        cont++;
        estado = 40;
    } else {
        estado = 41;
        if(c != ' ' || c != '\n')
            voltaCaractere(arquivoCodFonte);
    }
}
void estado_40() {
    lexico.lexema = vetor;
    lexico.token = TK_OP_DIFERENTE;
}
void estado_41() {
    lexico.lexema = vetor;
    lexico.token = TK_OP_NOT;
}
void estado_42() {
    if(c == '=') {
        vetor[cont] = c;
        cont++;
        estado = 43;
    } else {
        estado = 44;
        if(c != ' ' || c != '\n')
            voltaCaractere(arquivoCodFonte);
    }
}
void estado_43() {
    lexico.lexema = vetor;
    lexico.token = TK_OP_MODULO_ATRIBUICAO;
}
void estado_44() {
    lexico.lexema = vetor;
    lexico.token = TK_OP_MODULO;
}
void estado_45() {
    if(c == '=') {
        vetor[cont] = c;
        cont++;
        estado = 46;
    } else if(c == '<') {
        vetor[cont] = c;
        cont++;
        estado = 47;
    } else {
        estado = 50;
        if(c != ' ' || c != '\n')
            voltaCaractere(arquivoCodFonte);
    }
}
void estado_46() {
    lexico.lexema = vetor;
    lexico.token = TK_OP_MENOR_IGUAL;
}
void estado_47() {
    if(c == '=') {
        vetor[cont] = c;
        cont++;
        estado = 48;
    } else {
        estado = 49;
        if(c != ' ' || c != '\n')
            voltaCaractere(arquivoCodFonte);
    }
}
void estado_48() {
    lexico.lexema = vetor;
    lexico.token = TK_OP_DESLOCAMENTO_LEFT_ATRIBUICAO;
}
void estado_49() {
    lexico.lexema = vetor;
    lexico.token = TK_OP_DESLOCAMENTO_LEFT;
}
void estado_50() {
    lexico.lexema = vetor;
    lexico.token = TK_OP_MENOR;
}
void estado_51() {
    if(c == '=') {
        vetor[cont] = c;
        cont++;
        estado = 52;
    } else if(c == '>') {
        vetor[cont] = c;
        cont++;
        estado = 53;
    } else {
        estado = 56;
        if(c != ' ' || c != '\n')
            voltaCaractere(arquivoCodFonte);
    }
}
void estado_52() {
    lexico.lexema = vetor;
    lexico.token = TK_OP_MAIOR_IGUAL;
}
void estado_53() {
    if(c == '=') {
        vetor[cont] = c;
        cont++;
        estado = 54;
    } else {
        estado = 55;
        if(c != ' ' || c != '\n')
            voltaCaractere(arquivoCodFonte);
    }
}
void estado_54() {
    lexico.lexema = vetor;
    lexico.token = TK_OP_DESLOCAMENTO_RIGHT_ATRIBUICAO;
}
void estado_55() {
    lexico.lexema = vetor;
    lexico.token = TK_OP_DESLOCAMENTO_RIGHT;
}
void estado_56() {
    lexico.lexema = vetor;
    lexico.token = TK_OP_MAIOR;
}
void estado_57() {
    while(c != '"') {
        if(c == '\n') {
            estado = 75;
            voltaCaractere(arquivoCodFonte);
            return;
        }
        vetor[cont] = c;
        cont++;
        c = lerCaracter(arquivoCodFonte);
    }
    vetor[cont] = c;
    cont++;
    estado = 58;
}
void estado_58() {
    lexico.lexema = vetor;
    lexico.token = TK_VALOR_STRING;
}
void estado_59() {
    if(c == '\\') {
        vetor[cont] = c;
        cont++;
        estado = 74;
    } else if(c == '\'') {
        vetor[cont] = c;
        cont++;
        estado = 61;
    } else {
        vetor[cont] = c;
        cont++;
        estado = 60;
    }
}
void estado_60() {
    if(c == '\'') {
        vetor[cont] = c;
        cont++;
        estado = 61;
    } else {
        while(c != '\n' && c != '\'') {
            vetor[cont] = c;
            cont++;
            c = lerCaracter(arquivoCodFonte);
        }
        if(c == '\n')
            voltaCaractere(arquivoCodFonte);
        if(c == '\'') {
            vetor[cont] = c;
            cont++;
        }
        estado = 78;
    }
}
void estado_61() {
    lexico.lexema = vetor;
    lexico.token = TK_VALOR_CHAR;
}
void estado_62() {
    lexico.lexema = vetor;
    lexico.token = TK_ABRE_PARENTESES;
}
void estado_63() {
    lexico.lexema = vetor;
    lexico.token = TK_FECHA_PARENTESES;
}
void estado_64() {
    lexico.lexema = vetor;
    lexico.token = TK_ABRE_CHAVETA;
}
void estado_65() {
    lexico.lexema = vetor;
    lexico.token = TK_FECHA_CHAVETA;
}
void estado_66() {
    lexico.lexema = vetor;
    lexico.token = TK_ABRE_COLCHETES;
}
void estado_67() {
    lexico.lexema = vetor;
    lexico.token = TK_FECHA_COLCHETES;
}
void estado_68() {
    lexico.lexema = vetor;
    lexico.token = TK_OP_COMPLEMENTO_BIT_A_BIT;
}
void estado_69() {
    lexico.lexema = vetor;
    lexico.token = TK_DOIS_PONTOS;
}
void estado_70() {
    lexico.lexema = vetor;
    lexico.token = TK_PONTO_VIRGULA;
}
void estado_71() {
    lexico.lexema = vetor;
    lexico.token = TK_VIRGULA;
}
void estado_72() {
    lexico.lexema = vetor;
    lexico.token = TK_PONTO;
}
void estado_73() {
    lexico.lexema = vetor;
    lexico.token = TK_OP_OR;
}
void estado_74() {
    if(c == 'n' || c == 'r' || c == 't' || c == '\'' || c == '\\') {
        vetor[cont] = c;
        cont++;
        estado = 60;
    }
}
//Erro l�xico: falta delimitador de string (")
void estado_75() {
    descricaoErro = "Delimitador de string \" em falta";
    lexico.lexema = vetor;
    lexico.token = TK_VALOR_STRING;
    listaLexerros = insereErro(listaLexerros, lexico.lexema, lexico.token, linha, descricaoErro);
}
void estado_76() {
    descricaoErro = "Numero real mal formatado";
    lexico.lexema = vetor;
    lexico.token = TK_NUM_REAL;
    listaLexerros = insereErro(listaLexerros, lexico.lexema, lexico.token, linha, descricaoErro);
}
void estado_77() {
    descricaoErro = "Caractere invalido";
    lexico.lexema = vetor;
    lexico.token = TK_CARACTERE_INVALIDO;
    listaLexerros = insereErro(listaLexerros, lexico.lexema, lexico.token, linha, descricaoErro);
}
void estado_78() {
    descricaoErro = "Valor char mal formatado";
    lexico.lexema = vetor;
    lexico.token = TK_VALOR_CHAR;
    listaLexerros = insereErro(listaLexerros, lexico.lexema, lexico.token, linha, descricaoErro);
}
void estado_79() {
    descricaoErro = "Delimitador de comentario '*/' em falta";
    lexico.lexema = vetor;
    lexico.token = TK_BLOCO_COMENTARIO;
    listaLexerros = insereErro(listaLexerros, lexico.lexema, lexico.token, linha, descricaoErro);
}

/**
* Tabela de ponteiros (fun��es)
* Cada estado deve estar declarada aqui, para
* poder ser acedido din�micamnete l� na fun��o analex
*/
void (*estados[])() = {
    estado_0, estado_1, estado_2, estado_3,
    estado_4, estado_5, estado_6, estado_7,
    estado_8, estado_9, estado_10, estado_11,
    estado_12, estado_13, estado_14, estado_15,
    estado_16, estado_17, estado_18, estado_19,
    estado_20, estado_21, estado_22, estado_23,
    estado_24, estado_25, estado_26, estado_27,
    estado_28, estado_29, estado_30, estado_31,
    estado_32, estado_33, estado_34, estado_35,
    estado_36, estado_37, estado_38, estado_39,
    estado_40, estado_41, estado_42, estado_43,
    estado_44, estado_45, estado_46, estado_47,
    estado_48, estado_49, estado_50, estado_51,
    estado_52, estado_53, estado_54, estado_55,
    estado_56, estado_57, estado_58, estado_59,
    estado_60, estado_61, estado_62, estado_63,
    estado_64, estado_65, estado_66, estado_67,
    estado_68, estado_69, estado_70, estado_71,
    estado_72, estado_73, estado_74, estado_75,
    estado_76, estado_77, estado_78, estado_79

};

/**
* Fun��o principal, respons�vel por chamar os estados
* e retorna o token, lexema e linha, assim que validar
*
*/
Lexico analex(FILE *arquivo) {
    while(!feof(arquivo)) {
        if(lexico.lexema != NULL) {
            lexico.linha = linha;
            voltaCaractere(arquivoCodFonte);
            estado = 0;
            return lexico;
        }
        c = lerCaracter(arquivo);
        estados[estado]();
    }
    lexico.token = EOF;
    return lexico;
}

/**
* Fun��o para esvaziar o vetor que armazena sequ�ncia de
* caracteres lidos ap�s valida��o
*/
void zerarVetor() {
	int i;
	for(i = 0; i < cont; i++) {
		vetor[i] = '\0';
	}
	cont = 0;
}
