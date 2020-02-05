// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 200;

int n, ai[MAX_N], A[MAX_N], B[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &A[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &B[i]);
    sort(A + 1, A + 1 + n), sort(B + 1, B + 1 + n);
    int ptr = n, cnt = 0;
    for (int i = n; i >= 1; i--)
        if (B[ptr] >= A[i])
            cnt++, ptr--;
    printf("%d\n", cnt);
    return 0;
}