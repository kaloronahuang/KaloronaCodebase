// CF1098B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200;

char sol[][2] = {{'A', 'G'}, {'A', 'C'}, {'A', 'T'}, {'C', 'T'}, {'G', 'T'}, {'C', 'G'}};

int n, m, cnt[2], choose[2][MAX_N][6], tot[2][6];
string str[MAX_N], ansBox[MAX_N];

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> str[i], str[i] = "0" + str[i];
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < 6; j++)
        {
            cnt[0] = cnt[1] = 0;
            for (int k = 1; k <= m; k++)
            {
                cnt[0] += sol[(j + (i & 1) * 3) % 6][k & 1] != str[i][k];
                cnt[1] += sol[(j + (i & 1) * 3) % 6][!(k & 1)] != str[i][k];
            }
            choose[0][i][j] = cnt[0] < cnt[1] ? 0 : 1;
            tot[0][j] += min(cnt[0], cnt[1]);
        }
    for (int i = 1; i <= m; i++)
        for (int j = 0; j < 6; j++)
        {
            cnt[0] = cnt[1] = 0;
            for (int k = 1; k <= n; k++)
            {
                cnt[0] += sol[(j + (i & 1) * 3) % 6][k & 1] != str[k][i];
                cnt[1] += sol[(j + (i & 1) * 3) % 6][!(k & 1)] != str[k][i];
            }
            choose[1][i][j] = cnt[0] < cnt[1] ? 0 : 1;
            tot[1][j] += min(cnt[0], cnt[1]);
        }
    int ans = 1e9;
    pair<int, int> res;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 6; j++)
            if (tot[i][j] < ans)
                ans = tot[i][j], res = make_pair(i, j);
    if (res.first == 0)
        for (int i = 1; i <= n; i++, puts(""))
            for (int j = 1; j <= m; j++)
                cout << sol[(res.second + (i & 1) * 3) % 6][(j & 1) != (choose[0][i][res.second])];
    else
    {
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                ansBox[j] += sol[(res.second + (i & 1) * 3) % 6][(j & 1) != (choose[1][i][res.second])];
        for (int i = 1; i <= n; i++)
            cout << ansBox[i] << endl;
    }
    return 0;
}