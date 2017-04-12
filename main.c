#include <stdio.h>
#include <stdlib.h>

enum boardState {EMPTY, NOUGHT, CROSS};

int get_next_move(char position) {

  int invalid_input = 1;
  int next_move;
  printf("Enter the %c of you next move: ", position);

  while(invalid_input) {

    int input;
    int success = scanf("%d", &input);

    if (success == 1 && input < 4 && input > 0) {
      invalid_input = 0;
    } else {
      printf("Invalid input, try again:");
      char c;
      while((c = getchar()) != '\n' && c != EOF);
    }

    next_move = input;
  }

  return next_move;

}

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

int check_next(int** board, int player, int depth, 
    int x, int y, int x_direction, int y_direction) {

  int piece_here = 0;
  int piece_next = 1;
  
  if (x < 3 && y < 3 && x > -1 && y > -1) {
    piece_here = player == board[x][y];
  }

  x = x+x_direction;
  y = y+y_direction;

  if (depth < 2) {
    piece_next = check_next(board, player, ++depth, 
        x, y, x_direction, y_direction);
  }  

  return piece_here && piece_next;
}

int check_for_winner(int** board) {
  int winner = 0;

  for (int player = 1; player < 3; player++) {

    int possibilities[8] = {
      check_next(board, player, 0, 0, 0, 1, 0),
      check_next(board, player, 0, 0, 0, 0, 1),
      check_next(board, player, 0, 0, 0, 1, 1),
      check_next(board, player, 0, 2, 0, -1, 1),
      check_next(board, player, 0, 1, 0, 0, 1),
      check_next(board, player, 0, 2, 0, 0, 1),
      check_next(board, player, 0, 0, 1, 1, 0),
      check_next(board, player, 0, 0, 2, 1, 0)
    };

    for(int i=0; i<8; i++) {
      if(possibilities[i]) {
        winner = player;
      }
    }

  }
  
  return winner;
}

int switch_player(int player) {
  if(player == NOUGHT) {
    return CROSS;
  }
  return NOUGHT;
}

void take_turn(int** board, int player) {
  int invalid_turn = 1;
  while(invalid_turn) {

    int next_x = get_next_move('x');
    int next_y = get_next_move('y');
    /* printf("%d", board[next_x-1][next_y-1] */

    if (board[next_y-1][next_x-1]) {
      printf("A position must be empty, try again\n");
    } else {
      board[next_y-1][next_x-1] = player;
      invalid_turn = 0;
    }
  }
}

int play_game() {
  int** board = init_board(3, 3);
  int winner = 0;
  int current_player = NOUGHT;

  while(!winner) {
    take_turn(board, current_player);
    current_player = switch_player(current_player);
    winner = check_for_winner(board);
    print_board(board);
  }
  return winner;
}

int announce_winner(int winner) {
  if (winner == NOUGHT) {
    printf("The mighty noughts have won!!");
  }
  if (winner == CROSS) {
    printf("Crosses have won!!!");
  }
}

int main(void) {
  int winner = play_game();
  announce_winner(winner);
  return 0;
}
