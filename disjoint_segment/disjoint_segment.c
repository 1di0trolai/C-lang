
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a, b;
} Segment;

int cmp(const void *x, const void *y) {
    Segment *s1 = (Segment *)x;
    Segment *s2 = (Segment *)y;
    return s1->b - s2->b;
}

int main() {
    int n;
    scanf("%d", &n);

    Segment segments[100000];

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &segments[i].a, &segments[i].b);
    }

    qsort(segments, n, sizeof(Segment), cmp);

    int count = 0;
    int lastEnd = -1;

    for (int i = 0; i < n; i++) {
        if (segments[i].a > lastEnd) {
            count++;
            lastEnd = segments[i].b;
        }
    }

    printf("%d\n", count);
    return 0;
}
