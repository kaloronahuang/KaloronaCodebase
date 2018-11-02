// P1282.cpp
#include <iostream>
#include <cstring>
#include <algorithm>

const int INF = 0x7fffffff;
const int maxn = 1010;
int n;
int ua[maxn];
int db[maxn];
int F[1010][1010];

void init()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> ua[i] >> db[i];
    memset(F, INF, sizeof(F));
}

int genDP()
{
    for (int k = 0; k < n; k++)
        for (int i = k; i < n; i++)
        {
            
        }
}