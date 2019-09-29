// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n;
struct node
{
    int val, id;
    bool operator<(const node &nd) const { return val < nd.val; }
} nodes[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        nodes[i].id = i, scanf("%d", &nodes[i].val);
    sort(nodes + 1, nodes + 1 + n);
    for (int i = 1; i <= n; i++)
        printf("%d ", nodes[i].id);
    return 0;
}