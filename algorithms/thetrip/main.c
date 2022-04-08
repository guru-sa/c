#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int compare(const void *arg1, const void *arg2) {
    int p1, p2;
    p1 = *(int*)arg1;
    p2 = *(int*)arg2;
    return (p2 - p1);
}

int money_spent[1000];
int money_must_spent[1000];

void main() {
    while (1) {
        int i, n;
        int all_money_spent = 0;
        int each_money_spent;
        int money_exchange = 0;
        scanf("%d", &n);
        if (n == 0) break;
        for (i = 0; i < n; i++) {
            double temp;
            scanf("%lf", &temp);
            money_spent[i] = (int)(temp * 100 + 0.5);
            all_money_spent += money_spent[i];
        }
        /* 돈을 가장 많이 쓴 사람부터 순서대로 나열한다. */
        qsort((void *)money_spent, (size_t)(i), sizeof(int), compare);
        /* 각 사람별로 얼마나 돈을 써야 최적화되는지를 계산해준다. */
        each_money_spent = all_money_spent / n;
        for (i = 0; i < n; i++) {
            money_must_spent[i] = each_money_spent;
        }
        all_money_spent %= n;
        for (i = 0; i < all_money_spent; i++) {
            money_must_spent[i]++;
        }
        /* 각 사람별로 차액을 더해주면 결과가 나온다. */
        for (i = 0; i < n; i++) {
            money_exchange += abs(money_spent[i] - money_must_spent[i]);
        }
        money_exchange /= 2;
        printf("$%.2f\n", money_exchange / 100.0);
    }
}