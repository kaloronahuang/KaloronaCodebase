// CF1083B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 200;

typedef long long ll;

int n, k;
char S[MAX_N], T[MAX_N];

int main()
{
    scanf("%d%d%s%s", &n, &k, S + 1, T + 1);
    ll gans = 0, pans = 1;
    for (int i = 1; i <= n; i++)
    {
        pans <<= 1;
        if (S[i] == 'b')
            pans--;
        if (T[i] == 'a')
            pans--;
        if (pans >= k)
        {
            gans += 1LL * k * (n - i + 1);
            break;
        }
        gans += pans;
    }
    printf("%lld\n", gans);
    return 0;
}