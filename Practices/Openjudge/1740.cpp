// High precision adding;
#include <iostream>
#include <algorithm>

using namespace std;

string rev(string a)
{
    string ret;
    for (int i = a.length() - 1; i > -1; i--)
        ret += a[i];
    return ret;
}

string add_hp(string az, string as, string bz, string bs)
{
    // spart;
    int morebit = 0;
    string a = as;
    string b = bs;
    if (a.length() < b.length())
        swap(a, b);
    string rets;
    for (int i = a.length() - 1; i > -1; i--)
    {
        int res = a[i] - '0' + morebit;
        if (i < b.length())
            res += b[i] - '0';
        int sec = (int)res / 10;
        int fir = res % 10;
        morebit = sec;
        rets += fir + '0';
    }
    rets = rev(rets);
    // zpart;
    a = rev(az);
    b = rev(bz);
    if (a.length() < b.length())
        swap(a, b);
    string retz;
    for (int i = 0; i < a.length(); i++)
    {
        int res = a[i] - '0' + morebit;
        if (i < b.length())
            res += b[i] - '0';
        int fir = 0;
        morebit = (int)(res / 10);
        fir = res % 10;
        retz += fir + '0';
    }
    if (morebit != 0)
        retz += morebit + '0';
    retz = rev(retz);
    if (rets != "")
        retz += ".";
    return retz + rets;
}

string reg(string a)
{
    int pos = a.find('.');
    string pre, aft;
    int limitone = a.length();
    if (pos != -1)
    {
        limitone = pos;
    }
    bool toDel = true;
    for (int i = 0; i < limitone; i++)
    {
        if (a[i] != '0')
            toDel = false;
        if (!toDel)
            pre += a[i];
    }
    if (pos != -1)
    {
        bool toDel_ = true;
        for (int i = a.length() - 1; i > pos; i--)
        {
            if (a[i] != '0')
                toDel_ = false;
            if (!toDel_)
            {
                aft += a[i];
            }
        }
        aft = rev(aft);
    }
    if (pre == "")
        return "0." + aft;
    if (aft == "")
        return pre;
    return pre + "." + aft;
}

int main()
{
    string az, as, bz, bs;
    as = "";
    bs = "";
    string astr, bstr;
    cin >> astr >> bstr;
    if (astr.find('.') != -1)
    {
        az = astr.substr(0, astr.find('.'));
        as = astr.substr(astr.find(".") + 1, astr.length() - astr.find(".") - 1);
    }
    else
        az = astr;
    if (bstr.find('.') != -1)
    {
        bz = bstr.substr(0, bstr.find('.'));
        bs = bstr.substr(bstr.find(".") + 1, bstr.length() - bstr.find(".") - 1);
    }
    else
        bz = bstr;
    cout << reg(add_hp(az, as, bz, bs));
    return 0;
}