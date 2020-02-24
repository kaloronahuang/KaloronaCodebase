// A.cpp
#include <bits/stdc++.h>

using namespace std;

int idx[10];

int main()
{
    int T, a, b, c;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d", &a, &b, &c);
        for (int i = 1; i < 8; i++)
            idx[i] = i;
        int ans = 0;
        do
        {
            int remA = a, remB = b, remC = c, tmp = 0;
            for (int i = 1; i < 8; i++)
            {
                int stat = idx[i];
                int reqA = stat & 1, reqB = (stat >> 1) & 1, reqC = (stat >> 2) & 1;
                if (reqA <= remA && reqB <= remB && reqC <= remC)
                {
                    tmp++;
                    remA -= reqA, remB -= reqB, remC -= reqC;
                }
            }
            ans = max(ans, tmp);
        } while (next_permutation(idx + 1, idx + 8));
        printf("%d\n", ans);
    }
    return 0;
}