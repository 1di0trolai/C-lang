#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1005

// Cấu trúc biểu diễn tọa độ một ô trong mê cung
typedef struct {
    int r, c;
} Point;

int A[MAX][MAX];
int dist[MAX][MAX];
Point queue[MAX * MAX];
int head = 0, tail = 0;

// 4 hướng di chuyển: Lên, Xuống, Trái, Phải
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

int solve(int n, int m, int r, int c) {
    // Nếu ô xuất phát là tường gạch
    if (A[r][c] == 1) return -1;

    // Khởi tạo mảng khoảng cách
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            dist[i][j] = -1;
        }
    }

    // Đưa ô xuất phát vào hàng đợi
    queue[tail++] = (Point){r, c};
    dist[r][c] = 0;

    while (head < tail) {
        Point cur = queue[head++];
        int u = cur.r;
        int v = cur.c;

        // Nếu ô hiện tại nằm ở biên của mê cung, bước thêm 1 bước nữa sẽ ra ngoài
        if (u == 1 || u == n || v == 1 || v == m) {
            return dist[u][v] + 1;
        }

        // Duyệt 4 ô lân cận
        for (int i = 0; i < 4; i++) {
            int nr = u + dr[i];
            int nc = v + dc[i];

            // Kiểm tra ô nằm trong lưới, là ô trống và chưa được ghé thăm
            if (nr >= 1 && nr <= n && nc >= 1 && nc <= m) {
                if (A[nr][nc] == 0 && dist[nr][nc] == -1) {
                    dist[nr][nc] = dist[u][v] + 1;
                    queue[tail++] = (Point){nr, nc};
                }
            }
        }
    }

    // Không tìm thấy đường thoát
    return -1;
}

int main() {
    int n, m, r, c;
    if (scanf("%d %d %d %d", &n, &m, &r, &c) != 4) return 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    int result = solve(n, m, r, c);
    printf("%d\n", result);

    return 0;
}