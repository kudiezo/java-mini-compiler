#include "analex.c"

int defType = 0;
int defDeclarator = 0;
int simboloInesperado = 1;
int quantidadeErros = 0;


void consumir() {
    zerarVetor();
    lexico.lexema = NULL;
    lexico.token = NULL;
    lexico.tipoDado = NULL;
    lexico.valorAtribuido = NULL;
    lexico = analex(arquivoCodFonte);
}

//Função de erro
void erro(const char* messagem) {
    quantidadeErros++;
    fprintf(stderr, "\n Linha %d: %s, antes de '%s'\n", lexico.linha, messagem, lexico.lexema);
    return;
}

//Funão de análise intática
void parse() {
    //Chamada inicial, não terminal raiz
    program();
    if(strcmp(lexico.token, EOF) != 0) {
        erro("\n\tNAO FOI POSSIVEL LER TODO ARQUIVO DE CODIGO FONTE\n");
    } else {
        if(quantidadeErros == 0)
            printf("\n NENHUM ERRO SINTATICO IDENTIFICADO!\n");
        else
            printf("\n TOTAL DE ERROS SINTATICOS IDENTIFICADOS: %d\n", quantidadeErros);
    }
}

void main(){
    //Inicializando lista onde vão estar as palavras reservadas
    keywords = iniListaKeywords();
    //Importando as palavras reservadas para a lista de keywords
    keywords = importarKeyWords(keywords);

    //Inicializando lista de erros léxicos
    listaLexerros = iniListaLexerros();

    //Abertura do arquivo de código fonte (entrada)
    arquivoCodFonte = fopen("codigoFonte.txt", "r");

    if(arquivoCodFonte == NULL)
        printf("Nao foi possivel abrir o arquivo de codigo fonte.");
    else {
        parse();

    }
    fclose(arquivoCodFonte);
    mostrarTodosLexerros(listaLexerros);
    if(qtdLexerros > 0)
        printf("\n TOTAL DE ERROS LEXICOS: %d", qtdLexerros);
    printf("\n\n");
    system("pause");
}

/**********IMPLEMENTAÇÃO DAS FUNÇÕES NÃO TERMINAIS*************/
void program() {

    package();

    while((strcmp(lexico.lexema, "import") != 0)
          &&(strcmp(lexico.lexema, "class") != 0)
          &&(strcmp(lexico.lexema, "public") != 0)) {
       erro("Simbolo inesperado!");
       consumir();
    }

    import();

    while((strcmp(lexico.lexema, "public") != 0)
          &&(strcmp(lexico.lexema, "class") != 0)) {
       erro("Simbolo inesperado!");
       consumir();
    }

    mainClass();

    if(strcmp(lexico.token, EOF) == 0)
        return;

    while(strcmp(lexico.lexema, "class") != 0) {
       erro("Simbolo inesperado!");
       consumir();
    }

    if(strcmp(lexico.token, EOF) == 0)
        return;

    classDecl();

    if(strcmp(lexico.token, EOF) == 0)
        return;

    while((strcmp(lexico.lexema, "class") != 0) && (strcmp(lexico.token, EOF) != 0)) {
        erro("Simbolo inesperado!");
        consumir();
        if(strcmp(lexico.token, EOF) == 0)
            return;
    }

    if(strcmp(lexico.token, EOF) == 0)
        return;

    while((strcmp(lexico.lexema, EOF) != 0)) {
        classDecl();
        if(strcmp(lexico.token, EOF) == 0)
            return;
    }

    if(strcmp(lexico.token, EOF) == 0)
        return;
}
void package() {
    consumir();
    if(strcmp(lexico.lexema, "package") == 0) {
        consumir();
        id();
        while(strcmp(lexico.token, TK_PONTO) == 0) {
            consumir();
            id();
        }
        if(strcmp(lexico.token, TK_PONTO_VIRGULA) != 0) {
            erro("Esperava-se ponto e virgula");
        } else consumir();
    }
}
void import() {
    while(strcmp(lexico.lexema, "import") == 0) {
        consumir();
        id();
        while(strcmp(lexico.token, TK_PONTO) == 0) {
            consumir();
            id();
        }
        if(strcmp(lexico.token, TK_PONTO_VIRGULA) != 0) {
            erro("Esperava-se ponto e virgula");
        } else consumir();
        while((strcmp(lexico.lexema, "public") != 0)
              &&(strcmp(lexico.lexema, "class") != 0)
              &&(strcmp(lexico.lexema, "import") != 0)) {
           erro("Simbolo inesperado!");
           consumir();
        }
    }
}

