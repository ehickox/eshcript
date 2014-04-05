#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mpc.h"

#ifdef _WIN32

#include <string.h>

static char buffer[2049];

/* Fake readline */
char* readline(char* prompt){
    fputs("ESHcript> ", stdout);
    fgets(buffer, 2048, stdin);
    char* cpy = malloc(strlen(buffer)+1);
    strcpy(cpy, buffer);
    cpy[strlen(cpy)-1] = '\0';
    return cpy;
}

/* Fake add_history */
void add_history(char unused) {}

/* Otherwise include the editline (readline) headers */
#else

#include <readline/readline.h>
#include <readline/history.h>

#endif

int main(int argc, char** argv) {

    /* Create Parsers */
    mpc_parser_t* Number = mpc_new("number");
    mpc_parser_t* Operator = mpc_new("operator");
    mpc_parser_t* Expr = mpc_new("expr");
    mpc_parser_t* ESHcript = mpc_new("eshcript");

    /* Define them with the following language */
    mpca_lang(MPC_LANG_DEFAULT,
        "                                                           \
            number      : /-?[0-9]+/ ;                              \
            operator    : '+' | '-' | '*' | '/' ;                   \
            expr        : <number> | '(' <operator> <expr>+ ')' ;   \
            eshcript    : /^/ <operator> <expr>+ /$/ ;              \
        ",
        Number, Operator, Expr, ESHcript);

    /* Print Version and Exit Information */
    puts("ESHcript Version 0.0.0.0.2");
    puts("Press Ctrl+c to Exit\n");
                
    /* In a never ending loop */
    while (1) {
        char* input = readline("ESHcript> ");
        add_history(input);

        /*Attempt to parse the user input */
        mpc_result_t r;
        if(mpc_parse("<stdin>", input, ESHcript, &r)){
            //print and delete the AST
            mpc_ast_print(r.output);
            mpc_ast_delete(r.output);
        } else{
            //print and delete the error
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        }

        /* Free retrieved input */
        free(input);
    }

    /* Undefine and delete parsers */
    mpc_cleanup(4, Number, Operator, Expr, ESHcript);

    return 0;
}

