// CH1806.cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <map>
using namespace std;
const int maxn = 1020;
const int bitnum = 13331;
const int aitnum = 133;
#define ull unsigned long long
char strs[maxn][maxn];
map<ull, int> mapping;
ull prehash[maxn][maxn], pprehash[maxn][maxn], ps[maxn * maxn], pss[maxn * maxn], M, N, A, B, Q;
int main()
{
    scanf("%d%d%d%d", &M, &N, &A, &B);
    ps[0] = pss[0] = 1;
    for (int i = 1; i < maxn; i++)
        ps[i] = ps[i - 1] * bitnum, pss[i] = pss[i - 1] * aitnum;
    for (int i = 1; i <= M; i++)
    {
        scanf("%s", strs[i] + 1);
        for (int j = 1; j <= N; j++)
            prehash[i][j] = strs[i][j] - '0';
    }
    for (int i = 1; i <= M; i++)
        for (int j = 1; j <= N; j++)
            prehash[i][j] += prehash[i - 1][j] * bitnum;
    for (int i = 1; i <= M; i++)
        for (int j = 1; j <= N; j++)
            prehash[i][j] += prehash[i][j - 1] * aitnum;

    for (int i = A; i <= M; i++)
        for (int j = B; j <= N; j++)
        {
            ull hscode;
            hscode = prehash[i][j] - prehash[i - A][j] * ps[A] - prehash[i][j - B] * pss[B] +
                     prehash[i - A][j - B] * ps[A] * pss[B];
            mapping[hscode] = 1;
        }

    scanf("%d", &Q);
    for (int T = 0; T < Q; T++)
    {
        ull hscode = 0;
        for (int i = 1; i <= A; i++)
        {
            scanf("%s", strs[i] + 1);
            for (int j = 1; j <= B; j++)
                pprehash[i][j] = strs[i][j] - '0';
        }
        for (int i = 1; i <= A; i++)
            for (int j = 1; j <= B; j++)
                pprehash[i][j] += pprehash[i - 1][j] * bitnum;
        for (int i = 1; i <= A; i++)
            for (int j = 1; j <= B; j++)
                pprehash[i][j] += pprehash[i][j - 1] * aitnum;
        hscode = pprehash[A][B];
        if (mapping.count(hscode))
            printf("1\n");
        else
            printf("0\n");
    }
    return 0;
}