void mainClass() {
    if(strcmp(lexico.lexema, "public") == 0) {
        consumir();
    }
    if(strcmp(lexico.lexema, "class") == 0) {
        consumir();
        id();
        if(strcmp(lexico.token, TK_ABRE_CHAVETA) != 0) {
            erro("Esperava-se abertura de chaveta!");
        } else consumir();
        if(strcmp(lexico.lexema, "public") != 0) {
            erro("Esperava-se public");
        } else consumir();
        if(strcmp(lexico.lexema, "static") != 0) {
            erro("Esperava-se static");
        } else consumir();
        if(strcmp(lexico.lexema, "void") != 0) {
            erro("Esperava-se void");
        } else consumir();
        if(strcmp(lexico.lexema, "main") != 0) {
            erro("Esperava-se main");
        } else consumir();
        if(strcmp(lexico.token, TK_ABRE_PARENTESES) != 0) {
            erro("Esperava-se abertura de parenteses '('");
        } else consumir();
        if(strcmp(lexico.lexema, "String") != 0) {
            erro("Esperava-se o tipo de parametro 'String'");
        } else consumir();
        if(strcmp(lexico.token, TK_ABRE_COLCHETES) != 0) {
            erro("Esperava-se abertura de colchetes '['");
        } else consumir();
        if(strcmp(lexico.token, TK_FECHA_COLCHETES) != 0) {
            erro("Esperava-se fecho de colchetes']'");
        } else consumir();
        if(strcmp(lexico.token, TK_ID) != 0) {
            erro("Esperava-se um nome do parametro valido");
        } else consumir();
        if(strcmp(lexico.token, TK_FECHA_PARENTESES) != 0) {
            erro("Esperava-se fecho de parenteses ')'");
        } else consumir();
        if(strcmp(lexico.token, TK_ABRE_CHAVETA) != 0) {
            erro("Esperava-se abertura de chaveta '{'");
        } else consumir();

        statement();

        if(strcmp(lexico.token, TK_FECHA_CHAVETA) != 0) {
            erro("Esperava-se fecho de chaveta '}'");
        } else consumir();

        statement();

        if(strcmp(lexico.token, TK_FECHA_CHAVETA) != 0) {
            erro("Esperava-se fecho de chaveta '}'");
        } else consumir();
    }
}

void classDecl() {
    if(strcmp(lexico.lexema, "class") == 0) {
        consumir();
        id();
        if(strcmp(lexico.lexema, "extends") == 0) {
            consumir();
            id();
        }
        if(strcmp(lexico.token, TK_ABRE_CHAVETA) != 0) {
            erro("Esperava-se abertura de chaveta!");
        } else consumir();

        statement();

        if(strcmp(lexico.token, TK_FECHA_CHAVETA) != 0) {
            erro("Esperava-se fecho de chaveta '}'");
        } else consumir();
    }
}

void id() {
    if(strcmp(lexico.token, TK_ID) != 0) {
        erro("Esperava-se um nome valido!");
    } else consumir();
}

decl() {
    defType = 0;
    defDeclarator = 0;
    declarators();
    type();
    /*printf("-->%s %d", lexico.lexema, defType);
    system("pause");*/
    if(defType == 1) {
        simboloInesperado = 0;
        id();
        decl1();
    }
}
decl1() {
    if(strcmp(lexico.token, TK_PONTO_VIRGULA) == 0) {
        consumir();
    } else if(strcmp(lexico.token, TK_ABRE_PARENTESES) == 0) {
        consumir();
        methodDecl();
    } else if(strcmp(lexico.token, TK_OP_ATRIBUICAO) == 0) {
        consumir();
        expression();
        if(strcmp(lexico.token, TK_PONTO_VIRGULA) != 0) {
            erro("Esperava-se ponto e virgula ';'");
        } consumir();
    } else if(strcmp(lexico.token, TK_ABRE_COLCHETES) == 0) {
        consumir();
        expression();
        if(strcmp(lexico.token, TK_FECHA_COLCHETES) != 0) {
            erro("Esperava-se fecho de colchetes ']'");
        } consumir();
        if(strcmp(lexico.token, TK_OP_ATRIBUICAO) == 0) {
            consumir();
            expression();
        }
        if(strcmp(lexico.token, TK_PONTO_VIRGULA) != 0) {
            erro("Esperava-se ponto e virgula ';'");
        } consumir();
    } else if(defDeclarator == 1 || defType == 1) {
        if(defType == 0)
            erro("Esperava-se um tipo valido");
        erro("Esperava-se ponto e virgula");
    }
}
methodDecl() {
    //consumir();
    parametersList();
    if(strcmp(lexico.token, TK_FECHA_PARENTESES) != 0) {
        erro("Esperava-se fecho de parenteses");
    } else consumir();
    if(strcmp(lexico.token, TK_ABRE_CHAVETA) != 0) {
        erro("Esperava-se abertura de chaveta");
    } else consumir();
    statement();

    if(strcmp(lexico.lexema, "return") == 0) {
        consumir();
        expression();
        if(strcmp(lexico.token, TK_PONTO_VIRGULA) != 0) {
            erro("Esperava-se ponto e virgula");
        } else consumir();
    }

    if(strcmp(lexico.token, TK_FECHA_CHAVETA) != 0) {
        erro("Esperava-se fecho de chaveta");
    } else consumir();
}

