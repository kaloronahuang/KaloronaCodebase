// sequence.cpp
// tag:AC automaton;
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 1e5;
char str1[4100], str2[4100];
int trie[MAX_N][2], tot = 1, fa[MAX_N], len = 4000000;
string ans;
string mint(const string a, const string b)
{
    if (a.length() != b.length())
        return (a.length() < b.length()) ? a : b;
    for (int i = 0; i < a.length(); i++)
        if (a[i] < b[i])
            return a;
        else if (a[i] > b[i])
            return b;
    return a;
}
void insert(char *str, int st, int len, int pt)
{
    if (st == len)
        return;
    int p = pt;
    for (int i = st; i < len; i++)
    {
        if (trie[p][str[i] - '0'] == 0)
            trie[p][str[i] - '0'] = ++tot, fa[tot] = p;
        insert(str, i + 1, len, fa[p]);
        insert(str, i + 1, len, p);
        p = trie[p][str[i] - '0'];
    }
}
void dfs(int u, string acc, int lens)
{
    if (lens > len)
        return;
    if (u == 0)
    {
        ans = mint(ans, acc), len = lens;
        return;
    }
    for (int i = 0; i < 2; i++)
        dfs(trie[u][i], acc + (char)(i + '0'), lens + 1);
}
int main()
{
    freopen("sequence.in", "r", stdin);
    freopen("sequence.out", "w", stdout);
    ans.resize(4001, '1');
    scanf("%s\n%s", str1, str2);
    insert(str1, 0, strlen(str1), 1);
    insert(str2, 0, strlen(str2), 1);
    dfs(1, "", 0);
    cout << ans << endl;
    return 0;
}