// CF1261A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2020;

int T, n, limit;
char str[MAX_N];

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%s", &n, &limit, str + 1);
        vector<pair<int, int> /**/> vec;
        for (int i = 1; i <= n; i++)
            if ((i & 1) && str[i] == ')')
            {
                // find the next ( to switch;
                for (int j = i; j <= n; j++)
                    if (str[j] == '(')
                    {
                        vec.push_back(make_pair(i, j));
                        reverse(str + i, str + j + 1);
                        break;
                    }
            }
            else if (((~i) & 1) && str[i] == '(')
            {
                for (int j = i; j <= n; j++)
                    if (str[j] == ')')
                    {
                        vec.push_back(make_pair(i, j));
                        reverse(str + i, str + j + 1);
                        break;
                    }
            }
        // now there is k/2 double pair;
        int rem = n >> 1, ptr = 2;
        while (rem > limit)
            rem--, vec.push_back(make_pair(ptr, ptr + 1)), ptr += 2;
        printf("%lld\n", 1LL * vec.size());
        for (int i = 0, siz = vec.size(); i < siz; i++)
            printf("%d %d\n", vec[i].first, vec[i].second);
    }
    return 0;
}