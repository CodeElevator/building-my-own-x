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
  mpc_parser_t *Operator = mpc_new("operator");
  mpc_parser_t *Expr = mpc_new("expr");
  mpc_parser_t *PaperLang = mpc_new("paprlang");

  mpca_lang(MPCA_LANG_DEFAULT,
            "                                                     \
     number   : /-?[0-9]+/ ;                              \
     operator : '+' | '-' | '*' | '/' ;                   \
     expr     : <number> | '(' <operator> <expr>+ ')' ;   \
     paprlang    : /^/ <operator> <expr>+ /$/ ;              \
    ",
            Number, Operator, Expr, PaperLang);

  puts("PaperLang version 0.0.1");
  puts("Press CTRL+C to Exit");

  while (1) {
    char *input = readline("paprlang> ");
    add_history(input);

    mpc_result_t r;
    if (mpc_parse("<stdin>", input, PaperLang, &r)) {
      lval result = eval(r.output);
      lval_println(result);
      mpc_ast_delete(r.output);
    } else {
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }
    free(input);
  }

  mpc_cleanup(4, Number, Operator, Expr, PaperLang);
  return 0;
}
