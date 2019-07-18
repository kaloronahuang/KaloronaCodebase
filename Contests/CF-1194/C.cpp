// C.cpp
#include <bits/stdc++.h>

using namespace std;

int q, req[30], weapon[30];
string s, t, p;

int main()
{
    scanf("%d", &q);
    while (q--)
    {
        cin >> s >> t >> p;
        memset(weapon, 0, sizeof(weapon)), memset(req, 0, sizeof(req));
        for (int i = 0; i < p.length(); i++)
            weapon[p[i] - 'a']++;
        if (s.length() > t.length())
        {
            puts("NO");
            continue;
        }
        else
        {
            int curS = 0, curT = 0;
            while (curT < t.length() && curS < s.length())
                if (s[curS] == t[curT])
                    curT++, curS++;
                else
                    curT++;
            if (curS < s.length() && curT >= t.length())
            {
                puts("NO");
                continue;
            }

            bool flag = true;
            for (int i = 0; i < s.length(); i++)
                req[s[i] - 'a']++;
            for (int i = 0; i < t.length(); i++)
                req[t[i] - 'a']--;
            for (int i = 0; i < 26; i++)
                if (req[i] + weapon[i] < 0)
                {
                    puts("NO"), flag = false;
                    break;
                }
            if (flag)
                puts("YES");
        }
    }
    return 0;
}