// C.cpp
#include <bits/stdc++.h>
#define pr pair<int, int>

using namespace std;

const int MAX_N = 5050;

int Ai[MAX_N], Bi[MAX_N], middle_stat[MAX_N], n, *curt_array;

vector<pr> vec;

void __solve(int l, int mid, int r)
{
    if (mid < l || mid >= r || l == r)
        return;
    // [l, mid] and [mid + 1, r] are both increasing;
    int curLft = mid, curRig = mid + 1;
    while (curLft > l && curRig < r && curt_array[curLft - 1] > curt_array[curRig + 1])
        curLft--, curRig++;
    if (curt_array[curLft] > curt_array[curRig])
    {
        for (int i = curLft, j = mid; i < j; i++, j--)
            vec.push_back(make_pair(i, j)), swap(curt_array[i], curt_array[j]);
        for (int i = mid + 1, j = curRig; i < j; i++, j--)
            vec.push_back(make_pair(i, j)), swap(curt_array[i], curt_array[j]);
        for (int i = curLft, j = curRig; i < j; i++, j--)
            vec.push_back(make_pair(i, j)), swap(curt_array[i], curt_array[j]);
        __solve(l, curLft - 1, mid), __solve(mid + 1, curRig, r);
    }
}

void solve(int l, int r)
{
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    solve(l, mid), solve(mid + 1, r);
    __solve(l, mid, r);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &Ai[i]), middle_stat[i] = Ai[i];
    for (int i = 1; i <= n; i++)
        scanf("%d", &Bi[i]);
    sort(middle_stat + 1, middle_stat + 1 + n);

    curt_array = Ai, solve(1, n);
    int current_stat = vec.size();

    curt_array = Bi, solve(1, n);

    printf("%d\n", vec.size());
    for (int i = 0; i < current_stat; i++)
        printf("%d %d\n", vec[i].first, vec[i].second);
    for (int i = vec.size() - 1; i >= current_stat; i--)
        printf("%d %d\n", vec[i].first, vec[i].second);
    return 0;
}