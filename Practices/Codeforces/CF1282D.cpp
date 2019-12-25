// CF1282D.cpp
#include <bits/stdc++.h>

using namespace std;

int GET(string str, int ret = 0)
{
    cout << str << endl, cin >> ret;
    if (ret == 0)
        exit(0);
    return ret;
}

int main()
{
    int A = GET(string(300, 'a')), n = 600 - (A + GET(string(300, 'b')));
    string str = string(n, 'a');
    int atot = 300 - A, btot = n - atot;
    for (int i = 0; i <= n - 2; i++)
    {
        str[i] = 'b';
        if (GET(str) > btot)
            str[i] = 'a';
        else
            btot--;
    }
    if (btot)
        str[n - 1] = 'b';
    GET(str);
    return 0;
}