// P3462.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, m, tot, ci[MAX_N], ai[MAX_N], bi[MAX_N], digits[MAX_N];

bool remove(int bitpos)
{
    int ptr = bitpos;
    for (; ptr <= tot && digits[ptr] == 0; ptr++)
        ;
    if (ptr > tot)
        return false;
    digits[ptr--]--;
    for (; ptr >= bitpos; ptr--)
        digits[ptr] += ai[ptr + 1] / ai[ptr] - 1;
    return true;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ci[i]);
    for (int i = 1; i <= m; i++)
        scanf("%d", &ai[i]);
    sort(ai + 1, ai + 1 + m), bi[tot = 1] = 1;
    for (int i = 2; i <= m; i++)
    {
        if (ai[i] != ai[i - 1])
            ai[++tot] = ai[i];
        bi[tot]++;
    }
    for (int i = 1; i <= n; i++)
        for (int j = tot; j >= 1; j--)
            digits[j] += ci[i] / ai[j], ci[i] %= ai[j];
    int ans = 0;
    for (int i = 1; i <= tot; i++)
        for (int j = 1; j <= bi[i]; j++)
            if (remove(i))
                ans++;
            else
                printf("%d\n", ans), exit(0);
    printf("%d\n", ans);
    return 0;
}