void declarators() {
    //consumir();
    while((strcmp(lexico.lexema, "public") == 0)||(strcmp(lexico.lexema, "private") == 0)
       ||(strcmp(lexico.lexema, "static") == 0)||(strcmp(lexico.lexema, "final") == 0)
          ||(strcmp(lexico.lexema, "protected") == 0)) {
        defDeclarator = 1;
        consumir();
    }
}

type() {
    defType = 0;
    primType();
    /*if(defType == 0)
        classType();*/
    arrType();

}
primType() {
    if((strcmp(lexico.lexema, "int") == 0)||(strcmp(lexico.lexema, "boolean") == 0)
       ||(strcmp(lexico.lexema, "float") == 0)||(strcmp(lexico.lexema, "double") == 0)
       ||(strcmp(lexico.lexema, "char") == 0)||(strcmp(lexico.lexema, "byte") == 0)
       ||(strcmp(lexico.lexema, "short") == 0)||(strcmp(lexico.lexema, "long") == 0)
       ||(strcmp(lexico.lexema, "void") == 0)) {
        consumir();
        defType = 1;
    }
}
classType() {
    if(strcmp(lexico.token, TK_ID) == 0) {
        consumir();
        defType = 1;
    }
}
arrType() {
    if(strcmp(lexico.token, TK_ABRE_COLCHETES) == 0) {
        consumir();
        expression();
        if(defType == 0) erro("Esperava-se um nome valido para o vetor");
        if(strcmp(lexico.token, TK_FECHA_COLCHETES) != 0) {
            erro("Esperava-se fecho de colchetes");
        } else consumir();
    }
}

