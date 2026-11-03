#include <stdio.h>
#include <stdlib.h>

#define MAXN 10
#define MAXMASK (1 << MAXN)
#define INF 1000000000

int n, m;
int d[MAXN], v[MAXN], order[MAXN];
int sum[MAXMASK];
int dp[MAXMASK], ndp[MAXMASK];
int feasible[MAXMASK];

int cmpDesc(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (y > x) - (y < x);
}

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        char code[256];
        scanf("%255s %d %d", code, &d[i], &v[i]);
        order[i] = i;
    }

    // Sort classes by decreasing duration
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (d[order[i]] < d[order[j]]) {
                int tmp = order[i];
                order[i] = order[j];
                order[j] = tmp;
            }
        }
    }

    int total = 1 << n;

    // Sum of durations for each subset
    for (int mask = 1; mask < total; mask++) {
        int j = __builtin_ctz((unsigned)mask);
        sum[mask] = sum[mask ^ (1 << j)] + d[j];
    }

    // Initialize DP
    for (int mask = 0; mask < total; mask++)
        dp[mask] = INF;

    dp[0] = 0;

    scanf("%d", &m);

    // Process each room
    for (int r = 0; r < m; r++) {
        char room[256];
        int cap, k;

        scanf("%255s %d %d", room, &cap, &k);

        int *lengths = malloc((k > 0 ? k : 1) * sizeof(int));
        if (!lengths) return 1;

        for (int j = 0; j < k; j++) {
            int start;
            scanf("%d %d", &start, &lengths[j]);
        }

        qsort(lengths, k, sizeof(int), cmpDesc);

        // Check which subsets this room can serve
        feasible[0] = 1;

        for (int mask = 1; mask < total; mask++) {
            int used = 0;
            int ok = 1;

            for (int j = 0; j < n; j++) {
                int i = order[j];

                if (!(mask & (1 << i)))
                    continue;

                if (v[i] > cap ||
                    used >= k ||
                    d[i] > lengths[used]) {
                    ok = 0;
                    break;
                }

                used++;
            }

            feasible[mask] = ok;
        }

        // Assign a subset of classes to this room
        for (int mask = 0; mask < total; mask++) {
            ndp[mask] = INF;

            for (int sub = mask; ; 
                 sub = (sub - 1) & mask) {

                if (feasible[sub] &&
                    dp[mask ^ sub] != INF) {

                    int val = dp[mask ^ sub];

                    if (sum[sub] > val)
                        val = sum[sub];

                    if (val < ndp[mask])
                        ndp[mask] = val;
                }

                if (sub == 0)
                    break;
            }
        }

        for (int mask = 0; mask < total; mask++)
            dp[mask] = ndp[mask];

        free(lengths);
    }

    int ans = dp[total - 1];

    printf("%d\n", ans == INF ? -1 : ans);

    return 0;
}
