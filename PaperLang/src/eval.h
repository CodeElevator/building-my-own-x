#ifndef EVAL_H
#define EVAL_H

#include "./library/mpc.h" // required for mpc_ast_t

// Value Types
enum { LVAL_ERR, LVAL_NUM, LVAL_SYM, LVAL_SEXPR };
// Error Types
enum { LERR_DIV_ZERO, LERR_BAD_OP, LERR_BAD_NUM };

// Lisp Value Struct
typedef struct lval {
  int type;
  long num;
  char *err;
  char *sym;
  int count;
  struct lval **cell;
} lval;

// Constructors
lval *lval_num(long x);
lval *lval_err(char *x);
lval *lval_sym(char *s);
lval *lval_sexpr(void);
void lval_del(lval *v);
lval *lval_read_num(mpc_ast_t *t);
lval *lval_add(lval *v, lval *x);
lval *lval_read(mpc_ast_t *t);

// Eval functions
lval *lval_eval_sexpr(lval *v);
lval *lval_eval(lval *v);
lval *lval_pop(lval *v, int i);
lval *lval_take(lval *v, int i);
lval *builtin_op(lval *a, char *op);

// Print
void lval_expr_print(lval *v, char open, char close);
void lval_print(lval *v);
void lval_println(lval *v);

#endif
