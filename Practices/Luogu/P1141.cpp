// P1141_ufs.cpp
#include <iostream>

using namespace std;

const int maxm = 10000000;
const int maxn = 1010;
char map[maxn][maxn];
int n, m;

struct UFS
{
    int mem[maxm];
    int mem_h[maxm];

    UFS()
    {
        for (int i = 0; i < maxm; i++)
            mem[i] = i, mem_h[i] = 1;
        for (int i = maxm; i < maxn; i++)
            mem_h[i] = 1;
    }

    int Find(int a)
    {
        if (mem[a] == a)
            return a;
        return mem[a] = Find(mem[a]);
    }

    void Unite(int a, int b)
    {
        if (Find(a) != Find(b))
            mem_h[Find(a)] += mem_h[Find(b)], mem[Find(b)] = Find(a);
    }
} u;

int hashcode(int a, int b)
{
    return a * n + b;
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            cin >> map[i][j];
            // left;
            if (j != 1 && map[i][j - 1] != map[i][j])
                u.Unite(hashcode(i, j), hashcode(i, j - 1));
            // up;
            if (i != 1 && map[i - 1][j] != map[i][j])
                u.Unite(hashcode(i, j), hashcode(i - 1, j));
        }
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        cout << u.mem_h[u.Find(hashcode(a, b))] << endl;
    }
    return 0;
}