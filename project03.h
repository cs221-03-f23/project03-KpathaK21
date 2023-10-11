#ifndef PROJECT03_H
#define PROJECT03_H

typedef char **board_t;

void init_board(board_t board, int size, char **argv);

void print_board(board_t board, int size);

int check_board(board_t board, int size);

void get_next_move(board_t board, int size);

#endif
