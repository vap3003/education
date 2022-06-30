#include "calc.h"

struct node *init(double d) {
  struct node *t;
  t = (struct node*)malloc(sizeof(struct node));
  t -> value = d;
  t -> next = NULL;
  return t;
}

void push_c(double d, struct node **t) {
  struct node *new_top;
  new_top = init(d);
  new_top -> next = *t;
  *t = new_top;
}

double pop_c(struct node **t) {
  struct node *new_top;
  double d;
  new_top = (*t) -> next;
  d = (*t) -> value;
  free(*t);
  *t = new_top;
  return d;
}

void destroy(struct node *t) {
  if (t -> next != NULL) {
    destroy(t -> next);
  }
  free(t);
}

double calc(char *rpn, double x) {
  double res = 0, n, a, b;
  struct node *stack;
  char *token;
  token = strtok(rpn, " ");
  sscanf(token, "%lf", &n);
  stack = init(n);
  while (token != NULL) {
      if (sscanf(token, "%lf", &n)) {
        res = n;
      } else {
        switch (token[0]) {
          case 'x': {
            res = x;
            break;
          }
          case '+': {
            b = pop_c(&stack);
            a = pop_c(&stack);
            res = a + b;
            break;
          }
          case '-': {
            b = pop_c(&stack);
            a = pop_c(&stack);
            res = a - b;
            break;
          }
          case '*': {
            b = pop_c(&stack);
            a = pop_c(&stack);
            res = a * b;
            break;
          }
          case '^': {
            b = pop_c(&stack);
            a = pop_c(&stack);
            res = pow(a, b);
            break;
          }
          case '/': {
            b = pop_c(&stack);
            a = pop_c(&stack);
            res = a / b;
            break;
          }
          case 's': {
            a = pop_c(&stack);
            res = sin(a);
            break;
          }
          case 'c': {
            a = pop_c(&stack);
            res = cos(a);
            break;
          }
          case 'k': {
            a = pop_c(&stack);
            res = 1./(tan(a));
            break;
          }
          case 't': {
            a = pop_c(&stack);
            res = tan(a);
            break;
          }
          case 'q': {
            a = pop_c(&stack);
            res = sqrt(a);
            break;
          }
          case 'l': {
            a = pop_c(&stack);
            res = log(a);
            break;
          }
          case '~': {
            a = pop_c(&stack);
            res = -a;
            break;
          }
        }
      }
          push_c(res, &stack);
      token = strtok(NULL, " ");
  }
  destroy(stack);
  return res;
}
