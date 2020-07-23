// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, ai[MAX_N], si[MAX_N];
map<int, int> mp, tmp;

int main()
{
    scanf("%d", &n);
    for (int i = 1, x; i <= n; i++)
        scanf("%d", &ai[i]), mp[ai[i]]++;
    if (mp.size() <= 3)
    {
        vector<int> vi;
        for (auto x : mp)
            vi.push_back(x.first);
        bool flag = false;
        do
        {
            int len = vi.size();
            tmp.clear();
            for (int i = 1; i <= 2; i++)
                si[i] = vi[(i - 1) % len];
            for (int i = 3; i <= n; i++)
                si[i] = si[i - 1] ^ si[i - 2];
            for (int i = 1; i <= n; i++)
                tmp[si[i]]++;
            bool cflag = true;
            for (auto x : tmp)
                cflag &= mp[x.first] == x.second;
            flag |= cflag;
        } while (next_permutation(vi.begin(), vi.end()));
        puts(flag ? "Yes" : "No");
    }
    else
        puts("No");
    return 0;
}