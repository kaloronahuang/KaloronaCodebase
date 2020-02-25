// CF1276A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1.5e5 + 200;
const char *one = "one", *two = "two";

int T, n;
char str[MAX_N];
vector<int> onepos, twopos;

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        map<int, bool> mp;
        onepos.clear(), twopos.clear();
        scanf("%s", str + 1), n = strlen(str + 1);
        for (int i = 1; i <= n - 2; i++)
        {
            for (int j = 0; j <= 3; j++)
                if (j == 3)
                    onepos.push_back(i);
                else if (str[i + j] != one[j])
                    break;
            for (int j = 0; j <= 3; j++)
                if (j == 3)
                    twopos.push_back(i);
                else if (str[i + j] != two[j])
                    break;
        }
        int cnt = 0;
        for (int i = 0, siz = onepos.size(); i < siz; i++)
        {
            int pos = onepos[i];
            if (pos > 2 && str[pos - 2] == 't' && str[pos - 1] == 'w')
                onepos[i] = 1e9, cnt++, mp[pos] = true;
        }
        printf("%lld\n", 1LL * onepos.size() - cnt + twopos.size());
        for (int i = 0, siz = onepos.size(); i < siz; i++)
            if (onepos[i] != 1e9)
                printf("%d ", onepos[i] + 1);
        for (int i = 0, siz = twopos.size(); i < siz; i++)
            if (mp[twopos[i] + 2] == true)
                printf("%d ", twopos[i] + 2);
            else
                printf("%d ", twopos[i] + 1);
        puts("");
    }
    return 0;
}