// E1.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110;

int n;

struct node
{
    int cnt[26], len;
    void clear() { memset(cnt, 0, sizeof(cnt)), len = 0; }
    bool operator<(const node &rhs) const
    {
        for (int i = 0; i < 26; i++)
            if (cnt[i] < rhs.cnt[i])
                return true;
            else if (cnt[i] > rhs.cnt[i])
                return false;
        return false;
    }
};
map<node, int> mp;
vector<node> rec[3];
vector<string> strrec[3];
node buck[MAX_N];

node toNode(const string &str)
{
    node ret;
    ret.clear();
    for (int i = 0; i < str.length(); i++)
        ret.cnt[str[i] - 'a']++, ret.len++;
    return ret;
}

void query(int l, int r, int idx)
{
    cout << "? " << l << " " << r << endl;
    rec[idx].resize((r - l + 2) * (r - l + 1) / 2);
    for (int cnt = 0; cnt < (r - l + 2) * (r - l + 1) / 2; cnt++)
    {
        string str;
        cin >> str;
        rec[idx].push_back(toNode(str));
        strrec[idx].push_back(str);
    }
}

int main()
{
    cin >> n;
    if (n == 1)
        query(1, n, 0), cout << "! " << strrec[0][0] << endl, exit(0);
    query(1, n, 0), query(1, n - 1, 1);
    for (int i = 0, siz = rec[0].size(); i < siz; i++)
        mp[rec[0][i]]++;
    for (int i = 0, siz = rec[1].size(); i < siz; i++)
        mp[rec[1][i]]--;
    for (map<node, int>::iterator it = mp.begin(); it != mp.end(); it++)
        if (it->second == 1)
            buck[it->first.len] = it->first;
    string ans;
    for (int i = 1; i <= n; i++)
    {
        char bit;
        for (int c = 0; c < 26; c++)
            if (buck[i].cnt[c] - buck[i - 1].cnt[c] > 0)
                bit = c + 'a';
        ans = bit + ans;
    }
    cout << "! " << ans << endl;
    return 0;
}