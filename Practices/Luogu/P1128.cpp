// P1128.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 502000;
vector<int> vec;
bool isPrime[MAX_N];
ll quick_pow(ll bas, ll tim)
{
    ll ans = 1;
    while (tim)
    {
        if (tim & 1)
            ans = bas * ans;
        bas = bas * bas;
        tim >>= 1;
    }
    return ans;
}
int main()
{
    ll ans = 1;
    memset(isPrime, true, sizeof(isPrime));
    int n, x = 2;
    scanf("%d", &n);
    while (n != 1)
        if (n % x == 0)
            n /= x, vec.push_back(x);
        else
            x++;
    for (int i = 2; i < MAX_N; i++)
        if (isPrime[i])
            for (int j = 2; j * i < MAX_N; j++)
                isPrime[i * j] = false;
    reverse(vec.begin(), vec.end());
    vector<int>::iterator it = vec.begin();
    for (int i = 2; i < MAX_N && it != vec.end(); i++)
        if (isPrime[i])
            ans = ans * quick_pow(i, *it - 1), it++;
    printf("%lld", ans);
    return 0;
}