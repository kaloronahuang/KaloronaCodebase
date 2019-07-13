// A.cpp
#include <bits/stdc++.h>

using namespace std;

string rev, revk;
int T, k;

int main()
{
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    scanf("%d", &T);
    while (T--)
    {
        rev = "";
        cin >> k >> rev;
        stringstream ss;
        ss << k;
        revk = ss.str(), reverse(revk.begin(), revk.end());
        // starts to compare;
        if (revk.length() > rev.length())
        {
            puts("Yes");
            continue;
        }
        else if (revk.length() == rev.length())
        {
            bool flag = true;
            for (int i = revk.length() - 1; i >= 0; i--)
                if (revk[i] > rev[i])
                    break;
                else if (revk[i] < rev[i])
                {
                    flag = false;
                    break;
                }
            if (flag)
            {
                puts("Yes");
                continue;
            }
        }
        // general compare;
        int d = 0;
        for (int i = 0; i < rev.length(); i++)
            d = (d * 10 + rev[i] - '0') % (k + 1);
        if (d == 0)
            printf("No\n");
        else
            printf("Yes\n");
    }
    return 0;
}