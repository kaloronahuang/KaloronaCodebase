// answer.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 30100;

int n, m, p, q;
string buff, ans;
map<string, int> mp;

bool compare(const string &strA, const string &strB)
{
    if (strA == "")
        return true;
    for (int i = 0; i < m; i++)
        if (strA[i] < strB[i])
            return false;
        else if (strA[i] > strB[i])
            return true;
    return false;
}

int main()
{
    scanf("%d%d%d%d", &n, &m, &p, &q);
    for (int i = 1; i <= n; i++)
        cin >> buff, mp[buff]++;
    for (map<string, int>::iterator it = mp.begin(); it != mp.end(); it++)
        if (it->second == p && compare(ans, it->first))
            ans = it->first;
    if (ans.length() == 0)
        puts("-1");
    else
        cout << ans;
    return 0;
}