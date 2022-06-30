#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"
#include "graph.h"

int main() {
    char *str = malloc(NMAX*sizeof(char));
    char *PN = malloc(NMAX*sizeof(char));
    char *len;
    len = PN;
    char *to_free = str;
    fgets(str, NMAX, stdin);
    stk *s = (stk*)malloc(sizeof(stk));
    create_stack(s);
    if (translate(&str, &PN, &s)) {
        double *data = malloc(X_MAX * sizeof(double));
        int *out = malloc(X_MAX * sizeof(int));
        calculate(len, data);
        normalize(data, out);
        output(out);
        free(data);
        free(out);
    } else {
        printf("Неверное выражение!");
    }
    free(s);
    free(to_free);
    free(len);
}
