#ifndef SRC_CALC_H_
#define SRC_CALC_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "graph.h"

struct node {
  double value;
  struct node *next;
};

struct node *init(double d);

void push_c(double d, struct node **top);

double pop_c(struct node **top);

void destroy(struct node *top);

double calc(char *rpn, double x);


#endif  // SRC_CALC_H_
