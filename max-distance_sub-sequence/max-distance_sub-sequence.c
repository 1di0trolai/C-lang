#include <stdio.h>
#include <stdlib.h>

#define MAXN 100000

int x[MAXN];
int N, C;

int cmp(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}

int check(int d) {
    int count = 1;
    int lastPos = x[0];

    for (int i = 1; i < N; i++) {
        if (x[i] - lastPos >= d) {
            count++;
            lastPos = x[i];

            if (count >= C)
                return 1;
        }
    }

    return count >= C;
}

int solve() {
    qsort(x, N, sizeof(int), cmp);

    int left = 0;
    int right = x[N - 1] - x[0];
    int ans = 0;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (check(mid)) {
            ans = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return ans;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d %d", &N, &C);

        for (int i = 0; i < N; i++) {
            scanf("%d", &x[i]);
        }

        printf("%d\n", solve());
    }

    return 0;
}
