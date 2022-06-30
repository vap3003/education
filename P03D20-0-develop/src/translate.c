#include <string.h>
#include <stdio.h>
#include "stack.h"
#include "translate.h"

int translate(char** str, char** PN, stk **s) {
    int response = 1;
    while (**str != '\n' && response) {
        if (check(**str)) {
            number(&str, &PN);
        } else {
            mark(&str, &s, &PN, &response);
        }
    }
    if (response) {
        while (!is_empty(*s)) {
            if (top(*s) != '(') {
                **PN = top(*s); (*PN)++;
                pop(*s);
                **PN = ' '; (*PN)++;
            } else {
                pop(*s);
                break;
            }
        }
    }
    return response;
}

int check(char str) {
    return ((str >= '0' && str <= '9') || str == 'x') ? 1 : 0;
}

void number(char*** a, char*** b) {
    int point = 1;
    if (***a == 'x') {
        ***b = ***a; (**a)++; (**b)++;
        point = 0;
    }
    while ((***a >= '0' && ***a <= '9') || (***a == '.' && point)) {
        if (***a == '.')
            point = 0;
        ***b = ***a;
        (**a)++; (**b)++;
    }
    ***b = ' '; (**b)++;
}

void mark(char*** a, stk ***s, char ***b, int* response) {
    char symbol;
    if (***a == '*' || ***a == '/' || ***a == '(' || ***a == '+') {
        symbol = ***a;
        (**a)++;
    } else if (***a == '-') {
        if (***(a-1) == '(') {
            symbol = '~'; (**a)++;
        } else {
            symbol = ***a; (**a)++;
        }
    } else if (***a == ')') {
        symbol = ***a; (**a)++;
    } else {
        char help[] = {'0', '0', '0', '0'};
        int i = 0;
        while (***a != '(' && i < 4) {
            help[i] = ***a; i++; (**a)++;
        }
        if (help[0] == 's' && help[1] == 'i' && help[2] == 'n') {
            symbol = 's';
        } else if (help[0] == 'c' && help[1] == 'o' && help[2] == 's') {
            symbol = 'c';
        } else if (help[0] == 'c' && help[1] == 't' && help[2] == 'g') {
            symbol = 'k';
        } else if (help[0] == 't' && help[1] == 'g') {
            symbol = 't';
        } else if (help[0] == 's' && help[1] == 'q' && help[2] == 'r' && help[3] == 't') {
            symbol = 'q';
        } else if (help[0] == 'l' && help[1] == 'n') {
            symbol = 'l';
        } else {
            *response = 0;
        }
    }
    if (response) {
        if (is_empty(**s)) {
            push(**s, symbol);
        } else if (symbol =='(') {
            push(**s, symbol);
        } else if (priority(top(**s)) <= priority(symbol)) {
                if (symbol == ')') {
                    while (top(**s) != '(') {
                        ***b = top(**s); (**b)++;
                        pop(**s);
                        ***b = ' '; (**b)++;
                    }
                    pop(**s);
                    if (top(**s) == 's' || top(**s) == 'c' || top(**s) == 'k'||
                        top(**s) == 't' || top(**s) == 'q' || top(**s) == 'l') {
                            ***b = top(**s); (**b)++;
                            pop(**s);
                            ***b = ' '; (**b)++;
                        }
                } else {
                    push(**s, symbol);
                }
        } else {
            while (!is_empty(**s)) {
                if (top(**s) != '(') {
                    ***b = top(**s); (**b)++;
                    pop(**s);
                    ***b = ' '; (**b)++;
                } else {
                    pop(**s);
                    break;
                }
            }
            push(**s, symbol);
        }
    }
}

int priority(char symb) {
    int result;
    switch (symb) {
        case '+' :
        case '-' : {result = 2; break;}
        case '*' :
        case '/' : {result = 3; break;}
        case '~' : {result = 4; break;}
        case 's' :
        case 'c' :
        case 't' :
        case 'k' :
        case 'q' :
        case 'l' : {result = 2; break;}
        case '(' : {result = 0; break;}
        case ')' : {result = 5; break;}
    }
    return(result);
}
