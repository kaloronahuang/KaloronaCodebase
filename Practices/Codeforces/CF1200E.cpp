// CF1200E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

string tmp;
int n, nxt[MAX_N * 10];

void get_nxt(string curt)
{
    int len = curt.length();
    nxt[0] = 0;
    for (int i = 1; i < len; i++)
    {
        int j = nxt[i - 1];
        while (j > 0 && curt[i] != curt[j])
            j = nxt[j - 1];
        if (curt[j] == curt[i])
            j++;
        nxt[i] = j;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        string str;
        cin >> str;
        get_nxt(str);
        int len_tmp = tmp.length(), len_str = str.length();
        int pos = 0;
        for (int j = max(0, len_tmp - len_str); j < len_tmp; j++)
        {
            while (pos > 0 && str[pos] != tmp[j])
                pos = nxt[pos - 1];
            if (str[pos] == tmp[j])
                pos++;
        }
        if (pos < len_str)
            for (int i = pos; i < len_str; i++)
                tmp += str[i];
    }
    cout << tmp;
    return 0;
}