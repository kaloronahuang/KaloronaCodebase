// BZ1041.cpp
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int r, ans = 1;
    scanf("%d", &r);
    for (int i = 2; 1LL * i * i <= r; i++)
        if (r % i == 0)
        {
            int cnt = 0;
            while (r % i == 0)
                cnt += (i % 4 != 3) * 2, r /= i;
            if (i != 2)
                ans *= (cnt + 1);
        }
    if (r != 1 && r % 4 != 3)
        ans *= 3;
    printf("%d\n", ans << 2);
    return 0;
}