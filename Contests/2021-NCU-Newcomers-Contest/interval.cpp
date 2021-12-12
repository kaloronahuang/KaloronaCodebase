// interval.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e6 + 200;

typedef long long ll;

int n, seq[MAX_N], ans;

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]);
    for (int i = 1; i <= n; i++)
    {
        int coll = seq[i], pans = seq[i];
        for (int j = i - 1; j >= 1 && j >= i - 29; j--)
            if (coll & seq[j])
                break;
            else
                pans += seq[j], coll |= seq[j];
        ans = max(ans, pans);
    }
    printf("%d\n", ans);
    return 0;
}