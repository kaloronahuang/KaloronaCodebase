// CH2902.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define numA(num) matching[a[num]]
#define numB(num) matching[b[num]]
#define numC(num) matching[c[num]]
using namespace std;
char s1[30], s2[30], s3[30];
int a[30], b[30], c[30], nxt[30];
int matching[30], N, cur;
bool vis[30];
bool validiate()
{
    int nxt_bit = 0;
    for (int i = N - 1; i >= 0; i--)
    {
        if ((numA(i) + nxt_bit + numB(i)) % N - numC(i))
            return false;
        nxt_bit = (numA(i) + nxt_bit + numB(i)) / N;
    }
    return true;
}
bool cut()
{
    if (numA(0) + numB(0) >= N)
        return true;
    for (int i = N - 1; i >= 0; i--)
    {
        if (numA(i) == -1 || numB(i) == -1 || numC(i) == -1)
            continue;
        if ((numA(i) + numB(i)) % N - numC(i) && (numA(i) + numB(i) + 1) % N - numC(i))
            return true;
    }
    return false;
}
void dfs(int curt)
{
    if (cut())
        return;
    if (curt == N)
    {
        if (validiate())
        {
            for (int i = 0; i < N; i++)
                printf("%d ", matching[i]);
            exit(0);
        }
        return;
    }
    for (int i = N - 1; i >= 0; i--)
        if (!vis[i])
        {
            matching[nxt[curt]] = i;
            vis[i] = true;
            dfs(curt + 1);
            matching[nxt[curt]] = -1;
            vis[i] = false;
        }
}
void set(int x)
{
    if (!vis[x])
        vis[x] = true, nxt[cur++] = x;
}
int main()
{
    scanf("%d", &N);
    scanf("%s", s1), scanf("%s", s2), scanf("%s", s3);
    for (int i = 0; i < N; i++)
        a[i] = s1[i] - 'A', b[i] = s2[i] - 'A', c[i] = s3[i] - 'A';
    for (int i = N - 1; i >= 0; i--)
        set(a[i]), set(b[i]), set(c[i]);
    memset(vis, false, sizeof(vis));
    memset(matching, -1, sizeof(matching));
    dfs(0);
    return 0;
}