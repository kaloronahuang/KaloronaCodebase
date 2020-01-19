// A.cpp
#include <bits/stdc++.h>

using namespace std;

// const int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1}, dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1}

const int MAX_N = 550, dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1}, dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1}, bitnum = 133;
typedef unsigned long long ull;
typedef long long ll;

int n, m, k;
char mp[MAX_N][MAX_N];
ull hash_val[31][MAX_N][MAX_N];
map<ull, ll> ansBox;

void fileIO()
{
    freopen("chessboard.in", "r", stdin);
    freopen("chessboard.out", "w", stdout);
}

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

pair<int, int> getPos(int x, int y, int dir, int step)
{
    x--, x = (x + (1 << step) * dx[dir] % n + n) % n, x++;
    y--, y = (y + (1 << step) * dy[dir] % m + m) % m, y++;
    return make_pair(x, y);
}

int main()
{
    // fileIO();
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++)
        scanf("%s", mp[i] + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            hash_val[0][i][j] = mp[i][j] - 'a' + 1;
    for (int dir = 0; dir < 8; dir++)
    {
        ull pow_num = bitnum;
        for (int step = 1; step <= 30 && (1 << step) <= k; step++)
        {
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= m; j++)
                {
                    pair<int, int> dst = getPos(i, j, dir, step - 1);
                    hash_val[step][i][j] = hash_val[step - 1][i][j] + hash_val[step - 1][dst.first][dst.second] * pow_num;
                }
            pow_num *= pow_num;
        }
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
            {
                ull curt = 0;
                pow_num = bitnum;
                int x = i, y = j;
                for (int bit = 0; bit <= 30; bit++)
                {
                    if (k & (1 << bit))
                    {
                        curt = curt * pow_num + hash_val[bit][x][y];
                        pair<int, int> dst = getPos(x, y, dir, bit);
                        x = dst.first, y = dst.second;
                    }
                    pow_num *= pow_num;
                }
                ansBox[curt]++;
            }
    }
    ll nominator = 0, denominator = 8LL * n * m * 8LL * n * m;
    for (map<ull, ll>::iterator it = ansBox.begin(); it != ansBox.end(); it++)
        nominator += 1LL * it->second * it->second;
    ll d = gcd(nominator, denominator);
    printf("%lld/%lld\n", ll(nominator / d), ll(denominator / d));
    return 0;
}