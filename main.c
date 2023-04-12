#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <time.h>
#include <unistd.h>

unsigned int height, width;

void display_board(unsigned int board[height][width]);
void display_debug(unsigned int board[height][width]);
void initialize_zeroes(unsigned int board[height][width]);
void initialize_population(unsigned int board[height][width], unsigned int n);
void step(unsigned int board[height][width]);
unsigned int get_n_alive_neighbors(unsigned int board[height][width],
                                   unsigned int height_pos,
                                   unsigned int width_pos);
unsigned int generate_number(unsigned int min, unsigned int max);

int main() {
  unsigned int init_pop;
  struct winsize w;
  srand(time(NULL));
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  height = w.ws_row - 1;
  width = w.ws_col;
  init_pop = (height * width) / 2.71828182846;

  unsigned int board[height][width];
  initialize_zeroes(board);
  initialize_population(board, init_pop);
  while (1) {
    system("clear");
    display_board(board);
    step(board);
    usleep(100000);
  }
  return EXIT_SUCCESS;
}

void display_board(unsigned int board[height][width]) {
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      printf("%c", (board[i][j] == 0) ? ' ' : '0');
    }
    printf("\n");
  }
}

void display_debug(unsigned int board[height][width]) {
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      printf("%d", board[i][j]);
    }
    printf("\n");
  }
}

void initialize_zeroes(unsigned int board[height][width]) {
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      board[i][j] = 0;
    }
  }
}

void initialize_population(unsigned int board[height][width], unsigned int n) {
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

unsigned int get_n_alive_neighbors(unsigned int board[height][width],
                                   unsigned int height_pos,
                                   unsigned int width_pos) {
  if ((height_pos + width_pos) == 0) {
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

void step(unsigned int board[height][width]) {
  int count;
  int copy_board[height][width];
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      count = get_n_alive_neighbors(board, i, j);
      if (board[i][j] == 1) {
        if (count < 2 || count > 3) {
          copy_board[i][j] = 0;
        }
      } else if (count == 3) {
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

unsigned int generate_number(unsigned int min, unsigned int max) {
  return (rand() % (max - min + 1)) + min;
}
