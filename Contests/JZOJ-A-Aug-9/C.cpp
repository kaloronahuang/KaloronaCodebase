// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 2000;

int seq[MAX_N], n, prefix[MAX_N];
vector<int> vecs[MAX_N << 1];
int ans = 0;

bool compare(int a, int b) { return a > b; }

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]), prefix[i] = prefix[i - 1] + (seq[i] == i), vecs[seq[i] + i].push_back(min(seq[i], i));
    for (int i = 1; i <= 2 * n; i++)
        if (!vecs[i].empty())
        {
            sort(vecs[i].begin(), vecs[i].end(), compare);
            int tmp = 0;
            for (vector<int>::iterator it = vecs[i].begin(); it != vecs[i].end(); it++)
            {
                int rig = i - *it;
                tmp++, ans = max(ans, prefix[*it - 1] + prefix[n] - prefix[rig] + tmp);
            }
        }
    printf("%d", ans);
    return 0;
}