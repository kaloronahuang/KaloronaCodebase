// B.cpp
#include <bits/stdc++.h>
#define ull unsigned long long

using namespace std;

int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + (ch - '0'), ch = getchar();
    return x * f;
}

const int MAX_N = 2020, MAX_K = 35;
const ull bitnum = 133;

int n, k;
long long ans = 0;
string str[MAX_N];
ull hash_val[MAX_N];
unordered_map<ull, int> mp;

int main()
{
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
    {
        cin >> str[i];
        for (int ptr = 0; ptr < k; ptr++)
            hash_val[i] = hash_val[i] * bitnum + str[i][ptr] - 'a';
        mp[hash_val[i]]++;
    }
    for (int firstCard = 1; firstCard <= n; firstCard++)
    {
        mp[hash_val[firstCard]]--;
        for (int secondCard = firstCard + 1; secondCard <= n; secondCard++)
            if (hash_val[firstCard] != hash_val[secondCard])
            {
                mp[hash_val[secondCard]]--;
                ull target = 0;
                for (int i = 0; i < k; i++)
                    if (str[firstCard][i] != str[secondCard][i])
                    {
                        char bit;
                        if (str[firstCard][i] != 'S' && str[secondCard][i] != 'S')
                            bit = 'S';
                        if (str[firstCard][i] != 'E' && str[secondCard][i] != 'E')
                            bit = 'E';
                        if (str[firstCard][i] != 'T' && str[secondCard][i] != 'T')
                            bit = 'T';
                        target = target * bitnum + bit - 'a';
                    }
                    else
                        target = target * bitnum + str[firstCard][i] - 'a';
                ans += mp[target];
            }
        for (int secondCard = firstCard + 1; secondCard <= n; secondCard++)
            if (hash_val[firstCard] != hash_val[secondCard])
                mp[hash_val[secondCard]]++;
    }
    for (unordered_map<ull, int>::iterator it = mp.begin(); it != mp.end(); it++)
        ans += 1LL * (it->second) * (it->second - 1) * (it->second - 2);
    printf("%lld\n", ans);
    return 0;
}