// F.cpp
#include <bits/stdc++.h>

using namespace std;

int n, q;
map<string, int> mp;

int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
    {
        string s;
        cin >> s;
        mp[s] = i;
    }
    while (q--)
    {
        string a, b;
        cin >> a >> b;
        printf("%d\n", max(0, abs(mp[a] - mp[b]) - 1));
    }
    return 0;
}