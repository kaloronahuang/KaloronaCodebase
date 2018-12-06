// P1801.cpp
#include <iostream>
#include <cstdio>
#include <queue>
#define ll long long
using namespace std;
const int maxn = 210000;
ll M, N, arr[maxn], num, idx = 0, r = 1;
priority_queue<ll> qmax;
priority_queue< ll, vector<ll>, greater<ll> > qmin;
int main()
{
    scanf("%lld%lld", &M, &N);
    for (int i = 1; i <= M; i++)
        scanf("%lld", &arr[i]);
    for (int i = 1; i <= N; i++)
    {
        scanf("%lld", &num), idx++;
        for (int prev = r; prev <= num; prev++)
        {
            qmax.push(arr[prev]);
            if (i == qmax.size())
                qmin.push(qmax.top()), qmax.pop();
        }
        r = num + 1;
        printf("%d\n", qmin.top()), qmax.push(qmin.top()), qmin.pop();
    }
    return 0;
}