ifStmt() {
    if(strcmp(lexico.lexema, "if") == 0) {
        simboloInesperado = 0;
        consumir();
        if(strcmp(lexico.token, TK_ABRE_PARENTESES) != 0) {
            erro("Esperava-se abertura de parenteses '('");
        } else consumir();
        if(strcmp(lexico.token, TK_FECHA_PARENTESES) == 0) {
            erro("Esperava-se condicao");
        }
        expression();
        if(strcmp(lexico.token, TK_FECHA_PARENTESES) != 0) {
            erro("Esperava-se fecho de parenteses ')'");
        } else consumir();

        statement();

        if(strcmp(lexico.lexema, "else") == 0) {
            statement();
        }
    }
}
whileStmt() {
    if(strcmp(lexico.lexema, "while") == 0) {
        simboloInesperado = 0;
        consumir();
        if(strcmp(lexico.token, TK_ABRE_PARENTESES) != 0) {
            erro("Esperava-se abertura de parenteses '('");
        } else consumir();
        if(strcmp(lexico.token, TK_FECHA_PARENTESES) == 0) {
            erro("Esperava-se condicao");
        }
        expression();
        if(strcmp(lexico.token, TK_FECHA_PARENTESES) != 0) {
            erro("Esperava-se fecho de parenteses ')'");
        } else consumir();

        statement();
    }
}
doWhileStmt() {
    if(strcmp(lexico.lexema, "do") == 0) {
        simboloInesperado = 0;
        consumir();
        if(strcmp(lexico.token, TK_ABRE_CHAVETA) != 0) {
            erro("Esperava-se abertura de chaveta '{'");
        } else consumir();

        statement();

        if(strcmp(lexico.token, TK_FECHA_CHAVETA) != 0) {
            erro("Esperava-se fecho de chaveta '}'");
        } else consumir();
        if(strcmp(lexico.lexema, "while") != 0) {
            erro("Esperava-se a keyword 'while'");
        } else consumir();
        if(strcmp(lexico.token, TK_ABRE_PARENTESES) != 0) {
            erro("Esperava-se abertura de parenteses '('");
        } else consumir();
        expression();
        if(strcmp(lexico.token, TK_FECHA_PARENTESES) != 0) {
            erro("Esperava-se fecho de parenteses ')'");
        } else consumir();
        if(strcmp(lexico.token, TK_PONTO_VIRGULA) != 0) {
            erro("Esperava-se ponto e virgula ';'");
        } else consumir();
    }
}
forStmt() {
    if(strcmp(lexico.lexema, "for") == 0) {
        simboloInesperado = 0;
        consumir();        if(strcmp(lexico.token, TK_ABRE_PARENTESES) != 0) {
            erro("Esperava-se abertura de parenteses '('");
        } else consumir();
        if(strcmp(lexico.token, TK_FECHA_PARENTESES) == 0) {
            erro("Esperava-se os controloladores do 'for'");
        }
        parametersList();
        if(strcmp(lexico.token, TK_FECHA_PARENTESES) == 0) {
            erro("Esperava-se os controloladores do 'for'");
        }
        expression();
        if(strcmp(lexico.token, TK_PONTO_VIRGULA) != 0) {
            erro("Esperava-se ponto e virgula ';'");
        } else consumir();
        if(strcmp(lexico.token, TK_PONTO_VIRGULA) == 0) {
            erro("Esperava-se a condicao");
        }
        expression();
        if(strcmp(lexico.token, TK_PONTO_VIRGULA) != 0) {
            erro("Esperava-se ponto e virgula ';'");
        } else consumir();
        if(strcmp(lexico.token, TK_FECHA_PARENTESES) == 0) {
            erro("Esperava-se o controlador");
        }
        expression();
        if(strcmp(lexico.token, TK_FECHA_PARENTESES) != 0) {
            erro("Esperava-se fecho de parenteses ')'");
        } else consumir();

        statement();
    }
}

parametersList() {
    defType = 0;
    type();
    if(defType == 1) {
        id();
        if(strcmp(lexico.token, TK_VIRGULA) == 0) {
            consumir();
            parametersList();
        }
    }
}

statement() {
    simboloInesperado = 1;
    if((strcmp(lexico.token, TK_COMENTARIO) == 0)
        ||(strcmp(lexico.token, TK_BLOCO_COMENTARIO) == 0)) {
        consumir();
    }
    while(strcmp(lexico.lexema, "System") == 0)
        printStmt();
    decl();
    ifStmt();
    forStmt();
    whileStmt();
    assignment();
    doWhileStmt();
    blockStatement();
    if(simboloInesperado == 1 && (strcmp(lexico.token, TK_FECHA_CHAVETA) != 0)){
        erro("Simbolo inesperado!");
        consumir();
    }
    while(strcmp(lexico.lexema, "return") != 0 && (strcmp(lexico.token, TK_FECHA_CHAVETA) != 0)) {
        statement();
    }
}
blockStatement() {
    if(strcmp(lexico.token, TK_ABRE_CHAVETA) == 0) {
        simboloInesperado = 0;
        consumir();

        statement();

        if(strcmp(lexico.token, TK_FECHA_CHAVETA) != 0) {
            erro("Esperava-se fecho de chaveta '}'");
        } else consumir();
    }
}

void printStmt() {
    if(strcmp(lexico.lexema, "System") == 0) {
        simboloInesperado = 0;
        consumir();
        if(strcmp(lexico.token, TK_PONTO) != 0) {
            erro("Esperava-se ponto '.'");
        } else consumir();
        if(strcmp(lexico.lexema, "out") != 0) {
            erro("Esperava-se um nome valido, como 'out'");
        } else consumir();
        if(strcmp(lexico.token, TK_PONTO) != 0) {
            erro("Esperava-se ponto '.'");
        } else consumir();
        if((strcmp(lexico.lexema, "print") != 0)
           &&(strcmp(lexico.lexema, "println") != 0)
           &&(strcmp(lexico.lexema, "printf") != 0)) {
            erro("Esperava-se um nome valido, como 'print ou println'");
             if(strcmp(lexico.token, TK_ID) == 0) consumir();
        } else consumir();
        if(strcmp(lexico.token, TK_ABRE_PARENTESES) != 0) {
            erro("Esperava-se abertura de parenteses '('");
        } else consumir();

        expression();

        if(strcmp(lexico.token, TK_FECHA_PARENTESES) != 0) {
            erro("Esperava-se fecho de parenteses ')'");
        } else consumir();
        if(strcmp(lexico.token, TK_PONTO_VIRGULA) != 0) {
            erro("Esperava-se ponto e virgula ';'");
        } else consumir();
    }
}

