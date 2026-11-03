#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_TEACHERS 35 
#define MAX_COURSES 35

int m, n;
bool pref[MAX_TEACHERS][MAX_COURSES];
bool conflict[MAX_COURSES][MAX_COURSES];
int load[MAX_TEACHERS];
int teacher_of[MAX_COURSES];
int min_max_load = 1e9;

bool check(int t, int k){
    if (!pref[t][k]) return false;
    for (int i = 1; i < k; i++) {
        if (teacher_of[i] == t && conflict[i][k]) {
            return false;
        }
    }
    return true;
}

void try_assign(int k){
    if (k > n) {
        int current_max = 0;
        for (int i = 1; i <= m; i++) {
            if (load[i] > current_max) current_max = load[i];
        }
        if (current_max < min_max_load) min_max_load = current_max;
        return;
    }

    for (int t = 1; t <=m; t++){
        if (check(t, k)) {
            if (load[t] + 1 >= min_max_load) continue;

            load[t]++;
            teacher_of[k] = t;

            try_assign(k+1);

            load[t]--;
            teacher_of[k] = 0;
        }
    }
}

int main(){
    if (scanf("%d%d", &m, &n) != 2) return 0;

    for (int i = 1; i <= m; i++) {
        int k_i;
        scanf("%d", &k_i);
        for(int j = 0; j < k_i; j++) {
            int c;
            scanf("%d", &c);
            pref[i][c] = true;
        }
    }

    int num_conflicts;
    scanf("%d", &num_conflicts);
    for (int i = 0; i <num_conflicts; i++){
        int u, v;
        scanf("%d%d", &u, &v);
        conflict[u][v] = true;
        conflict[v][u] = true;
    }

    try_assign(1);

    if (min_max_load == 1e9){
        printf("-1\n");
    } else {
        printf("%d\n", min_max_load);
    }

    return 0;
}