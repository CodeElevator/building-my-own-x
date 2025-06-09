#ifndef EVAL_H
#define EVAL_H

#include "./library/mpc.h"  // required for mpc_ast_t

// Value Types
enum { LVAL_NUM, LVAL_ERR };

// Error Types
enum { LERR_DIV_ZERO, LERR_BAD_OP, LERR_BAD_NUM };

// Lisp Value Struct
typedef struct {
  int type;
  long num;
  int err;
} lval;

// Constructors
lval lval_num(long x);
lval lval_err(int x);

// Eval functions
lval eval_op(lval x, char* op, lval y);
lval eval(mpc_ast_t* t);

// Print
void lval_print(lval v);
void lval_println(lval v);

#endif
