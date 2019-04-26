// CH6201.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAX_N = 6060;
int size[MAX_N], buffer[MAX_N], T, n;
int tmpx, tmpy, tmpz;
ll answer = 0;

struct edge
{
    int from, to, weight;
    bool operator<(const edge &eg) const { return weight < eg.weight; }
} edges[MAX_N << 1];

void unite(int x, int y)
{
    if (size[x] < size[y])
        swap(x, y);
    buffer[y] = x, size[x] += size[y];
}

int find(int x) { return buffer[x] == x ? x : buffer[x] = find(buffer[x]); }

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        answer = 0;
        scanf("%d", &n);
        for (int i = 1; i <= n - 1; i++)
        {
            scanf("%d%d%d", &tmpx, &tmpy, &tmpz);
            edges[i].from = tmpx;
            edges[i].to = tmpy, edges[i].weight = tmpz;
        }
        sort(edges + 1, edges + n);
        for (int i = 1; i <= n; i++)
            buffer[i] = i, size[i] = 1;
        for (int i = 1; i <= n - 1; i++)
        {
            int x = edges[i].from, y = edges[i].to, z = edges[i].weight;
            if (find(x) != find(y))
                answer += (z + 1) * (size[find(x)] * size[find(y)] - 1), unite(find(x), find(y));
        }
        printf("%d\n", answer);
    }
    return 0;
}