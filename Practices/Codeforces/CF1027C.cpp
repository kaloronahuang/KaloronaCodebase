// CF1027C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e4 + 200;

int T, bucket[MAX_N], n;

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        memset(bucket, 0, sizeof(bucket));
        scanf("%d", &n);
        int id = 0;
        vector<long long> vec;
        for (int i = 1, tmp; i <= n; i++)
        {
            scanf("%d", &tmp), bucket[tmp]++, id = (bucket[tmp] >= 4) ? tmp : id;
            if (bucket[tmp] == 2)
                vec.push_back(tmp);
        }
        if (id != 0)
        {
            for (int j = 1; j <= 4; j++)
                printf("%d ", id);
            puts("");
            continue;
        }
        sort(vec.begin(), vec.end());
        int ans[2] = {vec[0], vec[1]};
        for (int i = 2; i < vec.size(); i++)
            if (ans[0] * vec[i] < ans[1] * vec[i - 1])
                ans[0] = vec[i - 1], ans[1] = vec[i];
        printf("%d %d %d %d\n", ans[0], ans[0], ans[1], ans[1]);
    }
    return 0;
}