// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5050;

struct psi
{
    string first;
    int second;
    bool operator<(const psi &rhs) const { return lexicographical_compare(first.begin(), first.end(), rhs.first.begin(), rhs.first.end()) || (first == rhs.first && second < rhs.second); }
};

psi make_pair(string A, int B) { return psi{A, B}; }

int n, k, mem[MAX_N];
string str, INF, ans;
string dp[110][110][110];

bool compare(const string &A, const string &B) { return lexicographical_compare(A.begin(), A.end(), B.begin(), B.end()); }

int find(int x) { return x == mem[x] ? x : mem[x] = find(mem[x]); }

void subtask1Handler()
{
    for (int i = 1; i <= (n << 1); i++)
        dp[i][i][1] = "0" + string(1, str[i]), INF += 'z';
    for (int len = 2; len <= n; len++)
    {
        for (int i = 1; i <= (n << 1) && i + len - 1 <= (n << 1); i++)
        {
            int j = i + len - 1;
            dp[i][j][1] = '0' + str.substr(i, len);
            for (int t = 2; t <= min(len, k); t++)
            {
                dp[i][j][t] = INF;
                for (int mid = i + t - 2; mid < j; mid++)
                    dp[i][j][t] = min(dp[i][j][t], max(dp[i][mid][t - 1], '0' + str.substr(mid + 1, j - mid), compare), compare);
            }
        }
    }
    for (int i = 1; i <= n; i++)
        ans = min(ans, dp[i][i + n - 1][k], compare);
}

void subtask2Handler()
{
    for (int i = 1; i <= n; i++)
    {
        int j = i + n - 1, len = n;
        multiset<psi> ms;
        for (int ptr = i; ptr <= j; ptr++)
            ms.insert(make_pair(str.substr(ptr, 1), ptr)), mem[ptr] = ptr;

        if (len == k)
            ans = min(ans, "0" + ms.rbegin()->first);
        ms.erase(make_pair(str.substr(i, 1), i));
        string header = str.substr(i, 1);

        for (int t = len - 1; t >= 1; t--)
        {
            // to combine;
            psi curt = *ms.rbegin();
            ms.erase(curt);
            int pre_pos = find(curt.second - 1);
            string pre_str = str.substr(pre_pos, curt.second - pre_pos);
            if (pre_pos == i)
                header += curt.first;
            else
            {
                multiset<psi>::iterator it = ms.find(make_pair(pre_str, pre_pos));
                psi pre = *it;
                ms.erase(it);
                pre_str += curt.first;
                ms.insert(make_pair(pre_str, pre_pos));
            }
            mem[find(curt.second)] = find(pre_pos);
            string tmp = header;
            if (!ms.empty())
                tmp = max(tmp, ms.rbegin()->first, compare);
            if (t == k)
                ans = min(ans, '0' + tmp);
        }
    }
}

int main()
{
    freopen("B.in5", "r", stdin);
    scanf("%d%d", &n, &k);
    cin >> str, INF = 'z';
    str = '0' + str;
    for (int i = 1; i <= n; i++)
        str = str + str[i];
    ans = INF;
    if (n <= 50)
        subtask1Handler();
    else
        subtask2Handler();
    for (int i = 1; i < ans.length(); i++)
        putchar(ans[i]);
    putchar('\n');
    return 0;
}