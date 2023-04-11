#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <time.h>
#include <unistd.h>

int height, width;

void display_board(int board[height][width]);
void display_debug(int board[height][width]);
void initialize_zeroes(int board[height][width]);
void initialize_population(int board[height][width], int n);
void step(int board[height][width]);
int get_n_alive_neighbors(int board[height][width], int height_pos,
                          int width_pos);
int generate_number(int min, int max);

int main() {
  int init_pop;
  struct winsize w;
  srand(time(NULL));
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  height = w.ws_row - 1;
  width = w.ws_col;
  init_pop = (height * width) / 2;

  int board[height][width];
  initialize_zeroes(board);
  initialize_population(board, init_pop);
  while (1) {
    system("clear");
    display_board(board);
    step(board);
    // usleep(20000);
  }
  return EXIT_SUCCESS;
}

void display_board(int board[height][width]) {
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      printf("%c", (board[i][j] == 0) ? ' ' : '0');
    }
    printf("\n");
  }
}

void display_debug(int board[height][width]) {
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      printf("%d", board[i][j]);
    }
    printf("\n");
  }
}

void initialize_zeroes(int board[height][width]) {
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      board[i][j] = 0;
    }
  }
}

void initialize_population(int board[height][width], int n) {
  int rand_height, rand_width;
  int i = 0;
  while (i < n) {
    rand_height = generate_number(0, height - 1);
    rand_width = generate_number(0, width - 1);
    if (board[rand_height][rand_width] == 0) {
      board[rand_height][rand_width] = 1;
      ++i;
    }
  }
}

int get_n_alive_neighbors(int board[height][width], int height_pos,
                          int width_pos) {
  if ((height_pos == 0) && (width_pos == 0)) {
    return board[height_pos + 1][width_pos] + board[height_pos][width_pos + 1] +
           board[height_pos + 1][width_pos + 1];
  } else if ((height_pos == 0) && (width_pos == (width - 1))) {
    return board[height_pos][width_pos - 1] +
           board[height_pos + 1][width_pos - 1] +
           board[height_pos + 1][width_pos];
  } else if ((height_pos == (height - 1)) && (width_pos == 0)) {
    return board[height_pos - 1][width_pos] +
           board[height_pos - 1][width_pos + 1] +
           board[height_pos][width_pos + 1];
  } else if ((height_pos == (height - 1)) && (width_pos == (width - 1))) {
    return board[height_pos][width_pos - 1] +
           board[height_pos - 1][width_pos - 1] +
           board[height_pos - 1][width_pos];
  } else if (height_pos == (height - 1)) {
    return board[height_pos][width_pos - 1] +
           board[height_pos - 1][width_pos - 1] +
           board[height_pos - 1][width_pos] +
           board[height_pos - 1][width_pos + 1] +
           board[height_pos][width_pos + 1];
  } else if (width_pos == (width - 1)) {
    return board[height_pos - 1][width_pos] +
           board[height_pos - 1][width_pos - 1] +
           board[height_pos][width_pos - 1] +
           board[height_pos + 1][width_pos - 1] +
           board[height_pos + 1][width_pos];
  } else if (height_pos == 0) {
    return board[height_pos][width_pos - 1] +
           board[height_pos + 1][width_pos - 1] +
           board[height_pos + 1][width_pos] +
           board[height_pos + 1][width_pos + 1] +
           board[height_pos][width_pos + 1];
  } else if (width_pos == 0) {
    return board[height_pos - 1][width_pos] +
           board[height_pos - 1][width_pos + 1] +
           board[height_pos][width_pos + 1] +
           board[height_pos + 1][width_pos + 1] +
           board[height_pos + 1][width_pos];
  } else {
    return board[height_pos][width_pos - 1] +
           board[height_pos - 1][width_pos - 1] +
           board[height_pos - 1][width_pos] +
           board[height_pos - 1][width_pos + 1] +
           board[height_pos][width_pos + 1] +
           board[height_pos + 1][width_pos + 1] +
           board[height_pos + 1][width_pos] +
           board[height_pos + 1][width_pos - 1];
  }
}

void step(int board[height][width]) {
  int count;
  int copy_board[height][width];
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      count = get_n_alive_neighbors(board, i, j);
      if (board[i][j] == 1) {
        if (count < 2 || count > 3) {
          copy_board[i][j] = 0;
        }
      } else if (board[i][j] == 0 && count == 3) {
        copy_board[i][j] = 1;
      } else {
        copy_board[i][j] = 0;
      }
    }
  }
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      board[i][j] = copy_board[i][j];
    }
  }
}

int generate_number(int min, int max) {
  return (rand() % (max - min + 1)) + min;
}
