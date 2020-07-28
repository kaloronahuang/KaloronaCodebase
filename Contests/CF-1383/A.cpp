// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int T, n, mem[22];
char A[MAX_N], B[MAX_N];

int find(int x) { return mem[x] == x ? x : mem[x] = find(mem[x]); }

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%s%s", &n, A + 1, B + 1);
        bool valid = true;
        for (int i = 1; i <= n; i++)
            valid &= A[i] <= B[i];
        if (!valid)
        {
            puts("-1");
            continue;
        }
        int ans = 0;
        for (int i = 1; i <= 20; i++)
            mem[i] = i;
        for (int i = 1; i <= n; i++)
            if (find(A[i] - 'a' + 1) != find(B[i] - 'a' + 1))
            {
                mem[find(A[i] - 'a' + 1)] = find(B[i] - 'a' + 1);
                ans++;
            }
        printf("%d\n", ans);
    }
    return 0;
}