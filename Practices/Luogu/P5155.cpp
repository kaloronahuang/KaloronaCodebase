// P5155.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 1e5 + 200, base = 1e5;

int n, stk[MAX_N], tail;
ll fi[MAX_N];

double slope(int a, int b) { return double(fi[b] - fi[a]) / double(b - a); }

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &fi[i]), fi[i] *= base;
    for (int i = 1; i <= n + 1; i++)
    {
        while (tail && slope(stk[tail - 1], stk[tail]) < slope(stk[tail - 1], i))
            tail--;
        stk[++tail] = i;
    }
    for (int i = 1, ptr = 0; i <= n; i++)
    {
        while (ptr < tail && stk[ptr] < i)
            ptr++;
        if (stk[ptr] == i)
            printf("%lld\n", fi[i]);
        else
            printf("%lld\n", ((stk[ptr] - i) * fi[stk[ptr - 1]] + (i - stk[ptr - 1]) * fi[stk[ptr]]) / (stk[ptr] - stk[ptr - 1]));
    }
    return 0;
}