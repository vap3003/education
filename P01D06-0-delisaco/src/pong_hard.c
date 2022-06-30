#include <ncurses.h>
//#include <stdlib.h>

// объявление глобальных переменных
int saved_position_player_1, // переменная хранит координату центра ракетки игрока 1 по вертикали
    saved_position_player_2, // переменная хранит координату центра ракетки игрока 2 по вертикали
    score_player_1, // переменная хранит счет игрока 1
    score_player_2, // переменная хранит счет игрока 2
    saved_position_ball_x, // переменная хранит координату мяча по горизонтали
    saved_position_ball_y, // переменная хранит координату мяча по вертикали
    ball_vector_x, /* переменная может принимать значения {1; -1} – если мяч движется вправо 
                   переменная принимает значение 1, если мяч движется влево 
                   переменная принимает значение -1*/
    ball_vector_y, /* переменная может принимать значения {1; -1} – если мяч движется вверх 
                   переменная принимает значение 1, если мяч движется вправо 
                   переменная принимает значение -1*/
    winner; // переменная передает номер игрока - победителя {1; 2}

// объявление функций
int finish_page(void);
int start_page(void);
int print_field(int x, int y, char type);
int ball_movement(void);

int main(){
    char comand; // переменная в которую считываются нажатые клавиши
    initscr();
    curs_set(0);
    keypad(stdscr, true);
    start_page(); // показываем стартовый экран
    do { // ожидаем нажатия клавиш "S" или "E"
        comand = getch(); // считывание нажатой клавиши
        if (comand == 'e' || comand == 'E') return 0; // выход из игры
        else start_page(); // очищает экран, если введены символы не {'s' 'S' 'e' 'E'}
    } while ((comand != 's' && comand != 'S'));
    print_field(1, 1, 's'); // вывод игрового поля с ракетками и мячом в стартовом положении
    do { //основной ход игры до нажатия клавиши "E"
        switch ( getch() ) {
            case 'a' : 
            case 'A' : { if (saved_position_player_1 > 2) print_field(1, saved_position_player_1 - 1, 'p'); ball_movement(); break;}
            case 'z' : 
            case 'Z' : { if (saved_position_player_1 < 24) print_field(1, saved_position_player_1 + 1, 'p'); ball_movement(); break;}
            case 'm' : 
            case 'M' : { if (saved_position_player_2 < 24) print_field(80, saved_position_player_2 + 1, 'p'); ball_movement(); break;}
            case 'k' : 
            case 'K' : { if (saved_position_player_2 > 2) print_field(80, saved_position_player_2 - 1, 'p'); ball_movement(); break;}
            case 'e' : 
            case 'E' : { endwin(); return 0; break;}
        }
    } while (true);
    endwin(); 
    return 0;
}

// Функция "finish_page" выводится после достижения одним из игроков 21 очка
int finish_page () {
    clear();
    printw("##################################################################################\n");
    for (int i = 0; i < 10; i++) {
        printw("#                                                                                #\n");
    }
    printw("#                                PLAYER %d WIN!                                   #\n", winner);
    printw("#                                                                                #\n");
    printw("#                                                                                #\n");
    printw("#                                                                                #\n");
    printw("#                               PRESS 'E' FOR EXIT                               #\n");
    printw("#                                                                                #\n");
    printw("#                                                                                #\n");
    for (int i = 0; i < 9; i++) {
        printw("#                                                                                #\n");
    }
    printw("##################################################################################\n");
    return 0;
}

