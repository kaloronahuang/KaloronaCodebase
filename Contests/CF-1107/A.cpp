// A.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 330;
int T, n;
char str[MAX_N];
bool comp(string a, string b)
{
    if (a.length() > b.length())
        return true;
    else if (a.length() < b.length())
        return false;
    for (int i = 0; i < a.length(); i++)
        if (a[i] > b[i])
            return true;
        else if (a[i] < b[i])
            return false;
    return false;
}
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n), scanf("%s", str);
        bool flag = false;
        string pre = str;
        for (int i = 0; i < pre.length() - 1; i++)
        {
            string a = pre.substr(0, i + 1);
            string b = pre.substr(i + 1);
            if (comp(b, a))
            {
                cout << "YES" << endl;
                cout << 2 << endl;
                cout << a << " " << b << endl;
                flag = true;
                break;
            }
        }
        if (!flag)
            cout << "NO" << endl;
        /*
        vector<string> segs;
        string curt = "", last = "";
        for (int i = 0; i < n; i++)
        {
            curt = curt + str[i];
            if (comp(curt, last))
                last = curt, segs.push_back(curt), curt = "";
        }
        if (segs.size() < 2)
            printf("NO\n");
        else
        {
            printf("YES\n%d\n", segs.size());
            int siz = segs.size();
            for (int i = 0; i < siz; i++)
                printf("%s ", segs[i].c_str());
            puts("");
        }
        */
    }
    return 0;
}