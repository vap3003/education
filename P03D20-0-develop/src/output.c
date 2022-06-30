#include "graph.h"
#include "calc.h"
#include <string.h>

void calculate(const char* PN, double* data) {
  char rpn[NMAX];
  double dx = (4. * M_PI) / X_MAX;
  for (int i = 0; i < X_MAX; i++) {
    strcpy(rpn, PN);
    data[i] = calc(rpn, i * dx);
  }
}

void normalize(double* data, int* a) {
  double dy = 2. / (Y_MAX - 1);
  for (int i = 0; i < X_MAX; i++) {
    if (isnan(data[i])) {
      a[i] = -1000;
    } else {
      a[i] = round((data[i] + 1) / dy);
    }
  }
}

void output(const int* a) {
    for (int it = 0; it < Y_MAX; it++) {
        for (int jt = 0; jt < X_MAX; jt++) {
            if (a[jt] == it) {
                printf("*");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
}
