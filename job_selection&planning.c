#include <stdio.h>
#include <stdlib.h>

#define MAXN 100000

typedef struct {
    int d, p;
} Job;

Job jobs[MAXN];
int parent[MAXN + 1];

// Sort by profit in descending order
int cmp(const void *a, const void *b) {
    Job *x = (Job *)a;
    Job *y = (Job *)b;

    return (y->p > x->p) - (y->p < x->p);
}

// Find latest available time slot
int find(int x) {
    int root = x;

    while (parent[root] != root)
        root = parent[root];

    while (x != root) {
        int next = parent[x];
        parent[x] = root;
        x = next;
    }

    return root;
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &jobs[i].d, &jobs[i].p);
    }

    // Sort jobs by decreasing profit
    qsort(jobs, n, sizeof(Job), cmp);

    // Initialize DSU
    for (int i = 0; i <= n; i++)
        parent[i] = i;

    long long ans = 0;

    for (int i = 0; i < n; i++) {
        int deadline = jobs[i].d;

        if (deadline > n)
            deadline = n;

        int slot = find(deadline);

        if (slot > 0) {
            ans += jobs[i].p;

            // Mark slot as occupied
            parent[slot] = find(slot - 1);
        }
    }

    printf("%lld\n", ans);

    return 0;
}
