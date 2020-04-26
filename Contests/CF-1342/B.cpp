// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int T, n;
char str[MAX_N];

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%s", str + 1), n = strlen(str + 1);
        int cnt[2] = {0, 0};
        for (int i = 1; i <= n; i++)
            cnt[str[i] - '0']++;
        if (cnt[0] == n || cnt[1] == n)
        {
            printf("%s\n", str + 1);
            continue;
        }
        string ans;
        for (int i = 1; i <= n; i++)
        {
            if (str[i] == '1' && str[i + 1] == '0')
                ans += "10", i++;
            else
                ans += "10";
        }
        cout << ans << endl;
    }
    return 0;
}