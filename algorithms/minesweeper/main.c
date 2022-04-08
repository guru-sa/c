#include <stdio.h>

#define MAX_N 100
#define MAX_M 100

void main(void) {
    char row[MAX_M + 1];
    int n, m, i, j, i2, j2, field_id;
    char mf[MAX_N + 2][MAX_M + 2];
    field_id = 1;
    scanf("%d %d", &n, &m);
    while (n || m) {
        for (i = 1; i <= n; i++) {
            for (j = 1; j <= m; j++) {
                mf[i][j] = 0;
            }
        }
        for (i = 1; i <= n; i++) {
            scanf("%s", row);
            for (j = 1; j <= m; j++) {
                if (row[j - 1] == '*') {
                    for (i2 = i - 1; i2 <= i + 1; i2++) {
                        for (j2 = j - 1; j2 <= j + 1; j2++) {
                            if (mf[i2][j2] != '*') {
                                mf[i2][j2]++;
                            }
                        }
                    }
                    mf[i][j] = '*';
                }
            }
        }
        if (field_id > 1) putchar('\n');
        printf("Field #%d:\n", field_id++);
        for (i = 1; i <= n; i++) {
            for (j = 1; j <= m; j++) {
                putchar(mf[i][j]);
            }
            putchar('\n');
        }
        scanf("%d %d", &n, &m);
    }
}