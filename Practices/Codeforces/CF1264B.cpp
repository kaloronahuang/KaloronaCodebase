// CF1264B.cpp
#include <bits/stdc++.h>

using namespace std;

int n;
map<int, int> mp;

int main()
{
    for (int i = 0; i <= 3; i++)
        scanf("%d", &mp[i]), n += mp[i];
    for (int startId = 0; startId <= 3; startId++)
        if (mp[startId])
        {
            vector<int> res;
            map<int, int> curt = mp;
            curt[startId]--, res.push_back(startId);
            int last_val = startId;
            for (int i = 1; i <= n - 1; i++)
                if (curt[last_val - 1] > 0)
                    curt[last_val - 1]--, res.push_back(last_val - 1), last_val--;
                else if (curt[last_val + 1] > 0)
                    curt[last_val + 1]--, res.push_back(last_val + 1), last_val++;
                else
                    break;
            if (res.size() == n)
            {
                puts("YES");
                for (int i = 0; i < n; i++)
                    printf("%d ", res[i]);
                puts("");
                return 0;
            }
        }
    puts("NO");
    return 0;
}