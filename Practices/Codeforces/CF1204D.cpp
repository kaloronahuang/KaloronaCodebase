// CF1204D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, INF = 0x3f3f3f3f;

char str[MAX_N];
int sta[MAX_N], n;
bool vis[MAX_N];

int main()
{
    scanf("%s", str + 1), n = strlen(str + 1);
    int ptr = 0;
    for (int i = 1; i <= n; i++)
        if (str[i] == '0' && ptr > 0)
            vis[sta[ptr--]] = 1;
        else if (str[i] == '1')
            sta[++ptr] = i;
    for (int i = 1; i <= n; i++)
        printf(vis[i] ? "1" : "0");
    return 0;
}