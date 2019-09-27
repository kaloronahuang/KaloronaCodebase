// P2587.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int seqA[MAX_N], seqB[MAX_N], n;

int battle(int A[], int B[])
{
    int head = 1, tail = n;
    int lft = 1, rig = n;
    int ans = 0;
    while (head <= tail && lft <= rig)
        if (A[head] > B[lft])
            ans += 2, head++, lft++;
        else if (A[tail] > B[rig])
            ans += 2, tail--, rig--;
        else
            ans += (A[head] == B[rig]), head++, rig--;
    return ans;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seqA[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seqB[i]);
    sort(seqA + 1, seqA + 1 + n);
    sort(seqB + 1, seqB + 1 + n);
    printf("%d %d", battle(seqA, seqB), (n << 1) - battle(seqB, seqA));
    return 0;
}