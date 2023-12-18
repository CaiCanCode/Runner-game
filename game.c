/*
    game.c
    Michaiah Williams
    2023-03-14 (pi day!!!)
    A cute little game that just prints in your command prompt but I want to turn it into a real game :)
    Inspired by Subway Surfer
*/
//#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


const int MIN_TIME = 400;
int wait_time;
int turn;
int max_row;
int max_col;

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
    for (int i = 5; i >= 0; i--){
        mvprintw(i + 6, 0, "|");
        for (int j = 0; j < 5; j++){
            mvprintw(11 - i, j + 1, "%c", board[i][j]);
        }
        mvprintw(i + 6, 6, "|\n");
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
    //avoid impossible boards, under construction
    if(board[4][1] == 'X' && board[4][2] == 'X' && board[4][3] == 'X' && num1 == 'X' && num2 == 'X' && num3 == 'X'){
        num2 = ' ';
    }
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

void left (player* me) {
    me->column -= 1;
    print_board(me);
    if(me->column == 0){
        if(me->sign != '*'){
            me->sign = '*';
        }
        me->score += turn;
        napms(wait_time);
        mvprintw(4, 0, "\nTurn: %d    Score: %d\n", turn, me->score);
        if(wait_time > MIN_TIME){
            wait_time -= turn;
        }
        halfdelay(wait_time/100);
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
        napms(wait_time);
        mvprintw(4, 0, "\nTurn: %d    Score: %d\n", turn, me->score);
        if(wait_time > MIN_TIME){
            wait_time -= turn;
        }
        halfdelay(wait_time/100);
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
    napms(MIN_TIME);
    mvprintw(4, 0, "\nTurn: %d    Score: %d\n", turn, me->score);
    if(wait_time > MIN_TIME){
        wait_time -= turn;
    }
    halfdelay(wait_time/100);
    turn++;
    update_board();
    if (1){
            int keystroke = getch();
            switch (keystroke) {
                case 'a':
                    if(me->column != 1){
                        me->column--;
                    }
                    break;
                case 'd':
                    if(me->column != 3){
                        me->column++;
                    }
                    break;
                case 'c':
                    print_board(me);
                    napms(500);
                    mvprintw(13, 0, "Game paused. Press any key to continue");
                    while(getch() != ERR){} //clear
                    while(getch() == ERR){} //wait
                    mvprintw(13, 0, "                                         ");
                    me->sign = '*';
                    return;
                case 'x':
                    print_board(me);
                    mvprintw(13, 0, "game ended\n");
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
    napms(MIN_TIME);
    mvprintw(4, 0, "\nTurn: %d    Score: %d\n", turn, me->score);
    if(wait_time > MIN_TIME){
        wait_time -= turn;
    }
    halfdelay(wait_time/100);    
    turn++;
    update_board();
    if (1){
            int keystroke = getch();
            switch (keystroke) {
                case 'a':
                    if(me->column != 1){
                        me->column--;
                    }
                    break;
                case 'd':
                    if(me->column != 3){
                        me->column++;
                    }
                    break;
                case 'c':
                    print_board(me);
                    napms(500);
                    mvprintw(13, 0, "Game paused. Press any key to continue");
                    while(getch() != ERR){} //clear
                    while(getch() == ERR){} //wait
                    me->sign = '*';
                    return;
                case 'x':
                    print_board(me);
                    mvprintw(13, 0, "game ended\n");
                    exit(0);
            }
    }
    me->sign = '*';
    print_board(me);
}

int main () {

    initscr();
    noecho();
    halfdelay(15);
    getmaxyx(stdscr,max_row,max_col);	

    while(1){
        turn = 0;
        wait_time = 1500;
        player me = {1, 0, 2, '*'};
        for (int i = 5; i > 0; i--){
            for (int j = 0; j < 5; j++){
                board[i][j] = ' ';
            }
        }
        mvprintw(0,0, "                                                                                                                 ");
        mvprintw(0,1, "                                                                                                                 ");
        mvprintw(0,2, "                                                                                                                 ");
        napms(500);
        mvprintw(0, 0, "Xs are obstacles, use wasd keys to avoid them.\n");
        napms(500);
        mvprintw(1, 0, "You can go off the edged but you will bounce back. w ans s go under and over the square, reprectively.\n");
        napms(500);
        mvprintw(2, 0, "Pressing x will exit the game, and pressing c will pause the game. \nPress any key to continue");
        while(getch() == ERR){} //wait
        while(me.alive){
            me.score += turn;
            if(turn){
                napms(MIN_TIME);
            }
            mvprintw(4, 0, "\nTurn: %d    Score: %d\n", turn, me.score);
            if(wait_time > MIN_TIME){
                wait_time -= turn;
            }
            halfdelay(wait_time/100);
            turn++;
            update_board();
            if (1){
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
                        napms(500);
                        mvprintw(13, 0, "Game paused. Press any key to continue");
                        while(getch() != ERR){} //clear
                        while(getch() == ERR){} //wait
                        mvprintw(13, 0, "                                           ");
                        break;
                    case 'x':
                        print_board(&me);
                        mvprintw(13, 0, "game ended\n");
                        return 0;
                    default:
                        print_board(&me);
                }
            } else {
                print_board(&me);
            }
        }
        napms(500);
        mvprintw(13, 0, "Game over :(\n");
        napms(1500);
        mvprintw(13, 0, "                            ");
        while(getch() != ERR){} //clear
    }
    return 0;
}
