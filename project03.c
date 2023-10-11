#include "project03.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to check if a player has won
int has_player_won(board_t board, int size, char player) {
  // Check rows and columns for a win
  for (int i = 0; i < size; i++) {
    bool row_win = true;
    bool col_win = true;

    for (int j = 0; j < size; j++) {
      if (board[i][j] != player) {
        row_win = false;
      }
      if (board[j][i] != player) {
        col_win = false;
      }
    }

    if (row_win || col_win) {
      return (player == 'X') ? 1 : -1; // 'X' wins (1) or 'O' wins (-1)
    }
  }

  // Check diagonals for a win
  bool diag1_win = true;
  bool diag2_win = true;
  for (int i = 0; i < size; i++) {
    if (board[i][i] != player) {
      diag1_win = false;
    }
    if (board[i][size - 1 - i] != player) {
      diag2_win = false;
    }
  }

  if (diag1_win || diag2_win) {
    return (player == 'X') ? 1 : -1; // 'X' wins (1) or 'O' wins (-1)
  }

  return 0; // No winner yet, game is ongoing
}

// Function to check if the board is full (a draw)
bool is_board_full(board_t board, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (board[i][j] == '_') {
        return false; // Empty cell found, the board is not full
      }
    }
  }
  return true; // No empty cell, the board is full (a draw)
}

// Function to check the current state of the board
int check_board(board_t board, int size) {
  int x_win = has_player_won(board, size, 'X');
  int o_win = has_player_won(board, size, 'O');

  if (x_win == 1 || o_win == 1) {
    return 1; // 'X' wins
  } else if (x_win == -1 || o_win == -1) {
    return -1; // 'O' wins
  } else if (is_board_full(board, size)) {
    return 0; // It's a draw
  } else {
    return 2; // Game is ongoing
  }
}

int score(board_t board, int size) {
  // Check for a win for 'O'
  int check = false;
  for (int i = 0; i < size; i++) {
    // // Check rows and columns
    // if (board[i][0] == 'O' && board[i][1] == 'O' && board[i][2] == 'O')
    // return 1; if (board[0][i] == 'O' && board[1][i] == 'O' && board[2][i] ==
    // 'O') return 1;
    for (int j = 0; j < size; j++) {
      if (board[i][j] == 'O') {
        check = true;
      } else {
        check = false;
        break;
      }
    }
    if (check == true) {
      return 1;
    }
  }

  // now check for columns
  for (int i = 0; i < size; i++) {
    // // Check rows and columns
    
    for (int j = 0; j < size; j++) {
      if (board[j][i] == 'O') {
        check = true;
      } else {
        check = false;
        break;
      }
    }
    if (check == true) {
      return 1;
    }

    // Check diagonals
    for (int i = 0; i < size; i++) {
      if (board[i][i] == 'O') {
        check = true;
      } else {
        check = false;
        break;
      }
    }
    if (check == true) {
      return 1;
    }
    for (int i = 0; i < size; i++) {
      if (board[i][size - i - 1] == 'O') {
        check = true;
      } else {
        check = false;
        break;
      }
    }
    if (check == true) {
      return 1;
    }
  }

  // Check for a win for 'X'
  for (int i = 0; i < size; i++) {
    // // Check rows and columns
    // if (board[i][0] == 'X' && board[i][1] == 'X' && board[i][2] == 'X')
    // return -1; if (board[0][i] == 'X' && board[1][i] == 'X' && board[2][i] ==
    // 'X') return -1;
    for (int j = 0; j < size; j++) {
      if (board[i][j] == 'X') {
        check = true;
      } else {
        check = false;
        break;
      }
    }
    if (check == true) {
      return -1;
    }
  }

  // now check for columns
  for (int i = 0; i < size; i++) {
    // // Check rows and columns
    // if (board[i][0] == 'X' && board[i][1] == 'X' && board[i][2] == 'X')
    // return -1; if (board[0][i] == 'X' && board[1][i] == 'X' && board[2][i] ==
    // 'X') return -1;
    for (int j = 0; j < size; j++) {
      if (board[j][i] == 'X') {
        check = true;
      } else {
        check = false;
        break;
      }
    }
    if (check == true) {
      return -1;
    }
  }

  // Check diagonals
  for (int i = 0; i < size; i++) {
    if (board[i][i] == 'X') {
      check = true;
    } else {
      check = false;
      break;
    }
  }
  if (check == true) {
    return -1;
  }
  for (int i = 0; i < size; i++) {
    if (board[i][size - i - 1] == 'X') {
      check = true;
    } else {
      check = false;
      break;
    }
  }

  // No winner yet, it's a draw
  return 0;
}

