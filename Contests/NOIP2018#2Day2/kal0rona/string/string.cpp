// string.cpp
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

const int mod = 1000000007;
const int maxn = 2020;
#define ll long long
int a, b, c, d;
ll ans = 0;
string seqT;

bool isValid(string son, string fat)
{
    int ssize = son.length();
    int cur = 0;
    int siz = fat.length();
    for (int i = 0; i < siz; i++)
    {
        bool flag = true;
        while (cur < ssize)
        {
            if (son[cur++] == fat[i])
            {
                flag = false;
                break;
            }
        }
        if (flag)
            return false;
    }
    return true;
}

int main()
{
    freopen("string.in", "r", stdin);
    freopen("string.out", "w", stdout);
    cin >> a >> b >> c >> d;
    for (int i = 1; i <= c; i++)
        seqT += "0";
    for (int i = c + 1; i - c <= d; i++)
        seqT += "1";
    //bool res = isValid("01100010", "01001");
    do
    {
        string sub;
        for (int i = 1; i <= a; i++)
            sub += "0";
        for (int i = a + 1; i - a <= b; i++)
            sub += "1";
        do
        {
            if (isValid(sub, seqT))
                ans++, ans %= mod;
        } while (next_permutation(sub.begin(), sub.end()));
    } while (next_permutation(seqT.begin(), seqT.end()));
    cout << ans;
    return 0;
}