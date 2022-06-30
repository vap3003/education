#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>
#include <stdlib.h>
#include <math.h>
#define NMAX 25
#define MMAX 80

int** initMatrix(int n, int m);
int input(int** matrix, int columns, int rows);
void renderAll(int **matrix, int columns, int rows, int round, int speed_level);
void copy_data(int **data, int **new_data, int n, int m);
void calculate_matrix(int **data, int **new_data, int n, int m);
void copy(int **from, int **to, int n, int m);
// int isEqual(int **a, int **b, int n, int m);
void gameOver(int rows, int round);
void add_hash(int **data, int round, long long int *hash_array);
int check_hash(const long long int *hash_array, int round);
void start_game(int rows);

int main() {
    int result = 0, n = NMAX, m = MMAX;
    long long int* hash_array = malloc(1 * sizeof(long long int));
    int** data = initMatrix(m, n);
    int** nextData = initMatrix(m, n);
        if ( !input(data, m, n) ) {
            int speed_level = 3, round = 0;
            int sec = 1, usec = 500000;  // setting timeout for one round
        if (!freopen("/dev/tty", "r", stdin))
            printf("try again");  // stdin back to terminal
        // printf("Data is loaded successfully, now starting the game!\n");
        start_game(n);
        system("stty -echo");  // supress echo
        system("stty cbreak");  // go to RAW mode
        while (1) {
            struct timeval timeout = {sec, usec};
            fd_set fds;
            FD_ZERO(&fds);
            FD_SET(STDIN_FILENO, &fds);
            int ret = select(1, &fds, NULL, NULL, &timeout);
            if (ret == -1) {
                printf("Oops! Something wrong happened...\n");
            } else if (ret == 0) {
                round++;
                switch (speed_level) {
                    case 1 : {sec = 5; usec = 0; break;}
                    case 2 : {sec = 2; usec = 500000; break;}
                    case 3 : {sec = 1; usec = 0; break;}
                    case 4 : {sec = 0; usec = 500000; break;}
                    case 5 : {sec = 0; usec = 200000; break;}
                    case 6 : {sec = 0; usec = 50000; break;}
                    default : {sec = 1; usec = 0; break;}
                }
                if ( round % 2 ) {
                    calculate_matrix(nextData, data, n, m);
                    add_hash(data, round, hash_array);
                    if (check_hash(hash_array, round)) {
                        gameOver(n, round);
                        break;
                    }
                    renderAll(data, m, n, round, speed_level);
                } else {
                    calculate_matrix(data, nextData, n, m);
                    add_hash(nextData, round, hash_array);
                    if (check_hash(hash_array, round)) {
                        gameOver(n, round);
                        break;
                    }
                    renderAll(nextData, m, n, round, speed_level);
                }
            } else {
                char ch = getchar();
                if (ch == 'q' || ch == 'Q')
                    break;
                if (ch == 'a' || ch == 'A')
                    speed_level = (speed_level <= 5) ? speed_level + 1 : 6;
                if (ch == 'z' || ch == 'Z')
                    speed_level = speed_level > 2 ? speed_level - 1 : 1;
            }
        }
        system("stty echo");   // Make echo work
        system("stty -cbreak");  // go to COOKED mode
        } else {
            result = 1;
        }
    free(data);
    free(nextData);
    free(hash_array);
    return result;
}

int** initMatrix(int n, int m) {
    int **matrix = malloc(m * n * sizeof(int) + m * sizeof(int*) );
    int* ptr = (int*) (matrix + m);
        for (int i = 0; i < m; i++)
            matrix[i] = ptr + n*i;
    return matrix;
}

int input(int** matrix, int columns, int rows) {
    const char inputSymbol = 'x';
    char c;
    int res = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            scanf("%c", &c);
            if ( c == ' ' ) {
                matrix[i][j] = 0;
            } else if ( c == inputSymbol ) {
                matrix[i][j] = 1;
            } else {
                res = 1;
                printf("Incorrect data in %d:%d. Expected %d chars in line, each space or '%c'",
                                                            i, j, columns-1, inputSymbol);
                break;
            }
        }
        if ( res )
            break;
        while ( scanf("%c", &c) && c != '\n' ) {
        }
    }
    return res;
}

