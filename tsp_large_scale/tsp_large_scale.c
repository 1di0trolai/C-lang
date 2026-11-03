#include <stdio.h>
#include <limits.h>

#define MAXN 1000
#define MAX_ITER 30

int n;
int c[MAXN][MAXN];
int tour[MAXN];
int visited[MAXN];

// Build initial route using Nearest Neighbor
void nearestNeighbor() {
    tour[0] = 0;
    visited[0] = 1;

    for (int i = 1; i < n; i++) {
        int u = tour[i - 1];
        int best = -1;

        for (int v = 0; v < n; v++) {
            if (!visited[v]) {
                if (best == -1 || c[u][v] < c[u][best])
                    best = v;
            }
        }

        tour[i] = best;
        visited[best] = 1;
    }
}

// Reverse segment [l, r]
void reverse(int l, int r) {
    while (l < r) {
        int tmp = tour[l];
        tour[l] = tour[r];
        tour[r] = tmp;
        l++;
        r--;
    }
}

// Improve route using directed 2-opt
void twoOpt() {
    for (int iter = 0; iter < MAX_ITER; iter++) {
        long long prefix[MAXN];

        prefix[0] = 0;

        for (int i = 0; i < n - 1; i++) {
            prefix[i + 1] = prefix[i]
                + (long long)c[tour[i + 1]][tour[i]]
                - c[tour[i]][tour[i + 1]];
        }

        long long bestDelta = 0;
        int bestL = -1, bestR = -1;

        for (int l = 1; l < n - 1; l++) {
            for (int r = l + 1; r < n; r++) {
                int a = tour[l - 1];
                int b = tour[l];
                int x = tour[r];
                int y = tour[(r + 1) % n];

                long long delta =
                    (long long)c[a][x] + c[b][y]
                    - c[a][b] - c[x][y]
                    + prefix[r] - prefix[l];

                if (delta < bestDelta) {
                    bestDelta = delta;
                    bestL = l;
                    bestR = r;
                }
            }
        }

        if (bestL == -1)
            break;

        reverse(bestL, bestR);
    }
}

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &c[i][j]);
        }
    }

    nearestNeighbor();
    twoOpt();

    printf("%d\n", n);

    for (int i = 0; i < n; i++) {
        printf("%d", tour[i] + 1);
        if (i < n - 1)
            printf(" ");
    }

    printf("\n");
    return 0;
}
