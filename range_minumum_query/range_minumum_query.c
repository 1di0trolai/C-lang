#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 1000005
#define LOG 20

int M[MAX][LOG];

int min(int a, int b) {
    return a < b ? a : b;
}

int fast_log2(int x) {
    return 31 - __builtin_clz(x);
}

int main(){
    int n, m;
    scanf("%d", &n);

    for (int i = 0; i < n; i++){
        scanf("%d", &M[i][0]);
    }

    for (int j = 1; (1 << j) <= n; j++){
        for (int i = 0; i + (1 << j) - 1 < n; i++){
            M[i][j] = min(M[i][j-1], M[i+(1<<(j-1))][j-1]);
        }
    }

    scanf("%d", &m);

    long long Q = 0;

    for (int k = 0; k < m; k++){
        int L, R;
        scanf("%d%d", &L, &R);
        int len = R - L + 1;
        int j = fast_log2(len);
        int current_min = min(M[L][j], M[R - (1 << j) + 1][j]);
        Q += current_min;
    }

    printf("%lld\n", Q);
    return 0;
}