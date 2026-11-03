#include <stdio.h>
#include <stdlib.h>

#define MAXN 100000

int d[MAXN];

int cmp(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (y > x) - (y < x);
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &d[i]);
    }

    // Sort durations in descending order
    qsort(d, n, sizeof(int), cmp);

    int T = 0;

    for (int i = 0; i < n; i++) {
        int finish = i + d[i];

        if (finish > T) {
            T = finish;
        }
    }

    printf("%d\n", T);

    return 0;
}
