#include <stdio.h>
#include <stdlib.h>

#define INPUT_WIDTH 8
#define ITERATIONS 6
#define GRID_WIDTH (INPUT_WIDTH + 2 * ITERATIONS)
#define GRID_HEIGHT (1 + 2 * ITERATIONS)

#define false 0
#define true 1
typedef int bool;

int idx(int q, int z, int y, int x) {
    return (q * GRID_HEIGHT * GRID_WIDTH * GRID_WIDTH) + (z * GRID_WIDTH * GRID_WIDTH) + (y * GRID_WIDTH) + x;
}

int isValidPos(int q, int z, int y, int x) {
    return x >= 0 && x < GRID_WIDTH
        && y >= 0 && y < GRID_WIDTH
        && z >= 0 && z < GRID_HEIGHT
        && q >= 0 && q < GRID_HEIGHT;
}

int countNeighbours(bool grid[], int q, int z, int y, int x) {
    int count = 0;
    for (int qd = -1; qd <= 1; qd++) {
        for (int zd = -1; zd <= 1; zd++) {
            for (int yd = -1; yd <= 1; yd++) {
                for (int xd = -1; xd <= 1; xd++) {
                    if (!isValidPos(q+qd, z+zd, y+yd, x+xd) || (qd == 0 && zd == 0 && yd == 0 && xd == 0)) continue;

                    count += grid[idx(q+qd, z+zd, y+yd, x+xd)];
                }
            }
        }
    }

    return count;
}

int main() {
    bool input[][INPUT_WIDTH] = {
        {false, true,  true,  true,  false, false, true,  false},
        {true,  true,  false, true,  true,  false, false, false},
        {false, false, false, false, true,  false, true,  false},
        {true,  false, false, true,  false, true,  true,  true },
        {false, false, false, true,  false, false, false, true },
        {true,  true,  false, true,  false, false, false, true },
        {true,  false, false, true,  true,  false, true,  true },
        {true,  false, false, false, false, false, false, false},
    };

    int qs = ITERATIONS - 1; int qe = ITERATIONS + 1;
    int zs = ITERATIONS - 1; int ze = ITERATIONS + 1;
    int ys = ITERATIONS - 1; int ye = ITERATIONS + INPUT_WIDTH;
    int xs = ITERATIONS - 1; int xe = ITERATIONS + INPUT_WIDTH;

    bool *grid = (bool*) calloc(GRID_WIDTH * GRID_WIDTH * GRID_HEIGHT * GRID_HEIGHT, sizeof(bool));
    bool *swapGrid = (bool*) calloc(GRID_WIDTH * GRID_WIDTH * GRID_HEIGHT * GRID_HEIGHT, sizeof(bool));

    // Fill grid with input
    for (int y = 0; y < INPUT_WIDTH; y++) {
        for (int x = 0; x < INPUT_WIDTH; x++) {
            grid[idx(ITERATIONS, ITERATIONS, ITERATIONS + y, ITERATIONS + x)] = input[y][x];
        }
    }

    // Mutate ITERATIONS times
    for (int i = 0; i < ITERATIONS; i++) {

        for (int q = qs; q <= qe; q++) {
            for (int z = zs; z <= ze; z++) {
                for (int y = ys; y <= ye; y++) {
                    for (int x = xs; x <= xe; x++) {
                        int nb = countNeighbours(grid, q, z, y, x);

                        if (grid[idx(q, z, y, x)]) {
                            swapGrid[idx(q, z, y, x)] = nb == 2 || nb == 3;
                        } else {
                            swapGrid[idx(q, z, y, x)] = nb == 3;
                        }
                    }
                }
            }
        }

        bool* buf = grid;
        grid = swapGrid;
        swapGrid = buf;

        qs -= 1; qe += 1;
        zs -= 1; ze += 1;
        ys -= 1; ye += 1;
        xs -= 1; xe += 1;
    }

    // Count active cells
    long count = 0;
    for (int i = 0; i < GRID_WIDTH * GRID_WIDTH * GRID_HEIGHT * GRID_HEIGHT; i++) {
        count += grid[i];
    }

    free(grid);
    free(swapGrid);

    printf("Count: %d", count);

    return 0;
}
