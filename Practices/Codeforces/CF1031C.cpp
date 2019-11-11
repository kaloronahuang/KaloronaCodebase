// CF1031C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int a, b, seqA[MAX_N], seqB[MAX_N];
bool vis[MAX_N];

int main()
{
    scanf("%d%d", &a, &b);
    int k = 1;
    for (int i = 0; i < MAX_N; i++)
        if (((1LL * i * (i + 1)) >> 1) <= a + b)
            k = i;
        else
            break;
    for (int i = k, acc = a; i >= 1 && acc > 0; i--)
        if (acc >= i)
            acc -= i, vis[i] = true, seqA[++seqA[0]] = i;
    for (int i = 1, acc = b; i <= k && acc > 0; i++)
        if (acc >= i && vis[i] == false)
            acc -= i, seqB[++seqB[0]] = i;
    printf("%d\n", seqA[0]);
    for (int i = 1; i <= seqA[0]; i++)
        printf("%d ", seqA[i]);
    puts("");
    printf("%d\n", seqB[0]);
    for (int i = 1; i <= seqB[0]; i++)
        printf("%d ", seqB[i]);
    return 0;
}