#include <stdio.h>

#define N 5

int board[N][N];
long long ans = 0;

/* 检查是否有五连 */
int check_win() {
    // 横
    for (int i = 0; i < N; i++) {
        int v = board[i][0];
        if (v == 0) continue;
        int ok = 1;
        for (int j = 1; j < N; j++) {
            if (board[i][j] != v) {
                ok = 0;
                break;
            }
        }
        if (ok) return 1;
    }
    // 竖
    for (int j = 0; j < N; j++) {
        int v = board[0][j];
        if (v == 0) continue;
        int ok = 1;
        for (int i = 1; i < N; i++) {
            if (board[i][j] != v) {
                ok = 0;
                break;
            }
        }
        if (ok) return 1;
    }
    // 主对角线
    int v = board[0][0];
    if (v != 0) {
        int ok = 1;
        for (int i = 1; i < N; i++) {
            if (board[i][i] != v) {
                ok = 0;
                break;
            }
        }
        if (ok) return 1;
    }
    // 副对角线
    v = board[0][N - 1];
    if (v != 0) {
        int ok = 1;
        for (int i = 1; i < N; i++) {
            if (board[i][N - 1 - i] != v) {
                ok = 0;
                break;
            }
        }
        if (ok) return 1;
    }
    return 0;
}

/* DFS 枚举 */
void dfs(int pos, int white, int black) {
    if (check_win()) return; // 已出现胜利，剪枝

    if (pos == 25) {
        // 白13 黑12
        if (white == 13 && black == 12) {
            ans++;
        }
        return;
    }

    int x = pos / 5;
    int y = pos % 5;

    // 放白棋（先手，总数13）
    if (white < 13) {
        board[x][y] = 1;
        dfs(pos + 1, white + 1, black);
        board[x][y] = 0;
    }

    // 放黑棋（总数12）
    if (black < 12) {
        board[x][y] = 2;
        dfs(pos + 1, white, black + 1);
        board[x][y] = 0;
    }
}

int main() {
    dfs(0, 0, 0);
    printf("%lld\n", ans);
    return 0;
}