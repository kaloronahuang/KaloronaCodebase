// P1265.cpp
// tag:Prim

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iomanip>

using namespace std;

const int maxn = 5010;
const int INF = 0x7fffffff;

int n;
int x[maxn];
int y[maxn];

double getDist(int a, int b)
{
    return sqrt(pow(x[a] - x[b], 2) + pow(y[a] - y[b], 2));
}

bool vis[maxn];
double dis[maxn];

void init()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> x[i] >> y[i];
    memset(vis, false, sizeof(vis));
    memset(dis, INF, sizeof(INF));
}

double Prim()
{
    
}