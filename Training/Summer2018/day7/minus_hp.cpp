// high precision;
#include <iostream>
#include <algorithm>

using namespace std;

string removeZero(string str)
{
    bool toRemove = true;
    string tmp = "";
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] != '0')
        {
            toRemove = false;
        }
        if (!toRemove)
        {
            tmp += str[i];
        }
    }
    return tmp;
}

string rev(string str)
{
    string ret = "";
    for (int i = 0; i < str.length(); i++)
    {
        ret += str[str.length() - 1 - i];
    }
    return ret;
}

string minus_hp(string a, string b)
{
    string reva = rev(a);
    string revb = rev(b);
    string ret;
    for (int i = 0; i < a.length(); i++)
    {
        if (reva[i] < revb[i])
        {
            for (int j = i + 1; i < a.length(); j++)
            {
                if (reva[j] != '0')
                {
                    reva[j]--;
                    ret += (reva[i] + 10 - revb[i] + '0');
                    break;
                }
                else
                {
                    reva[j] = '9';
                }
            }
        }
        else
        {
            ret += reva[i] - revb[i] + '0';
        }
    }
    return rev(ret);
} // a>b;

int main()
{
    string a, b;
    getline(cin, a);
    getline(cin, b);
    bool isSigned = false;
    if (a < b)
    {
        isSigned = true;
        swap(a, b);
    }
    string res = minus_hp(a, b);
    if (isSigned)
        cout << "-";
    cout << removeZero(res);
    return 0;
}