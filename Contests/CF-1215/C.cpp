// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n;
char str1[MAX_N], str2[MAX_N];

struct point
{
    int idx, a1, a2;
};

int main()
{
    scanf("%d", &n);
    scanf("%s", str1 + 1), scanf("%s", str2 + 1);
    int tot0 = 0, tot1 = 0;
    for (int i = 1; i <= n; i++)
    {
        tot0 += (str1[i] == 'a'), tot1 += (str1[i] == 'b');
        tot0 += (str2[i] == 'a'), tot1 += (str2[i] == 'b');
    }
    if (tot0 % 2 == 1 || tot1 % 2 == 1)
        puts("-1"), exit(0);
    queue<int> q1, q2;
    for (int i = 1; i <= n; i++)
    {
        if (str1[i] == 'b' && str2[i] == 'a')
            q1.push(i);
        if (str1[i] == 'a' && str2[i] == 'b')
            q2.push(i);
    }
    int siz1 = q1.size(), siz2 = q2.size();
    vector<pair<int, int>> ans;
    for (int i = 1; i + 1 <= siz1; i += 2)
    {
        int pos1 = q1.front();
        q1.pop();
        int pos2 = q1.front();
        q1.pop();
        ans.push_back(make_pair(pos1, pos2));
    }
    for (int i = 1; i + 1 <= siz2; i += 2)
    {
        int pos1 = q2.front();
        q2.pop();
        int pos2 = q2.front();
        q2.pop();
        ans.push_back(make_pair(pos1, pos2));
    }
    if (q1.size() == 1 && q2.size() == 1)
    {
        int pos1 = q1.front(), pos2 = q2.front();
        ans.push_back(make_pair(pos1, pos1)), ans.push_back(make_pair(pos1, pos2));
    }
    printf("%d\n", ans.size());
    for (int i = 0, siz = ans.size(); i < siz; i++)
        printf("%d %d\n", ans[i].first, ans[i].second);
    return 0;
}