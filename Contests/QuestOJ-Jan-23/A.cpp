// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 101000;

int n, m, k, p, seq[MAX_N], ansBox[MAX_N], tmp[MAX_N];

int main()
{
    scanf("%d%d%d%d", &n, &m, &k, &p);
    for (int i = 1; i <= k; i++)
        scanf("%d", &seq[i]);
    if (m == 1)
        for (int i = 1; i <= n; i++)
            printf("%d\n", (i == p + k - 1));
    else if (n <= 20 && m <= 2)
    {
        for (int i = k; i <= n; i++)
            for (int stat = 0; stat < (1 << (i - k)); stat++)
            {
                for (int j = 1; j <= i - k; j++)
                    tmp[j] = ((stat >> (j - 1)) & 1) + 1;
                for (int j = 1; j <= k; j++)
                    tmp[i - k + j] = seq[j];
                int cnt = 1;
                for (int j = i - 1; j >= k; j--)
                {
                    bool flag = true;
                    for (int ptr = 1; ptr <= k; ptr++)
                        flag &= (seq[ptr] == tmp[j - k + ptr]);
                    cnt += (flag == true);
                }
                ansBox[i] += (cnt == p);
            }
        for (int i = 1; i <= n; i++)
            printf("%d\n", ansBox[i]);
    }
    return 0;
}