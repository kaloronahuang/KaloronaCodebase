// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, mcnt;
map<string, int> mp;
int seq[MAX_N];
int last_pos[MAX_N];

int main()
{
    memset(last_pos, -1, sizeof(last_pos));
    scanf("%d", &n);
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        string s;
        cin >> s;
        if (mp.count(s) == 0)
            mp[s] = ++mcnt;
        int idx = mp[s];
        seq[i] = idx;
        if (last_pos[idx] != -1)
            ans = max(ans, n - (i - last_pos[idx]));
        last_pos[idx] = i;
    }
    printf("%d\n", ans);
    return 0;
}