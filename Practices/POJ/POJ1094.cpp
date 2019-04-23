// POJ1094.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX_N = 30;

int n, m, di[MAX_N][MAX_N], mp[MAX_N][MAX_N];

int floyd()
{
    memcpy(mp, di, sizeof(di));
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                mp[i][j] |= mp[i][k] & mp[k][j];
                if (mp[i][j] == mp[j][i] && mp[i][j] == 1 && i != j)
                    return -1;
            }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (mp[i][j] == mp[j][i] && mp[i][j] == 0 && i != j)
                return 0;
    return 1;
}

void solve()
{
    memset(di, 0, sizeof(di));
    bool flag = true;
    int cnt = 0;
    while (m--)
    {
        cnt++;
        string idc;
        cin >> idc;
        int a = idc[0] - 'A', b = idc[2] - 'A';
        di[a][b] = 1;
        if (flag)
        {
            int stat = floyd();
            if (stat == -1)
                printf("Inconsistency found after %d relations.\n", cnt), flag = false;
            else if (stat == 1)
            {
                pair<char, int> prs[MAX_N];
                for (int i = 0; i < n; i++)
                    prs[i].first = 0, prs[i].second = 'A' + i;
                printf("Sorted sequence determined after %d relations: ", cnt);
                for (int j = 0; j < n; j++)
                    for (int k = 0; k < n; k++)
                        if (mp[j][k])
                            prs[j].first++;
                sort(prs, prs + n);
                for (int i = n - 1; i >= 0; i--)
                    printf("%c", prs[i].second);
                puts(".");
                flag = false;
            }
        }
    }
    if (flag)
        puts("Sorted sequence cannot be determined.");
}

int main()
{
    while (scanf("%d%d", &n, &m) && n != 0)
        solve();
    return 0;
}