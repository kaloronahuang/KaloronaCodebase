// BZ4029.cpp
#include <bits/stdc++.h>

using namespace std;

int calc(int num, int ret = 0)
{
    while (num % 10 == 0)
        num /= 10;
    if (num % 10 == 5)
        ret--;
    int base = 1;
    while (num)
        num /= 10, base <<= 1;
    return ret + base;
}

int main()
{
    int l, r, T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &l, &r);
        int ans = l;
        for (int base = 1; base <= r; base *= 10)
        {
            int curt = int(l / (10 * base)) * (10 * base);
            while (curt < l)
                curt += 10 * base;
            if (curt <= r && curt >= l && calc(curt) < calc(ans))
                ans = curt;
            curt = int(l / (10 * base)) * (10 * base) + 5 * base;
            while (curt < l)
                curt += 10 * base;
            if (curt <= r && curt >= l && calc(curt) < calc(ans))
                ans = curt;
        }
        printf("%d\n", ans);
    }
    return 0;
}