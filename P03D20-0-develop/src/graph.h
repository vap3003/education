#ifndef SRC_GRAPH_H_
#define SRC_GRAPH_H_
#include "stack.h"
#define NMAX 100
#define X_MAX 80
#define Y_MAX 25

int translate(char** str, char** PN, stk **s);
void calculate(const char* PN, double* data);
void normalize(double* data, int *a);
void output(const int* a);


#endif  // SRC_GRAPH_H_
