#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


void create_stack(stk *s) {
  s -> top = -1;
}

int is_full(stk *s) {
    return (s->top == SIZE - 1) ? 1 : 0;
}

int is_empty(stk *s) {
    return (s->top == -1) ? 1 : 0;
}

int push(stk *s, char newitem) {
    int response = 1;
    if (!is_full(s)) {
        s->top++;
        s->mark[s->top] = newitem;
    } else {
      response = 0;
    }
    return(response);
}

int pop(stk *s) {
    int response = 1;
    if (!is_empty(s)) {
        s->top--;
    } else {
        response = 0;
    }
    return(response);
}

char top(stk *s) {
    return(s->mark[s->top]);
}
