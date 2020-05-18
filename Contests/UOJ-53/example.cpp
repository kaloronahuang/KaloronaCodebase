#include "lcs.h"
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 110;

vector<int> vec;

bool judge(int x, int y)
{
    // x < y;
    int now[2] = {x, y};
    return get_lcs(2, now) == 2;
}

void find_permutation(int n, int res[])
{
    vec.push_back(1);
    for (int i = 2; i <= n; i++)
    {
        int l = 0, r = vec.size() - 1, rk;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if (judge(i, vec[mid]))
                // bef;
                r = mid - 1, rk = mid;
            else
                l = mid + 1, rk = mid + 1;
        }
        //printf("rk : %d\n", rk);
        vector<int> nxt;
        int delta = 0;
        for (int j = 0, siz = vec.size(); j <= siz; j++)
        {
            int crk = j + delta;
            if (crk > siz)
                break;
            if (crk == rk)
                delta++, nxt.push_back(i), j--;
            else
                nxt.push_back(vec[j]);
        }
        vec = nxt;
        puts("");
    }
    for (int i = 0; i < n; i++)
        res[i] = vec[i];
}
