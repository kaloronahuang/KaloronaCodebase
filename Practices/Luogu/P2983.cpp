// P2983.cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdio>

using namespace std;
#define ll long long

long long N, B;

struct chocolate
{
    long long p, c;
    double val;
    bool operator<(const chocolate &c_) const
    {
        return p < c_.p;
    }
} cs[100010];

void init()
{
    cin >> N >> B;
    for (long long i = 1; i <= N; i++)
        cin >> cs[i].p >> cs[i].c;
    sort(cs + 1, cs + 1 + N);
}

long long solve()
{
    long long ans = 0;
    long long B_remain = B;
    for (int i = 1; i <= N; i++)
    {
        ll k = B_remain / cs[i].p;
        if (k > cs[i].c)
        {
            B_remain -= cs[i].c * cs[i].p;
            ans += cs[i].c;
        }
        else
        {
            ans += k;
            break;
        }
    }
    return ans;
}

int main()
{
    init();
    cout << solve();
    return 0;
}