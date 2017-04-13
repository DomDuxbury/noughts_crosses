#include <stdio.h>
#include <stdlib.h>
#include <board.h>

enum boardState {EMPTY, NOUGHT, CROSS};

int** init_board(int m, int n) {
  int* values = calloc(m*n, sizeof(float));
  int** rows = malloc(n*sizeof(float*));
  for(int i=0; i<n; ++i) {
    rows[i] = values + i*m;
  }
  return rows;
}

void print_board(int** board) {
  printf("  1|2|3\n");
  for(int i=0; i<3; i++) {
    printf("%d", i+1);
    for(int j=0; j<3; j++) {
      char symbol = ' ';
      if(board[i][j] == NOUGHT) symbol = 'O';
      if(board[i][j] == CROSS) symbol = 'X';
      printf("|%c", symbol);
    }
    printf("\n");
  }
}
