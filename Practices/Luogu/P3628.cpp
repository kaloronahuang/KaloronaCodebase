// P3628.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 1e6 + 2000;
ll n, xi[MAX_N], a, b, c, S[MAX_N], f[MAX_N], q[MAX_N], head, tail;
ll pow(ll num) { return num * num; }
double slope(int j1, int j2)
{
    return double((f[j1] - f[j2] + b * (S[j2] - S[j1]) + a * (pow(S[j1]) - pow(S[j2])))) / double(2 * a * (S[j1] - S[j2]));
}
int main()
{
    scanf("%lld%lld%lld%lld", &n, &a, &b, &c);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &xi[i]), S[i] = S[i - 1] + xi[i];
    head = 1, tail = 1;
    for (int i = 1; i <= n; i++)
    {
        while (head < tail && slope(q[head], q[head + 1]) <= S[i] * 1.0)
            head++;
        f[i] = f[q[head]] + a * pow(S[i] - S[q[head]]) + b * (S[i] - S[q[head]]) + c;
        while (head <= tail && slope(q[tail - 1], q[tail]) >= slope(q[tail], i))
            tail--;
        q[++tail] = i;
    }
    printf("%lld", f[n]);
    return 0;
}