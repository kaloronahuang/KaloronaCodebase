// BZ2793.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int m, n, last[MAX_N];
vector<long long> ansBox;
bool tag[MAX_N], vis[MAX_N];

int main()
{
    scanf("%d", &m);
    for (int i = 1, val; i <= m; i++)
        scanf("%d", &val), tag[val] = true;
    long long idx = 0;
    scanf("%d", &n);
    for (int i = 1, val, cnt; i <= n; i++)
    {
        scanf("%d", &val), cnt = 0;
        for (int j = last[val] + val; j < MAX_N && cnt < val; last[val] = j, j += val)
            if (!vis[j])
            {
                vis[j] = true, cnt++;
                if (tag[j])
                    ansBox.push_back(cnt + idx);
            }
        idx += val;
    }
    printf("%lld\n", ansBox.size());
    for (int i = 0, siz = ansBox.size(); i < siz; i++)
        printf("%lld\n", ansBox[i]);
    return 0;
}