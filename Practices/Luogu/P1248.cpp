// P1248.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010;

struct node
{
    int a_time, b_time, d, id;

    bool operator<(const node &nd) const { return d == nd.d ? min(a_time, nd.b_time) < min(b_time, nd.a_time) : d < nd.d; }
} nodes[MAX_N];

int n;

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &nodes[i].a_time), nodes[i].id = i;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &nodes[i].b_time);
        nodes[i].d = nodes[i].a_time < nodes[i].b_time ? -1 : (nodes[i].a_time > nodes[i].b_time ? 1 : 0);
    }
    sort(nodes + 1, nodes + 1 + n);
    long long T_A = nodes[1].a_time, T_B = nodes[1].a_time + nodes[1].b_time;
    for (int i = 2; i <= n; i++)
        T_B = max(T_A + nodes[i].a_time, T_B) + nodes[i].b_time, T_A += nodes[i].a_time;
    printf("%lld\n", T_B);
    for (int i = 1; i <= n; i++)
        printf("%d ", nodes[i].id);
    return 0;
}