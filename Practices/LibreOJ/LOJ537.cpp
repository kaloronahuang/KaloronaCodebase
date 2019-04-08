// LOJ537.cpp
#include <bits/stdc++.h>
#define ll unsigned long long
using namespace std;
const int MAX_N = 5e6 + 1000;
int cnt[MAX_N], len, n;
char str[MAX_N];
int mapping(char ch)
{
    switch (ch)
    {
    case 'A':
        return 0;
    case 'G':
        return 1;
    case 'C':
        return 2;
    case 'T':
        return 3;
    }
}
int main()
{
    scanf("%s", str + 1), len = strlen(str + 1);
    scanf("%d", &n);
    for (int i = 1; i + n - 1 <= len; i++)
    {
        ll hashCode = 0;
        for (int j = i; j <= i + n - 1; j++)
            hashCode = (hashCode << 2) + mapping(str[j]);
        cnt[hashCode]++;
    }
    int ans = 0;
    for (int i = 0; i < MAX_N; i++)
        ans = max(ans, cnt[i]);
    printf("%d", ans);
    return 0;
}