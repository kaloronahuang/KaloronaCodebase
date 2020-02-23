// CF1280A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, mod = 1e9 + 7;

int T, n, x;
string str;

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        cin >> x >> str, n = str.length();
        int len = n;
        for (int i = 0; i < x; i++)
        {
            int bit = str[i] - '1';
            if (str.length() < x)
            {
                string tmp = str.substr(i + 1);
                for (int i = 0; i < bit && str.length() < x; i++)
                    str += tmp;
            }
            len = (0LL + len + 1LL * ((len + mod - i - 1) % mod) * bit % mod) % mod;
        }
        printf("%d\n", len);
    }
    return 0;
}