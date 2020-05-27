// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 550;

const int primes[] = {2, 3, 5, 7, 11, 13, 17, 19};
const int limits[] = {8, 5, 3, 3, 2, 2, 2, 2};

int n, val[MAX_N], idx[MAX_N][9], box[9], tmp[MAX_N], ans;
vector<int> num;

int check()
{
    int ret = 0;
    memset(tmp, 0, sizeof(tmp));
    for (int x : num)
    {
        bool flag = true;
        for (int i = 0; i < 8; i++)
            flag &= box[i] >= idx[x][i];
        if (flag)
            if (idx[x][8] == 1)
                ret += val[x];
            else
                tmp[idx[x][8]] += val[x];
    }
    for (int i = 1; i < MAX_N; i++)
        ret += max(0, tmp[i]);
    return ret;
}

void dfs(int pos)
{
    if (pos == 8)
        return (void)(ans = max(ans, check()));
    for (box[pos] = 0; box[pos] <= limits[pos]; box[pos]++)
        dfs(pos + 1);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1, m, v; i <= n; i++)
        scanf("%d%d", &m, &v), val[m] += v;
    for (int i = 1; i < MAX_N; i++)
        if (val[i] != 0)
        {
            num.push_back(i);
            int acc = i;
            for (int j = 0; j < 8; j++)
                while (acc % primes[j] == 0)
                    idx[i][j]++, acc /= primes[j];
            idx[i][8] = acc;
        }
    ans = -0x7fffffff;
    dfs(0), printf("%d\n", ans);
    return 0;
}