void expression() {
    expression1();
    expression2();
}
void expression1() {
    references();
    expression4();
    if((strcmp(lexico.token, TK_NUM_INTEIRO) == 0)
       ||(strcmp(lexico.token, TK_NUM_REAL) == 0)
       ||(strcmp(lexico.token, TK_VALOR_CHAR) == 0)
       ||(strcmp(lexico.lexema, "false") == 0)
       ||(strcmp(lexico.lexema, "true") == 0)
       ||(strcmp(lexico.token, TK_VALOR_STRING) == 0)) {
        consumir();
    }
}
void expression4() {
    if(strcmp(lexico.token, TK_ABRE_COLCHETES) == 0) {
        consumir();
        expression();
        if(strcmp(lexico.token, TK_FECHA_COLCHETES) != 0) {
            erro("Esperava-se fecho de colchetes ']'");
        } else consumir();
        expression2();
    }
    if(strcmp(lexico.token, TK_ABRE_PARENTESES) == 0) {
        consumir();
        argumentList();
        if(strcmp(lexico.token, TK_FECHA_PARENTESES) != 0) {
            erro("Esperava-se fecho de parenteses ')'");
        } else consumir();
        expression2();
    }
    if(strcmp(lexico.token, TK_PONTO) == 0) {
        consumir();
        if(strcmp(lexico.lexema, "length") != 0) {
            erro("Esperava-se um nome valido, como 'length...'");
        } else consumir();
        expression2();
    }
}
void expression2() {
    if((strcmp(lexico.token, TK_OP_ATRIBUICAO) == 0)||(strcmp(lexico.token, TK_OP_DIVISAO) == 0)
    ||(strcmp(lexico.token, TK_OP_DIVISAO_ATRIBUICAO) == 0)||(strcmp(lexico.token, TK_OP_MAIS) == 0)
    ||(strcmp(lexico.token, TK_OP_INCREMENTO) == 0)||(strcmp(lexico.token, TK_OP_SOMA_ATRIBUICAO) == 0)
    ||(strcmp(lexico.token, TK_OP_MENOS) == 0)||(strcmp(lexico.token, TK_OP_DECREMENTO) == 0)
    ||(strcmp(lexico.token, TK_OP_SUBTRACAO_ATRIBUICAO) == 0)||(strcmp(lexico.token, TK_OP_MULTIPLICACAO) == 0)
    ||(strcmp(lexico.token, TK_OP_MULTIPLICACAO_ATRIBUICAO) == 0)||(strcmp(lexico.token, TK_OP_IGUAL) == 0)
    ||(strcmp(lexico.token, TK_OP_XOR_BIT_A_BIT) == 0)||(strcmp(lexico.token, TK_OP_XOR_BIT_A_BIT_ATRIBUICAO) == 0)
    ||(strcmp(lexico.token, TK_OP_OR_BIT_A_BIT) == 0)||(strcmp(lexico.token, TK_OP_OR_BIT_A_BIT_ATRIBUICAO) == 0)
    ||(strcmp(lexico.token, TK_OP_OR) == 0)||(strcmp(lexico.token, TK_OP_AND_BIT_A_BIT) == 0)
    ||(strcmp(lexico.token, TK_OP_AND_BIT_A_BIT) == 0)||(strcmp(lexico.token, TK_OP_AND_BIT_A_BIT_ATRIBUICAO) == 0)
    ||(strcmp(lexico.token, TK_OP_AND) == 0)||(strcmp(lexico.token, TK_OP_DIFERENTE) == 0)
    ||(strcmp(lexico.token, TK_OP_MODULO) == 0)||(strcmp(lexico.token, TK_OP_MODULO_ATRIBUICAO) == 0)
    ||(strcmp(lexico.token, TK_OP_MENOR) == 0)||(strcmp(lexico.token, TK_OP_MENOR_IGUAL) == 0)
    ||(strcmp(lexico.token, TK_OP_DESLOCAMENTO_LEFT) == 0)||(strcmp(lexico.token, TK_OP_DESLOCAMENTO_LEFT_ATRIBUICAO) == 0)
    ||(strcmp(lexico.token, TK_OP_MAIOR) == 0)||(strcmp(lexico.token, TK_OP_MAIOR_IGUAL) == 0)
    ||(strcmp(lexico.token, TK_OP_DESLOCAMENTO_RIGHT) == 0)||(strcmp(lexico.token, TK_OP_DESLOCAMENTO_RIGHT_ATRIBUICAO) == 0)
    ||(strcmp(lexico.token, TK_OP_COMPLEMENTO_BIT_A_BIT) == 0)||(strcmp(lexico.token, TK_OP_NOT) == 0)) {
        consumir();
        expression();
        expression2();
    }
    if(strcmp(lexico.token, TK_ABRE_COLCHETES) == 0) {
        consumir();
        expression();
        if(strcmp(lexico.token, TK_FECHA_COLCHETES) != 0) {
            erro("Esperava-se fecho de colchetes '}'");
        } consumir();
        if(strcmp(lexico.token, TK_OP_ATRIBUICAO) != 0) {
            erro("Esperava-se operador de atribuicao '='");
        } consumir();
        expression();
    }
    if(strcmp(lexico.lexema, "new") == 0) {
        consumir();
        type();
        if(defType == 1) {
            if(strcmp(lexico.token, TK_ABRE_COLCHETES) == 0) {
                consumir();
                expression();
                if(strcmp(lexico.token, TK_FECHA_COLCHETES) != 0) {
                    erro("Esperava-se fecho de colchetes ']'");
                } consumir();
            }
        } else if(strcmp(lexico.token, TK_ID) == 0) {
            id();
            if(strcmp(lexico.token, TK_ABRE_PARENTESES) != 0) {
                erro("Esperava-se abertura de parenteses '('");
            } consumir();
            argumentList();
            if(strcmp(lexico.token, TK_FECHA_PARENTESES) != 0) {
                erro("Esperava-se fecho de parenteses ')'");
            } consumir();
        } else erro("Esperava-se um nome da classe valido para instanciar");
    }
}

