#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32

static char buffer[2048];

char *readline(char *prompt) {
  fputs(prompt, stdout);
  fgets(buffer, 2048, stdin);
  char *cpy = malloc(strlen(buffer) + 1);
  strcpy(cpy, buffer);
  cpy[strlen(cpy) - 1] = '\0';
  return cpy;
}

void add_history(char *unused) {}

#else
#include <readline/history.h>
#include <readline/readline.h>
#endif
#include "eval.h"

int main(int argc, char **argv) {
  mpc_parser_t *Number = mpc_new("number");
  mpc_parser_t *Symbol = mpc_new("symbol");
  mpc_parser_t *Sexpr = mpc_new("sexpr");
  mpc_parser_t *Qexpr = mpc_new("qexpr");
  mpc_parser_t *Expr = mpc_new("expr");
  mpc_parser_t *PaperLang = mpc_new("paprlang");

  mpca_lang(MPCA_LANG_DEFAULT,
            "                                                    \
    number : /-?[0-9]+/ ;                              \
    symbol : \"list\" | \"head\" | \"tail\"                \
           | \"join\" | \"eval\" | '+' | '-' | '*' | '/' ; \
    sexpr  : '(' <expr>* ')' ;                         \
    qexpr  : '{' <expr>* '}' ;                         \
    expr   : <number> | <symbol> | <sexpr> | <qexpr> ; \
    paprlang  : /^/ <expr>* /$/ ;                         \
  ",
            Number, Symbol, Sexpr, Qexpr, Expr, PaperLang);
  puts("PaperLang version 0.0.3");
  puts("Press CTRL+C to Exit");

  while (1) {
    char *input = readline("paprlang> ");
    add_history(input);

    mpc_result_t r;
    if (mpc_parse("<stdin>", input, PaperLang, &r)) {
      lval *x = lval_eval(lval_read(r.output));
      lval_println(x);
      lval_del(x);
      mpc_ast_delete(r.output);
    } else {
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }
    free(input);
  }

  mpc_cleanup(6, Number, Symbol, Sexpr, Qexpr, Expr, PaperLang);
  return 0;
}
