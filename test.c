#include "project03.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    int board_size = 3; // Default board size
    board_t b;
    if (argc>9){
        if (strcmp(argv[1], "-s") == 0) 
        {
            board_size = atoi(argv[2]);
            argc -= 2;
            argv += 2;
            b = (char**)malloc(board_size * sizeof(char*));
            for (int i = 0; i < board_size; i++) {
                b[i] = (char*)malloc(board_size * sizeof(char));
            }
            init_board(b, board_size, argv);
            print_board(b, board_size);
            get_next_move(b, board_size);
        }

        else
                {
                    board_size=3;
                    b = (char**)malloc(board_size * sizeof(char*));
                    for (int i = 0; i < board_size; i++) {
                        b[i] = (char*)malloc(board_size * sizeof(char));
                    }
                    init_board(b, board_size, argv);
                    print_board(b, board_size);
                    get_next_move(b, board_size);
                }
            }
            else
                {
                    // Loop to play a full game with human ('X') and computer ('O')
                    b = (char**)malloc(board_size * sizeof(char*));
                    for (int i = 0; i < board_size; i++) {
                    b[i] = (char*)malloc(board_size * sizeof(char));
                    }

                    argv[1] = "_";
                            argv[2] = "_";
                            argv[3] = "_";
                            argv[4] = "_";
                            argv[5] = "_";
                            argv[6] = "_";
                            argv[7] = "_";
                            argv[8] = "_";
                            argv[9] = "_";
                            init_board(b, board_size, argv);
                            print_board(b, board_size);

                            int game_result = check_board(b, board_size);
                                
                                while (game_result == 2) {
                                  // Human's turn ('X')
                                  int row, col;
                                  printf("Enter your move (row and column, e.g., '0 0'): ");
                                  scanf("%d %d", &row, &col);
                                  if (row >= 0 && row < board_size && col >= 0 && col <board_size &&
                                      b[row][col] == '_') {
                                    b[row][col] = 'X';
                                  } else {
                                    printf("Invalid move! Try again.\n");
                                    continue;
                                  }

                                        print_board(b, board_size);
      game_result = check_board(b, board_size);
      
      if (game_result != 2)
        break;

      // Computer's turn ('O')
      get_next_move(b, board_size);
      print_board(b, board_size);
      game_result = check_board(b, board_size);
    }

    // Print the game result
    switch (game_result) {
      case 1:
        printf("X wins\n");
        break;
      case -1:
        printf("O wins\n");
        break;
      default:
        printf("draw\n");
    }
  
    }
    

   
}
