// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010;

struct act
{
    int ai, bi, di, id;
    bool operator<(const act &A) const { return di == A.di ? min(ai, A.bi) < min(bi, A.ai) : di < A.di; }
} acts[MAX_N];

int n;

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &acts[i].ai);
    for (int i = 1; i <= n; i++)
        scanf("%d", &acts[i].bi), acts[i].di = (acts[i].ai < acts[i].bi) ? -1 : ((acts[i].ai == acts[i].bi) ? 0 : 1), acts[i].id = i;
    sort(acts + 1, acts + 1 + n);
    int t1 = acts[1].ai, t2 = acts[1].ai + acts[1].bi;
    for (int i = 2; i <= n; i++)
        t2 = max(t1 + acts[i].ai, t2) + acts[i].bi, t1 += acts[i].ai;
    printf("%d\n", t2);
    for (int i = 1; i <= n; i++)
        printf("%d ", acts[i].id);
    return 0;
}