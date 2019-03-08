// A.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int mod = 998244353;
int n, m, p, q;
struct point1
{
    int table[20][20], anses[20][20], answer;
    bool check()
    {
        memset(anses, 0, sizeof(anses));
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                anses[i][table[i][j]]++;
        for (int i = 2; i <= n; i++)
        {
            int sta = 0;
            for (int col = 1; col <= p; col++)
                if (anses[i][col] || anses[i - 1][col])
                    sta++;
            if (sta < q)
                return false;
        }
        return true;
    }
    void dfs(int step)
    {
        if (step == n * m + 1)
        {
            if (check())
                answer++, answer %= mod;
            return;
        }
        for (int i = 1; i <= p; i++)
            table[(step - 1) / m + 1][(step - 1) % m + 1] = i, dfs(step + 1);
    }
    ll solve()
    {
        answer = 0;
        dfs(1);
        return answer;
    }
} pt1;
int main()
{
    freopen("color.in", "r", stdin);
    freopen("color.out", "w", stdout);
    scanf("%d%d%d%d", &n, &m, &p, &q);
    if (n * m <= 15 && p <= 3 && q <= 3)
        printf("%lld", pt1.solve()), exit(0);
    return 0;
}