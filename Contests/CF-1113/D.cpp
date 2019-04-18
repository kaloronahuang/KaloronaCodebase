// D.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 5050;
char str[MAX_N];
long long ans, n, cnt[26];

void goFuck() { printf("Impossible"), exit(0); }

int main()
{
    scanf("%s", str + 1), n = strlen(str + 1);
    char opt = str[1];
    string st = str + 1;
    for (int i = 1; i <= n; i++)
        cnt[str[i] - 'a']++;
    for (int i = 0; i < 26; i++)
        if (cnt[i] == n || cnt[i] == n - 1)
            goFuck();
    for (int i = 1; i < n; i++)
    {
        bool flag = true;
        string sub = st.substr(i) + st.substr(0, i);
        for (int pt = 0; pt < sub.length(); pt++)
            if (sub[pt] != sub[sub.length() - pt - 1])
            {
                flag = false;
                break;
            }
        if (flag && sub != st)
            printf("1"), exit(0);
    }
    printf("2");
    return 0;
}