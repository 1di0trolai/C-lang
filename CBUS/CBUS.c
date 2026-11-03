#include <stdio.h>
#include <stdbool.h>

#define MAX_N 30

int n, k;
int c[MAX_N * 2][MAX_N * 2];
bool visited[MAX_N * 2];
int x[MAX_N * 2];      // Mảng lưu hành trình
int load = 0;          // Số khách hiện có trên xe
int curr_len = 0;
int best_len = 1e9;
int c_min = 1e9;       // Khoảng cách nhỏ nhất giữa 2 đỉnh phân biệt

bool check(int v) {
    if (visited[v]) return false;

    if (v <= n) {
        // Điểm đón: xe không được đầy
        if (load >= k) return false;
    } else {
        // Điểm trả: khách tương ứng phải đã được đón
        if (!visited[v - n]) return false;
    }

    return true;
}

void try_step(int step) {
    for (int v = 1; v <= 2 * n; v++) {
        if (check(v)) {
            x[step] = v;
            visited[v] = true;
            curr_len += c[x[step - 1]][v];

            if (v <= n) load++;
            else load--;

            if (step == 2 * n) {
                // Đã đi qua 2n điểm, cộng chi phí quay về điểm 0
                int total_len = curr_len + c[v][0];
                if (total_len < best_len) {
                    best_len = total_len;
                }
            } else {
                // Đánh giá cận dưới để cắt nhánh
                if (curr_len + (2 * n + 1 - step) * c_min < best_len) {
                    try_step(step + 1);
                }
            }

            // Quay lui (Backtrack)
            if (v <= n) load--;
            else load++;
            curr_len -= c[x[step - 1]][v];
            visited[v] = false;
        }
    }
}

int main() {
    if (scanf("%d %d", &n, &k) != 2) return 0;

    int total_nodes = 2 * n;
    for (int i = 0; i <= total_nodes; i++) {
        for (int j = 0; j <= total_nodes; j++) {
            scanf("%d", &c[i][j]);
            if (i != j && c[i][j] < c_min) {
                c_min = c[i][j];
            }
        }
    }

    x[0] = 0; // Xuất phát từ điểm 0
    try_step(1);

    printf("%d\n", best_len);

    return 0;
}