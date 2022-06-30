#ifndef SRC_STACK_H_
#define SRC_STACK_H_

#define SIZE 100

struct steck {
  char mark[SIZE];
  int top;
};

typedef struct steck stk;

void create_stack(stk *s);
int is_full(stk *s);
int is_empty(stk *s);
int push(stk *s, char newitem);
int pop(stk *s);
char top(stk *s);
void print_stack(stk *s);

#endif  // SRC_STACK_H_