void renderAll(int **matrix, int columns, int rows, int round, int speed_level) {
    printf("\033[0d\033[2J\r");
    const char symbol = '*';
    for (int i = 0; i < rows + 1; i++) {
        for (int j = 0; j < columns + 1; j++) {
            if (i == 0 || i == rows || j == 0 || j == columns) {
                printf("#");
            } else {
                printf("%c", (matrix[i - 1][j - 1]) ? symbol : ' ');
            }
        }
        printf("\n");
    }
    printf("Generation: %d\n", round);
    switch (speed_level) {
        case 1 : {printf("Speed: very slow\n"); break;}
        case 2 : {printf("Speed: slow\n"); break;}
        case 3 : {printf("Speed: medium\n"); break;}
        case 4 : {printf("Speed: high\n"); break;}
        case 5 : {printf("Speed: very high\n"); break;}
        case 6 : {printf("Speed: EXTREMLY HIGH\n"); break;}
        default : {printf("Speed: medium\n"); break;}
    }
    printf("Speed change: A/Z\n");
    printf("Exit: Q\n");
}

void calculate_matrix(int **data, int **new_data, int n, int m) {
    int sum;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            sum = data[(i - 1 + n) % n][(j - 1 + m) % m] + data[(i - 1 + n) % n][j] +
                data[(i - 1 + n) % n][(j + 1 + m) % m] +
                data[i][(j - 1 + m) % m] + data[i][(j + 1 + m) % m] +
                data[(i + 1 + n) % n][(j - 1 + m) % m] +
                data[(i + 1 + n) % n][j] + data[(i + 1 + n) % n][(j + 1 + m) % m];
            if (data[i][j] == 1 && (sum < 2 || sum > 3)) {
                new_data[i][j] = 0;
            } else if (data[i][j] == 0 && sum == 3) {
                new_data[i][j] = 1;
            }
        }
    }
    copy_data(data, new_data, n, m);
}

void copy_data(int **data, int **new_data, int n, int m) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            data[i][j] = new_data[i][j];
}

void add_hash(int **data, int round, long long int *hash_array) {
    long long int hash = 0;
    for (int i = 0; i < NMAX; i++)
        for (int j = 0; j < MMAX; j++)
           hash = (int)(hash + data[i][j] * (pow(2, i) + j)) % 2099999920999999;
    if (round > 1)
        hash_array = realloc(hash_array, round);
    hash_array[round-1] = hash;
}

int check_hash(const long long int *hash_array, int round) {
    int res = 0;
    long long int checker = hash_array[round-1];
    for (int i = 0; i < round - 1; i++) {
        if (hash_array[i] == checker) {
            res = 1;
            break;
        }
    }
    return res;
}

void start_game(int rows) {
    printf("\033[0d\033[2J\r");
    for (int i = 0; i < rows + 1; i++) {
        if (i == 0 || i == rows || i == 8 || i == 16)
            printf("#################################################################################\n");
        else if (i == 10)
            printf("#                     ####  ######  ####   #####  ######                        #\n");
        else if (i == 11)
            printf("#                    ##       ##   ##  ##  ##  ##   ##                          #\n");
        else if (i == 12)
            printf("#                     ####    ##   ######  #####    ##                          #\n");
        else if (i == 13)
            printf("#                        ##   ##   ##  ##  ##  ##   ##                          #\n");
        else if (i == 14)
            printf("#                     ####    ##   ##  ##  ##  ##   ##                          #\n");
        else if (i == 18)
            printf("#                                 MAP LOADING...                                #\n");
        else
            printf("#                                                                               #\n");
    }
}

void gameOver(int rows, int round) {
    printf("\033[0d\033[2J\r");
    for (int i = 0; i < rows + 1; i++) {
        if (i == 0 || i == rows || i == 9 || i == 17)
            printf("#################################################################################\n");
        else if (i == 7)
            printf("#                             LAST GENERATION - #%-5d                          #\n",
            round);
        else if (i == 11)
            printf("#            ####   ####  ##   ## #####     ####  ##  ## ##### ####             #\n");
        else if (i == 12)
            printf("#           ##     ##  ## ### ### ##       ##  ## ##  ## ##    ##  ##           #\n");
        else if (i == 13)
            printf("#           ## ### ###### ## # ## ####     ##  ## ##  ## ####  #####            #\n");
        else if (i == 14)
            printf("#           ##  ## ##  ## ##   ## ##       ##  ##  ####  ##    ##  ##           #\n");
        else if (i == 15)
            printf("#            ####  ##  ## ##   ## #####     ####    ##   ##### ##  ##           #\n");
        else
            printf("#                                                                               #\n");
    }
}
