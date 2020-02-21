// CF1290B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, q, prefix[26][MAX_N];
char str[MAX_N];

int main()
{
    scanf("%s%d", str + 1, &q), n = strlen(str + 1);
    for (int i = 1; i <= n; i++)
        prefix[str[i] - 'a'][i]++;
    for (int c = 0; c < 26; c++)
        for (int i = 1; i <= n; i++)
            prefix[c][i] += prefix[c][i - 1];
    while (q--)
    {
        int l, r, kind = 0;
        scanf("%d%d", &l, &r);
        for (int i = 0; i < 26; i++)
            kind += (prefix[i][r] - prefix[i][l - 1] > 0);
        if (l == r || kind >= 3 || str[l] != str[r])
            puts("Yes");
        else
            puts("No");
    }
    return 0;
}