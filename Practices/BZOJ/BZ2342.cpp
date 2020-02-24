// BZ2342.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int n, mlen, match[MAX_N], ans;
char str[MAX_N], org[MAX_N];

int main()
{
    scanf("%d%s", &n, str + 1);
    org[++mlen] = '?';
    for (int i = 1; i <= n; i++)
        org[++mlen] = '#', org[++mlen] = str[i];
    org[++mlen] = '#', org[++mlen] = '!';
    int ptr = 0, rig = 0;
    for (int i = 1; i <= mlen; i++)
    {
        if (i < rig)
            match[i] = min(rig - i, match[(ptr << 1) - i]);
        else
            match[i] = 1;
        while (org[i - match[i]] == org[i + match[i]])
            match[i]++;
        if (rig < i + match[i])
        {
            if (org[i] == '#')
                for (int j = max(rig, i + 4); j < i + match[i]; j++)
                    if (!((j - i) & 3) && match[i - ((j - i) >> 1)] > ((j - i) >> 1))
                        ans = max(ans, j - i);
            rig = i + match[i], ptr = i;
        }
    }
    printf("%d\n", ans);
    return 0;
}