void argumentList() {
    expression();
    while(strcmp(lexico.token, TK_VIRGULA) == 0) {
        consumir();
        expression();
    }
}

void assignment() {
    references();
    if(strcmp(lexico.token, TK_OP_ATRIBUICAO) == 0) {
        simboloInesperado = 0;
        consumir();
        expression();
        if(strcmp(lexico.token, TK_PONTO_VIRGULA) != 0) {
            erro("Esperava-se ponto e virgula");
        } else consumir();
    } else if(strcmp(lexico.token, TK_ABRE_COLCHETES) == 0) {
        simboloInesperado = 0;
        consumir();
        expression();
        if(strcmp(lexico.token, TK_FECHA_COLCHETES) != 0) {
            erro("Esperava-se fecho de colchetes ']'");
        } else consumir();
        if(strcmp(lexico.token, TK_OP_ATRIBUICAO) == 0) {
            consumir();
            expression();
        } else erro("Esperava-se operador de atribuicao '='");
        if(strcmp(lexico.token, TK_PONTO_VIRGULA) != 0) {
            erro("Esperava-se ponto e virgula");
        } else consumir();
    } else if (strcmp(lexico.token, TK_ABRE_PARENTESES) == 0) {
        simboloInesperado = 0;
        consumir();
        argumentList();
        if(strcmp(lexico.token, TK_FECHA_PARENTESES) != 0) {
            erro("Esperava-se fecho de parenteses ')'");
        } else consumir();
        if(strcmp(lexico.token, TK_PONTO_VIRGULA) != 0) {
            erro("Esperava-se ponto e virgula ';'");
        } else consumir();
    } else if (strcmp(lexico.token, TK_OP_INCREMENTO) == 0) {
        simboloInesperado = 0;
        consumir();
        if(strcmp(lexico.token, TK_PONTO_VIRGULA) != 0) {
            erro("Esperava-se ponto e virgula ';'");
        } else consumir();
    }
}

void references() {
    if(strcmp(lexico.lexema, "this") == 0) {
        consumir();
        if(strcmp(lexico.token, TK_PONTO) != 0) {
            erro("Esperava-se ponto '.'");
        } else consumir();
        if(strcmp(lexico.token, TK_ID) != 0) {
            erro("Esperava-se um nome valido");
        } else consumir();
        if(strcmp(lexico.token, TK_PONTO) == 0) {
            consumir();
            references();
        }
    } else if(strcmp(lexico.token, TK_ID) == 0) {
        consumir();
        if(strcmp(lexico.token, TK_PONTO) == 0) {
            consumir();
            references();
        }
    }
}


