// tree.cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
// Report:
// Modules: Prime Selection;
//          UFS;

using namespace std;

#define ll long long
const int maxn = 500100;
const int INF = 0x7fffffff;
int arr[maxn];
int N;
bool isPrime[maxn];
// ufs;
int accs[maxn];
int mem[maxn];

int Find(int x)
{
    if (mem[x] == x)
        return x;
    return mem[x] = Find(mem[x]);
}

void Unite(int x, int y)
{
    if (Find(x) != Find(y))
    {
        int root = Find(x);
        accs[root] += accs[Find(y)];
        mem[Find(y)] = root;
    }
}
// O(n log n)
void shuffle()
{
    fill(isPrime, isPrime + maxn, true);
    for (int i = 2; i < maxn; i++)
    {
        if (!isPrime[i])
            continue;
        for (int j = 2; i * j < maxn; j++)
            isPrime[i * j] = false;
    }
}

void dfs(int u)
{
    int idx;
    int min_val = INF;
    if (!isPrime[u])
    {
        // getting the point;
        for (int i = 1; i < u; i++)
            if (u % i == 0)
                if (arr[i] != arr[u])
                {
                    idx = i;
                    break;
                }
                else if (min_val > accs[Find(i)])
                    idx = i, min_val = accs[Find(i)];
        accs[u] = 1;
        if (arr[idx] == arr[u])
            Unite(idx, u);
    }
    else
    {
        accs[u] = 1;
        if (arr[1] == arr[u])
            Unite(1, u);
    }
}

bool anses[maxn];

int main()
{
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    shuffle();
    scanf("%d", &N);
    for (int i = 1; i <= N; i++)
        scanf("%d", &arr[i]);
    for (int i = 0; i <= N; i++)
        mem[i] = i;
    for (int i = 2; i <= N; i++)
        dfs(i);
    ll ans = 0;
    for (int i = 1; i <= N; i++)
        if (!anses[mem[i]])
            ans++, anses[mem[i]] = true;
    printf("%lld", ans);
    return 0;
}