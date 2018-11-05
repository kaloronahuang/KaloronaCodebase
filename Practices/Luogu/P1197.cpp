// P1197.cpp
#include <iostream>
#include <vector>

using namespace std;

const int maxn = 500200;
vector<int> G[maxn];
int n, m, k;
int xi[maxn], yi[maxn];
bool mark[maxn];
int sum;

struct UFS
{
    int mem[maxn];
    UFS()
    {
        for (int i = 0; i < n; i++)
            mem[i] = i;
    }
    int Find(int x)
    {
        if (x == mem[x])
            return x;
        return mem[x] = Find(mem[x]);
    }
    void Unite(int x, int y)
    {
        if (Find(x) != Find(y))
            mem[Find(x)] = mem[Find(y)], sum--;
    }
};

int points[maxn];
int res[maxn];
int cur = 0;

int main()
{
    cin >> n >> m;
    sum = n;
    for (int i = 0; i < m; i++)
        cin >> xi[i] >> yi[i], G[xi[i]].push_back(yi[i]), G[yi[i]].push_back(xi[i]);
    cin >> k, sum -= k;
    for (int i = 0; i < k; i++)
        cin >> points[i], mark[points[i]] = true;
    UFS u;
    // initalize;
    for (int i = 0; i < m; i++)
        if (mark[xi[i]] || mark[yi[i]])
            continue;
        else
            u.Unite(xi[i], yi[i]);
    res[k] = sum;
    for (int i = k - 1; i >= 0; i--)
    {
        mark[points[i]] = false;
        sum++;
        int siz = G[points[i]].size();
        for (int j = 0; j < siz; j++)
            if (!mark[G[points[i]][j]])
                u.Unite(points[i], G[points[i]][j]);
        res[i] = sum;
    }
    for (int i = 0; i <= k; i++)
        cout << res[i] << endl;
    return 0;
}