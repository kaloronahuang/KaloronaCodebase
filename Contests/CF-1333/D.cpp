// D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3030;

typedef pair<int, int> pii;

int n, k;
char str[MAX_N];

int main()
{
    scanf("%d%d%s", &n, &k, str + 1);
    vector<vector<pii>> vec;
    int min_time = 0, max_time = 0;
    while (true)
    {
        vector<pii> tmp;
        for (int i = 1; i < n; i++)
            if (str[i] == 'R' && str[i + 1] == 'L')
                tmp.push_back(make_pair(i, i + 1));
        for (int i = 1; i < n; i++)
            if (str[i] == 'R' && str[i + 1] == 'L')
                swap(str[i], str[i + 1]), i++;
        if (tmp.empty())
            break;
        min_time++, max_time += tmp.size();
        vec.push_back(tmp);
    }
    if (k > max_time || k < min_time)
        puts("-1"), exit(0);
    int diff = k - min_time;
    stack<vector<pii>> ans;
    for (int i = vec.size() - 1; i >= 0; i--)
    {
        if (diff >= vec[i].size() - 1)
        {
            diff -= vec[i].size() - 1;
            while (!vec[i].empty())
                ans.push(vector<pii>{vec[i].back()}), vec[i].pop_back();
        }
        else if (diff == 0)
            ans.push(vec[i]);
        else
        {
            while (diff)
                ans.push(vector<pii>{vec[i].back()}), vec[i].pop_back(), diff--;
            ans.push(vec[i]);
        }
    }
    while (!ans.empty())
    {
        printf("%lld ", 1LL * ans.top().size());
        while (!ans.top().empty())
            printf("%d ", ans.top().back().first), ans.top().pop_back();
        ans.pop(), puts("");
    }
    return 0;
}