#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;

string removeZero(string a)
{
    string ret = "";
    bool toremove = false;
    for (int i = 0; i < a.length(); i++)
    {
        if (a[i] != '0')
        {
            toremove = true;
        }
        if (toremove)
        {
            ret += a[i];
        }
    }
    if (ret == "")
        return "0";
    return ret;
}

string assign_str(int N)
{
    string tmp;
    for (int i = 0; i <= N; i++)
    {
        tmp += '0';
    }
    return tmp;
}

string rev(string a)
{
    string ret = "";
    for (int i = a.length() - 1; i > -1; i--)
        ret += a[i];
    return ret;
}

string retBigger(string a, string b)
{
    if(a==b)
        return a;
    if(a.length()>b.length())
        return a;
    else
        return b;
    for(int i = 0;i<a.length();i++)
    {
        if(a[i]>b[i])
            return a;
    }
}

string retSmaller(string a, string b)
{
    if(a==b)
        return a;
    if(a.length()<b.length())
        return a;
    else
        return b;
    for(int i = 0;i<a.length();i++)
    {
        if(a[i]<b[i])
            return a;
    }
}

string mul(string a, string b)
{
    string ret = "0";
    if(retBigger(a,b) == b)
        swap(a,b);
    string reva = rev(a);
    string revb = rev(b);
    //  a
    // *b
    //------
    vector<string> addingNum;
    for (int i = 0; i < revb.length(); i++)
    {
        string res = "0";
        int src = revb[i] - '0';
        for (int j = 0; j < reva.length(); j++)
        {
            int dst = reva[j] - '0';
            int resu = src * dst + res[j] - '0';
            int fir = resu % 10;
            res.resize(res.length() + 1);
            res[j] = fir + '0';
            res[j + 1] += (int)(resu / 10) + '0';
        }
        addingNum.push_back(removeZero(rev(res) + assign_str(i - 1)));
    }
    // add;
    string c = "0";
    for (int i = 0; i < addingNum.size(); i++)
    {
        string source = addingNum[i];
        source = rev(source);
        c = rev(c);
        int maxs = max(c.length(), source.length());
        string tmp = assign_str(maxs);
        int morebits = 0;
        for (int j = 0; j < maxs; j++)
        {
            int current_src;
            int current_c;

            // inp;
            if (j >= source.length())
                current_src = 0;
            else
                current_src = source[j] - '0';
            if (j >= c.length())
                current_c = 0;
            else
                current_c = c[j] - '0';

            int result = current_c + current_src + morebits;
            int fir = result % 10;
            int sec = (int)(result / 10);

            morebits = sec;
            tmp[j] = fir + '0';
        }
        c = removeZero(rev(tmp));
    }
    return c;
}

int main()
{
    string a, b;
    getline(cin, a);
    getline(cin, b);
    cout << retSmaller(mul(a, b),mul(b,a));
    return 0;
}