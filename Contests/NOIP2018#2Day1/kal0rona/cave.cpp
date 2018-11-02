// cave.cpp
#include <iostream>
#include <algorithm>
#include <stack>
#include <cstdio>
using namespace std;

#define ll long long
const int maxn = 200;
const int maxm = 10020;
int n, m;
struct edge
{
    int to, next;
} edges[maxm];

struct istack
{
    int mem[maxm * 1000];
    ll head = -1;

    void push(int x)
    {
        mem[++head] = x;
    }

    int top()
    {
        return mem[head];
    }

    void pop()
    {
        if (head != -1)
            head--;
    }

    bool empty()
    {
        return head == -1;
    }
};
int head[maxn];
int current = 0;

void addpath(int a, int b)
{
    edges[current].to = b;
    edges[current].next = head[a];
    head[a] = current++;
}

bool dfs(int u, int dst, int strd)
{
    istack st, ac;
    st.push(u), ac.push(0);
    while (!st.empty())
    {
        int curt = st.top();
        int prev = ac.top();
        st.pop(), ac.pop();
        if (curt == dst && strd == prev)
            return true;
        if (prev > strd)
            continue;
        for (int i = head[curt]; i != -1; i = edges[i].next)
            st.push(edges[i].to), ac.push(prev + 1);
    }
    return false;
}

int main()
{
    freopen("cave.in", "r", stdin);
    freopen("cave.out", "w", stdout);
    scanf("%d%d", &n, &m);
    fill(head, head + maxn, -1);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        addpath(u, v);
    }
    int q;
    scanf("%d", &q);
    for (int i = 0; i < q; i++)
    {
        int a, b, l;
        scanf("%d%d%d", &l, &a, &b);
        bool res = dfs(a, b, l);
        if (res)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}