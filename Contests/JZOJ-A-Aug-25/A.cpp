// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int seq[MAX_N], n, pos[MAX_N];

int main()
{
    scanf("%d", &n);
    if (n <= 5)
    {
        int tot_bit = 0;
        for (int i = 1; i <= 2 * n; i++)
        {
            scanf("%d", &seq[i]), tot_bit += seq[i];
            if (seq[i] == 1)
                pos[tot_bit] = i;
        }
        int ans = 0, gans = 0x3f3f3f3f;
        for (int stat = 0; stat < (1 << (2 * n)); stat++)
        {
            int bitnum = 0;
            for (int i = 0; i < 2 * n; i++)
                if (stat & (1 << i))
                    bitnum++;
            if (bitnum != tot_bit)
                continue;
            for (int i = 0, p = 0; i < 2 * n; i++)
                if (stat & (1 << i))
                    ans += abs(i + 1 - pos[++p]);
            gans = min(gans, ans);
        }
        printf("%d", gans);
    }
    return 0;
}