// Minimax algorithm for 'O' to determine the optimal move
int minimax(board_t board, int size, int depth, bool is_maximizer) {

  int currentScore = score(board, size);

  // If the game has ended or depth is reached, return the score
  if (currentScore != 0 || depth == 0 || is_board_full(board, size)) {
    return currentScore;
  }

  if (is_maximizer) {
    int bestScore = INT_MIN;
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        if (board[i][j] == '_') {
          board[i][j] = 'O'; // Make a move for 'O'
          int score = minimax(board, size,0, false);
          board[i][j] = '_'; // Undo the move

          if (score > bestScore) {
            bestScore = score;
          }
        }
      }
    }
    return bestScore;
  } else {
    int bestScore = INT_MAX;
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        if (board[i][j] == '_') {
          board[i][j] = 'X'; // Make a move for 'X'
          int score = minimax(board, size, 0, true);
          board[i][j] = '_'; // Undo the move

          if (score < bestScore) {
            bestScore = score;
          }
        }
      }
    }
    return bestScore;
  }
}

// Function to find the best move for 'O'
void get_next_move(board_t board, int size) {

  bool emptyboard = true;
  // Check if the board is full empty
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (board[i][j] != '_') {
        emptyboard = false;
        break;
      }
    }
  }
  if (emptyboard == true) {
    board[0][0] = 'O';
    printf("O: %d %d\n", 0, 0);
    return;
  }
  int bestScore = INT_MIN;
  int bestMoveRow = -1;
  int bestMoveCol = -1;

  // Check for offensive move (win if possible)
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (board[i][j] == '_') {
        board[i][j] = 'O';
        if (score(board, size) == 1) {
          printf("O: %d %d\n", i, j);
          return; // Winning move found, no need to consider other moves
        }
        board[i][j] = '_'; // Reset the move
      }
    }
  }

  // If there are no immediate winning moves, perform minimax for defensive
  // moves
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (board[i][j] == '_') {
        // Try defensive move (block the opponent from winning)
        board[i][j] = 'X';
        if (score(board, size) == -1) {
          board[i][j] = 'O'; // Block the opponent's winning move
        } else {
          board[i][j] = '_'; // Reset the move if it's not a winning move
        }

        // Calculate the score for the move
        int moveScore = minimax(board, size, size * size, false);
        board[i][j] = '_'; // Undo the move

        if (moveScore >  bestScore) {
          bestScore = moveScore;
          bestMoveRow = i;
          bestMoveCol = j;
        }
      }
    }
  }

  // If no winning moves are found, make the best defensive move
  if (bestMoveRow != -1 && bestMoveCol != -1) {
    board[bestMoveRow][bestMoveCol] = 'O';
    printf("O: %d %d\n", bestMoveRow, bestMoveCol);
  }
}

// Function to initialize the board
void init_board(board_t board, int size, char **argv) {

  int k = 1;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      board[i][j] = argv[k][0]; // Start from argv[3] for initial state
      k++;
    }
  }
}

// Function to print the board
void print_board(board_t board, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      printf("%c", board[i][j]);
      if (j < size - 1)
        printf(" | ");
    }
    printf("\n");
    if (i < size - 1) {
      for (int j = 0; j < size; j++) {
        printf("---");
        if (j < size - 1)
          printf("+");
      }
      printf("\n");
    }
  }
}
