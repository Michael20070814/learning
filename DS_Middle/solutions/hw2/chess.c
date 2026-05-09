#include <stdio.h>

#define SIZE 19

static int board[SIZE][SIZE];

static int in_board(int r, int c)
{
    return r >= 0 && r < SIZE && c >= 0 && c < SIZE;
}

int main(void)
{
    int dr[4] = {0, 1, 1, 1};
    int dc[4] = {1, 0, 1, -1};

    for (int r = 0; r < SIZE; ++r) {
        for (int c = 0; c < SIZE; ++c) {
            scanf("%d", &board[r][c]);
        }
    }

    for (int r = 0; r < SIZE; ++r) {
        for (int c = 0; c < SIZE; ++c) {
            int color = board[r][c];

            if (color == 0) {
                continue;
            }

            for (int d = 0; d < 4; ++d) {
                int prev_r = r - dr[d];
                int prev_c = c - dc[d];
                int count = 0;
                int end_r;
                int end_c;
                int open_before;
                int open_after;

                /*
                 * Only test the first stone of a consecutive segment, so the
                 * same four stones are not reported from their middle.
                 */
                if (in_board(prev_r, prev_c) && board[prev_r][prev_c] == color) {
                    continue;
                }

                for (int k = 0; k < 4; ++k) {
                    int nr = r + dr[d] * k;
                    int nc = c + dc[d] * k;

                    if (in_board(nr, nc) && board[nr][nc] == color) {
                        ++count;
                    }
                }
                if (count != 4) {
                    continue;
                }

                end_r = r + dr[d] * 4;
                end_c = c + dc[d] * 4;
                open_before = in_board(prev_r, prev_c) && board[prev_r][prev_c] == 0;
                open_after = in_board(end_r, end_c) && board[end_r][end_c] == 0;

                if (open_before || open_after) {
                    printf("%d:%d,%d\n", color, r + 1, c + 1);
                    return 0;
                }
            }
        }
    }

    printf("No\n");
    return 0;
}
