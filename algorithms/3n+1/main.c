#include <stdio.h>

int main(void) {
    long lbound, ubound, lbOrg, ubOrg, temp;
    long i, j, length, max_length;

    while (scanf("%ld %ld", &lbound, &ubound) == 2) {
        lbOrg = lbound;
        ubOrg = ubound;

        /* 입력된 구간 값들 중 앞의 것이 더 크면 swap */
        if (lbound > ubound) {
            temp = lbound;
            lbound = ubound;
            ubound = temp;
        }

        max_length = 0;
        for (i = lbound; i <= ubound; i++) {
            j = i;
            length = 1;
            while (j != 1) {
                /* 홀수 n * 3 + 1은 항상 짝수 */
                if (j & 1) {
                    j = j * 3 + 1;
                    length++;
                }
                while (!(j & 1)) {
                    j >>= 1;
                    length++;
                }
            }
            if (length > max_length) {
                max_length = length;
            }
        }
        printf("%ld %ld %ld\n", lbOrg, ubOrg, max_length);
    }
}