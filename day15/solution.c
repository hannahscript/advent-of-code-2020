#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

int solve(int input[], int inputSize, int n) {
    int *map = (int*) calloc(n, sizeof(int));
    int last = input[inputSize - 1];

    for (int i = 0; i < inputSize; i++) {
        map[input[i]] = i + 1;
    }

    for (int i = inputSize; i < n; i++) {
        int pLast = last;
        int li = map[last];
        last = li ? i - li : 0;
        map[pLast] = i;
    }

    free(map);
    return last;
}

int main() {
    int input[] = {7, 14, 0, 17, 11, 1, 2};
    int part1 = solve(input, 7, 2020);
    int part2 = solve(input, 7, 30000000);
    printf("Part 1: %d\nPart 2: %d", part1, part2);
}
