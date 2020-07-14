// B.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const char cf[] = "codeforces";

ll n, block, freq[20];

int main()
{
    scanf("%lld", &n);
    ll curt = 1;
    int idx = pow(n, 1.0 / 10.0);
    for (int i = 0; i < 10; i++)
        freq[i] = idx, curt *= idx;
    for (int i = 0; i < 10; i++)
        if (curt < n)
            curt /= freq[i], freq[i]++, curt *= freq[i];
    for (int i = 0; i < 10; i++)
        for (int j = 1; j <= freq[i]; j++)
            putchar(cf[i]);
    putchar('\n');
    return 0;
}