// Функция "start_page" выводится при запуске программы
int start_page() {
    clear();
    printw("##################################################################################\n");
    for (int i = 0; i < 10; i++) {
        printw("#                                                                                #\n");
    }
    printw("#                Player 1               vc              Player 2                 #\n");
    printw("#                                                                                #\n");
    printw("#                                                                                #\n");
    printw("#                                                                                #\n");
    printw("#                          PRESS 'S' FOR START THE GAME                          #\n");
    printw("#                                                                                #\n");
    printw("#                               PRESS 'E' FOR EXIT                               #\n");
    for (int i = 0; i < 9; i++) {
        printw("#                                                                                #\n");
    }
    printw("##################################################################################\n");
    return 0;
}
// функция print_field отвечает за отображение актуального экрана 
int print_field(int x, int y, char type) {
    clear(); // очищаем экран
    printw(">> PLAYER 1  %03d                          >> PLAYER 2  %03d                        \n", score_player_1, score_player_2);
    if (type == 's') {
        saved_position_player_1 = 13;
        saved_position_player_2 = 13;
        saved_position_ball_x = 2;
        saved_position_ball_y = 13;
        score_player_1 = 0;
        score_player_2 = 0;
        ball_vector_x = 1;
        ball_vector_y = 1;
    }
    else if (type == 'p' && x == 1) saved_position_player_1 = y;
    else if (type == 'p' && x == 80) saved_position_player_2 = y;
    for (int i = 0; i <= 26; i++) {
        for (int j = 0; j <= 81; j++) {
            if (i == 0 || i == 26 || j == 0 || j == 81) printw("#"); // вывод границ поля
            else if (j == saved_position_ball_x && i == saved_position_ball_y) printw("o"); // вывод шара
            else if (j == 1 && i == saved_position_player_1 - 1) printw("]"); // вывод левой ракетки
            else if (j == 1 && i == saved_position_player_1) printw("]"); // вывод левой ракетки
            else if (j == 1 && i == saved_position_player_1 + 1) printw("]"); // вывод левой ракетки
            else if (j == 80 && i == saved_position_player_2 - 1) printw("["); // вывод правой ракетки
            else if (j == 80 && i == saved_position_player_2) printw("["); // вывод правой ракетки
            else if (j == 80 && i == saved_position_player_2 + 1) printw("["); // вывод правой ракетки
            else if (j == 41 || j == 42) printw("|"); // вывод сетки
            else printw(" ");
           }
        printw("\n");
    }
    return 0;
}

// функция "ball-movement" обрабатывает движение мяча и определяет координаты мяча на текущем шаге
int ball_movement() {
    if (saved_position_ball_y + ball_vector_y == 26) { // обработка столкновения с нижней границей
        ball_vector_y *= -1;
    } 
    else if (saved_position_ball_y + ball_vector_y == 0) { // обработка столкновения с верхней границей
        ball_vector_y *= -1;       
    }
    if (saved_position_ball_x + ball_vector_x == 80) { // обработка столкновения с правой границей
        if (saved_position_player_2 == saved_position_ball_y) ball_vector_x *= -1;
        else if (saved_position_player_2 - 1 == saved_position_ball_y) ball_vector_x *= -1;
        else if (saved_position_player_2 + 1 == saved_position_ball_y) ball_vector_x *= -1;
        else { // игрок 1 зарабатывает очко
            score_player_1++;
            if (score_player_1 >= 21) {
                winner = 1;
                finish_page();
                return 0;
            }
            ball_vector_x = 1;
            saved_position_ball_x = 2;
            saved_position_ball_y = 13;
            saved_position_player_1 = 13;
            saved_position_player_2 = 13;
            print_field(1, 1, 'r');
            return 0;
        }
    } else if (saved_position_ball_x + ball_vector_x == 1) { // обработка столкновения с левой границей
        if (saved_position_player_1 == saved_position_ball_y) ball_vector_x *= -1;
        else if (saved_position_player_1 - 1 == saved_position_ball_y) ball_vector_x *= -1;
        else if (saved_position_player_1 + 1 == saved_position_ball_y) ball_vector_x *= -1;
        else { // игрок 2 зарабатывает очко
            score_player_2++;
            if (score_player_2 >= 21) {
                winner = 2;
                finish_page();
                return 0;
            }
            ball_vector_x = -1;
            saved_position_ball_x = 79;
            saved_position_ball_y = 13;
            saved_position_player_1 = 13;
            saved_position_player_2 = 13;
            print_field(1, 1, 'r');
            return 0;
        }
    }
    saved_position_ball_y += ball_vector_y; // сохранение новых координат мяча по вертикали
    saved_position_ball_x += ball_vector_x; // сохранение новых координат мяча по горизонтали
    print_field(1, 1, 'b'); // вывод игрового поля с новой позицией мяча на экран 
    return 0;
}