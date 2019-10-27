// cover.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 300100;

struct segment
{
    int l, r, val;
    bool operator<(const segment &nd) const { return val < nd.val; }
} org[MAX_N];
vector<segment> segs[MAX_N];
int n, m;

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &org[i].l, &org[i].r, &org[i].val);
    
    return 0;
}