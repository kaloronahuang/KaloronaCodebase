// CH0502.cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdio>
#define ll long long
using namespace std;
const int maxn = 100200;
ll col[maxn], row[maxn], S[maxn];
ll N, M, T, ans;

void solveRow(int tot)
{
    for (int i = 1; i <= N; i++)
        row[i] -= (tot / N), S[i] = S[i - 1] + row[i];
    sort(S + 1, S + N + 1);
    ll mid = S[(N + 1) / 2];
    for (int idx = 1; idx <= N; idx++)
        ans += abs(S[idx] - mid);
}

void solveCol(int tot)
{
    for (int i = 1; i <= M; i++)
        col[i] -= (tot / M), S[i] = S[i - 1] + col[i];
    sort(S + 1, S + M + 1);
    ll mid = S[(M + 1) / 2];
    for (int idx = 1; idx <= M; idx++)
        ans += abs(S[idx] - mid);
}

int main()
{
    scanf("%d%d%d", &N, &M, &T);
    for (int i = 0; i < T; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        row[x]++, col[y]++;
    }
    // check the row;
    ll tot = 0;
    for (int i = 1; i <= N; i++)
        tot += row[i];
    bool toSolveRow = (tot % N) == 0;
    if (toSolveRow)
        solveRow(tot);
    tot = 0;
    for (int i = 1; i <= M; i++)
        tot += col[i];
    bool toSolveCol = (tot % M) == 0;
    if (toSolveCol)
        solveCol(tot);
    if (toSolveCol && toSolveRow)
        printf("both ");
    else if (toSolveCol)
        printf("column ");
    else if (toSolveRow)
        printf("row ");
    else
    {
        printf("impossible");
        return 0;
    }
    printf("%lld", ans);
    return 0;
}