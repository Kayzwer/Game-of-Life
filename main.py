import os
import argparse
import numpy as np


class World:
    def __init__(self, width: int, height: int) -> None:
        self.width = width
        self.height = height
        self.world = np.zeros((height, width), dtype=np.int0)

    def __str__(self) -> str:
        output = ""
        for row in self.world:
            for grid in row:
                output += " " if grid == 0 else "0"
            output += "\n"
        return output

    def step(self) -> np.ndarray:
        new_world = np.copy(self.world)
        for i in range(self.height):
            for j in range(self.width):
                if i == 0 and j == 0:
                    count = self.world[i + 1][j] + self.world[i][j + 1] + \
                        self.world[i + 1][j + 1]
                elif i == 0 and j == self.width - 1:
                    count = self.world[i][j - 1] + self.world[i + 1][j - 1] + \
                        self.world[i + 1][j]
                elif i == self.height - 1 and j == 0:
                    count = self.world[i - 1][j] + self.world[i - 1][j + 1] + \
                        self.world[i][j + 1]
                elif i == self.height - 1 and j == self.width - 1:
                    count = self.world[i][j - 1] + self.world[i - 1][j - 1] + \
                        self.world[i - 1][j]
                elif i == self.height - 1:
                    count = self.world[i][j - 1] + self.world[i - 1][j - 1] + \
                        self.world[i - 1][j] + self.world[i - 1][j + 1] + \
                        self.world[i][j + 1]
                elif j == self.width - 1:
                    count = self.world[i - 1][j] + self.world[i - 1][j - 1] + \
                        self.world[i][j - 1] + self.world[i + 1][j - 1] + \
                        self.world[i + 1][j]
                elif i == 0:
                    count = self.world[i][j - 1] + self.world[i + 1][j - 1] + \
                        self.world[i + 1][j] + self.world[i + 1][j + 1] + \
                        self.world[i][j + 1]
                elif j == 0:
                    count = self.world[i - 1][j] + self.world[i - 1][j + 1] + \
                        self.world[i][j + 1] + self.world[i + 1][j + 1] + \
                        self.world[i + 1][j]
                else:
                    count = self.world[i][j - 1] + self.world[i - 1][j - 1] + \
                        self.world[i - 1][j] + self.world[i - 1][j + 1] + \
                        self.world[i][j + 1] + self.world[i + 1][j + 1] + \
                        self.world[i + 1][j] + self.world[i + 1][j - 1]

                if new_world[i][j] == 1:
                    if count < 2:
                        new_world[i][j] = 0
                    elif count > 3:
                        new_world[i][j] = 0
                elif new_world[i][j] == 0 and count == 3:
                    new_world[i][j] = 1

        self.world = new_world

    def initial_population(self, number: int) -> None:
        assert number < self.width * self.height
        i = 0
        while i < number:
            row = np.random.randint(0, self.height)
            col = np.random.randint(0, self.width)
            while self.world[row][col] == 1:
                row = np.random.randint(0, self.height)
                col = np.random.randint(0, self.width)
            self.world[row][col] = 1
            i += 1

    def run(self) -> None:
        try:
            while True:
                os.system("clear")
                print(self, end="\r")
                self.step()
        except KeyboardInterrupt:
            os.system("clear")


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--width', help="width of the world", type=int,
                        default=50)
    parser.add_argument('--height', help="height of the world", type=int,
                        default=50)
    parser.add_argument('--init_pop', help="initial population of life cells",
                        type=int, default=1000)
    args = parser.parse_args()
    env = World(args.width, args.height)
    env.initial_population(args.init_pop)
    env.run()


if __name__ == "__main__":
    main()
