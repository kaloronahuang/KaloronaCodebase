// HDU-1848.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010;

int n, m, p, sg[MAX_N], fib[MAX_N], tot, mark[MAX_N];

void init()
{
    fib[0] = fib[1] = tot = 1;
    do
    {
        fib[tot + 1] = fib[tot] + fib[tot - 1], tot++;
    } while (fib[tot] < MAX_N);
    for (int i = 1; i < MAX_N; i++)
    {
        for (int j = 1; j <= tot && i - fib[j] >= 0; j++)
            mark[sg[i - fib[j]]] = i;
        for (int j = 0; j < MAX_N; j++)
            if (mark[j] != i)
            {
                sg[i] = j;
                break;
            }
    }
}

int main()
{
    init();
    while (scanf("%d%d%d", &n, &m, &p) != EOF && !(n == 0 && m == 0 && p == 0))
        puts((sg[n] ^ sg[m] ^ sg[p]) ? "Fibo" : "Nacci");
    return 0;
}