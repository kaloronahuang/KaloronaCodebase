// CH0501.cpp
#include <cstdio>
#include <algorithm>
#define ll long long
#define regi register int
using namespace std;
const int maxn = 100200;
ll A[maxn], n;
int main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &A[i]);
    sort(A + 1, A + n + 1);
    ll pos = 0;
    if (n & 1)
        pos = A[(n + 1) >> 1];
    else
        pos = A[n >> 1];
    ll result = 0;
    for (regi i = 1; i <= n; i++)
        result += abs(pos - A[i]);
    printf("%lld", result);
    return 0;
}