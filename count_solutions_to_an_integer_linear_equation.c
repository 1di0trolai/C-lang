#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 100

int n, m;
int a[MAX_N];
int sum_a[MAX_N];
int ans = 0;

void try_var(int k, int cur_sum){
    if (k == n) {
        int rem = m - cur_sum;
        if (rem > 0 && rem % a[n] == 0) {
            ans++;
        }
        return;
    }

    int rem_min = sum_a[k + 1];
    int max_val = (m - cur_sum - rem_min) / a[k];

    for (int v = 1; v <= max_val; v++){
        try_var(k+1, cur_sum + a[k] * v);
    }
}

int main(){
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
    }

    sum_a[n] = a[n];
    for (int i = n - 1; i >= 1; i--){
        sum_a[i] = sum_a[i + 1] + a[i];
    }

    try_var(1, 0);

    printf("%d\n", ans);

    return 0;
}