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

const int MIN_TIME = 400;
int time = 1500;
int turn = 0;

typedef struct player{
    int score;
    int column;
    char sign;
} player;

char board[6][5];

void print_board(player* me){
    board[0][me->column] = (board[0][me->column] == ' ' || me->sign != '*')?me->sign:'^';
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
}

void update_board(){
    for (int i = 1; i < 6; i++){
        for(int j = 0; j < 5; j++){
            board[i-1][j] = board[i][j];
        }
    }
    generate_row();
}

int up (player me) {
    me.sign = '#';
    print_board(&me);
    me.score += turn;
    Sleep(time);
    printf("\nScore: %d\n", me.score);
    if(time > MIN_TIME){
        time -= turn;
    }
        turn++;
    update_board();
    me.sign = '*';
    print_board(&me);
    return board[0][me.column] != '^';
}

int down (player me) {
    me.sign = '-';
    print_board(&me);
    me.score += turn;
    Sleep(time);
    printf("\nScore: %d\n", me.score);
    if(time > MIN_TIME){
         time -= turn;
    }
        turn++;
    update_board();
    me.sign = '*';
    print_board(&me);
    return board[0][me.column] != '^';
}

int left (player* me) {
    me->column -= 1;
    print_board(me);
    if(me->column == 0){
        me->score += turn;
        Sleep(time);
        printf("\nScore: %d\n", me->score);
        if(time > MIN_TIME){
            time -= turn;
        }
        turn++;
        update_board();
        me->column = 1;
        print_board(me);
    }
    return board[0][me->column] != '^';
}

int right (player* me) {
    me->column += 1;
    print_board(me);
    if(me->column == 4){
        me->score += turn;
        Sleep(time);
        printf("\nScore: %d\n", me->score);
        if(time > MIN_TIME){
            time -= turn;
        }
        turn++;
        update_board();
        me->column = 3;
        print_board(me);
    }
    return board[0][me->column] != '^';
}


int main () {
    player me = {0, 2, '*'};
    int alive = 1;
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
    while(alive){
        me.score += turn;
        if(turn){
            Sleep(time);
        }
        printf("\nScore: %d\n", me.score);
        if(time > MIN_TIME){
            time -= turn;
        }
        turn++;
        update_board();
        if (kbhit()){
            int keystroke = getch();
            switch (keystroke) {
                case 'w':
                    alive = up(me);
                    break;
                case 's':
                    alive = down(me);
                    break;
                case 'a':
                    alive = left(&me);
                    break;
                case 'd':
                    alive = right(&me);
                    break;
                case 'c':
                    printf("Game paused. Press enter to continue");
                    getchar();
                    break;
                case 'x':
                printf("game ended\n");
                    return 0;
                default:
                    alive = (board[0][me.column] == ' ');
                    print_board(&me);
            }
        } else {
            alive = (board[0][me.column] == ' ');
            print_board(&me);
        }
        if(!alive && !strcmp(isAdmin, "admin\n")){
            printf("You should be dead lol but you're an immortal admin.\nResetting timer");
            time = 1500;
            alive = 1;
        }
    }
    Sleep(500);
    printf("Game over :(\n");
    return 0;
}