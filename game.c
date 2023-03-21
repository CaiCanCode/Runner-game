/*
    game.c
    Michaiah Williams
    2023-03-14 (pi day!!!)
    A cute little game that just prints in your command prompt but I want to turn it into a real game :)
    Inspired by Subway Surfer
*/
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

const int MIN_TIME = 400;
int wait_time = 1500;
int turn = 0;

typedef struct player{
    int alive;
    int score;
    int column;
    char sign;
} player;

char board[6][5];

void print_board(player* me){
    board[0][me->column] = (board[0][me->column] != 'X' || me->sign != '*')?me->sign:'^';
    if(board[0][me->column] == '^'){
        me->alive = 0;
    }
    printf(" _____ \n");
    for (int i = 5; i >= 0; i--){
        printf("|");
        for (int j = 0; j < 5; j++){
            printf("%c", board[i][j]);
        }
        printf("|\n");
    }
}

void generate_row (){
    time_t t;
    srand((unsigned) time(&t)); //Use system time to generate random numbers
    char num1 = (rand() % 3);
    num1 = num1?' ':'X';
    char num2 = (rand() % 3);
    num2 = num2?' ':'X';
    char num3 = (rand() % 3);
    num3 = num3?' ':'X';
    board[5][0] = ' ';
    board[5][1] = num1;
    board[5][2] = num2;
    board[5][3] = num3;
    board[5][4] = ' ';
    //avoid impossible boards, under construction
    if(board[4][1] == 'X' && board[4][2] == 'X' && board[4][3] == 'X' && num1 == 'X' && num2 == 'X' && num3 == 'X'){
        board[5][2] == ' ';
    }
}

void update_board(){
    for (int i = 1; i < 6; i++){
        for(int j = 0; j < 5; j++){
            board[i-1][j] = board[i][j];
        }
    }
    generate_row();
}

void left (player* me) {
    me->column -= 1;
    print_board(me);
    if(me->column == 0){
        if(me->sign != '*'){
            me->sign = '*';
        }
        me->score += turn;
        Sleep(wait_time);
        printf("\nTurn: %d    Score: %d\n", turn, me->score);
        if(wait_time > MIN_TIME){
            wait_time -= turn;
        }
        turn++;
        update_board();
        me->column = 1;
        print_board(me);
    }
}

void right (player* me) {
    me->column += 1;
    print_board(me);
    if(me->column == 4){
        if(me->sign != '*'){
            me->sign = '*';
        }
        me->score += turn;
        Sleep(wait_time);
        printf("\nTurn: %d    Score: %d\n", turn, me->score);
        if(wait_time > MIN_TIME){
            wait_time -= turn;
        }
        turn++;
        update_board();
        me->column = 3;
        print_board(me);
    }
}

void up (player* me) {
    me->sign = '#';
    print_board(me);
    me->score += turn;
    Sleep(wait_time);
    printf("\nTurn: %d    Score: %d\n", turn, me->score);
    if(wait_time > MIN_TIME){
        wait_time -= turn;
    }
        turn++;
    update_board();
    if (kbhit()){
            int keystroke = getch();
            switch (keystroke) {
                int e = 0;
                case 'a':
                    if(me->column == 1){
                        e = 1;
                    }
                    left(me);
                    if(e){
                        me->sign = '*';
                        return;
                    }
                    break;
                case 'd':
                    if(me->column == 3){
                        e = 1;
                    }
                    right(me);
                    if(e){
                        me->sign = '*';
                        return;
                    }
                    break;
                case 'c':
                    print_board(me);
                    printf("Game paused. Press enter to continue");
                    getchar();
                    me->sign = '*';
                    return;
                case 'x':
                    print_board(me);
                    printf("game ended\n");
                    exit(0);
            }
    }
    me->sign = '*';
    print_board(me);
}

void down (player* me) {
    me->sign = '-';
    print_board(me);
    me->score += turn;
    Sleep(wait_time);
    printf("\nTurn: %d    Score: %d\n", turn, me->score);
    if(wait_time > MIN_TIME){
        wait_time -= turn;
    }
        turn++;
    update_board();
    if (kbhit()){
            int keystroke = getch();
            switch (keystroke) {
                int e = 0;
                case 'a':
                    if(me->column == 1){
                        e = 1;
                    }
                    left(me);
                    if(e){
                        me->sign = '*';
                        return;
                    }
                    break;
                case 'd':
                    if(me->column == 3){
                        e = 1;
                    }
                    right(me);
                    if(e){
                        me->sign = '*';
                        return;
                    }
                    break;
                case 'c':
                    print_board(me);
                    printf("Game paused. Press enter to continue");
                    getchar();
                    me->sign = '*';
                    return;
                case 'x':
                    print_board(me);
                    printf("game ended\n");
                    exit(0);
            }
    }
    me->sign = '*';
    print_board(me);
}

int main () {
    player me = {1, 0, 2, '*'};
    for (int i = 5; i > 0; i--){
        for (int j = 0; j < 5; j++){
            board[i][j] = ' ';
        }
    }
    Sleep(500);
    printf("Xs are obstacles, use wasd keys to avoid them.\n");
    Sleep(500);
    printf("You can go off the edged but you will bounce back. w ans s go under and over the square, reprectively.\n");
    Sleep(500);
    printf("Pressing x will exit the game, and pressing c will pause the game. \nPress enter to continue");
    char isAdmin[10];
    fgets(isAdmin, 9, stdin);
    Sleep(500);
    while(me.alive){
        me.score += turn;
        if(turn){
            Sleep(wait_time);
        }
        printf("\nTurn: %d    Score: %d\n", turn, me.score);
        if(wait_time > MIN_TIME){
            wait_time -= turn;
        }
        turn++;
        update_board();
        if (kbhit()){
            int keystroke = getch();
            switch (keystroke) {
                case 'w':
                    up(&me);
                    break;
                case 's':
                    down(&me);
                    break;
                case 'a':
                    left(&me);
                    break;
                case 'd':
                    right(&me);
                    break;
                case 'c':
                    print_board(&me);
                    printf("Game paused. Press enter to continue");
                    getchar();
                    break;
                case 'x':
                    print_board(&me);
                    printf("game ended\n");
                    return 0;
                default:
                    print_board(&me);
            }
        } else {
            print_board(&me);
        }
        if(!me.alive && !strcmp(isAdmin, "admin\n")){
            printf("You should be dead lol but you're an immortal admin.\nResetting timer");
            wait_time = 1500;
            me.alive = 1;
        }
    }
    Sleep(500);
    printf("Game over :(\n");
    return 0;
}
