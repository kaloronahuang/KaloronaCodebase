// FOJ3785.cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int MAX_N = 1010;

int n, ai[MAX_N], bi[MAX_N], bits[MAX_N * 2000];
vector<int> vec;

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

char getHex(int bit)
{
    if (bit < 10)
        return bit + '0';
    return bit - 10 + 'A';
}

void multiply(int x)
{
    int rem = 0;
    for (int i = 1; i <= bits[0]; i++)
    {
        bits[i] = bits[i] * x + rem;
        rem = bits[i] / 16;
        bits[i] %= 16;
    }
    while (rem > 0)
        bits[++bits[0]] = rem % 16, rem /= 16;
}

signed main()
{
    /*
    freopen("fraction.in", "r", stdin);
    freopen("fraction.out", "w", stdout);
    */
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld%lld", &ai[i], &bi[i]);
    // considering to factorize the bi and prod them;
    bits[0] = 1, bits[1] = 1;
    for (int idx = 1; idx <= n; idx++)
    {
        int bas = bi[idx] / gcd(ai[idx], bi[idx]);
        for (int i = 2; 1LL * i * i <= bas; i++)
            if (bas % i == 0)
            {
                vec.push_back(i);
                while (bas % i == 0)
                    bas /= i;
            }
        if (bas != 1)
            vec.push_back(bas);
    }
    sort(vec.begin(), vec.end()), vec.erase(unique(vec.begin(), vec.end()), vec.end());
    while (!vec.empty())
        multiply(vec.back()), vec.pop_back();
    for (int i = bits[0]; i >= 1; i--)
        printf("%c", getHex(bits[i]));
    return 0;
}