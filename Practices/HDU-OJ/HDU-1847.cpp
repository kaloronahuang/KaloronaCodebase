// HDU-1847.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010;

int n;
bool f[MAX_N];

int main()
{
    f[0] = false;
    for (int i = 1; i < MAX_N; i++)
        for (int j = 0; (1 << j) <= i; j++)
            f[i] |= f[i - (1 << j)] == false;
    while (scanf("%d", &n) != EOF)
        puts(f[n] ? "Kiki" : "Cici");
    return 0;
}