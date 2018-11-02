#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

string brain[10086];
int range = 0;

string rev(string a)
{
    string ret;
    for (int i = a.length() - 1; i > -1; ret += a[i--])
        ;
    return ret;
}

string add_hp(string a, string b)
{
    string an, bn;
    string ret;
    an = rev(a); // shorter;
    bn = rev(b);
    if (an.length() > bn.length())
        swap(an, bn);
    int morebit = 0;
    for (int i = 0; i < bn.length(); i++)
    {
        int res = bn[i] - '0' + morebit;
        if (i < an.length())
            res += an[i] - '0';
        morebit = (int)(res / 10);
        ret += (res % 10 + '0');
    }
    if (morebit != 0)
        ret += morebit + '0';
    return rev(ret);
}

void precalculate()
{
    int limit = 300;
    for (int i = 3; i < limit; i++)
    {
        brain[i - 1] = add_hp(add_hp(brain[i - 3], brain[i - 3]), brain[i - 2]);
    }
    range = limit;
}

string search(int limit)
{
    if (limit == 1)
        return "1";
    if (limit == 2)
        return "3";
    if (limit < range)
    {
        brain[limit - 1] = add_hp(add_hp(brain[limit - 3], brain[limit - 3]), brain[limit - 2]);
        range++;
    }
    else
    {
        range = limit;
        brain[limit - 1] = add_hp(search(limit - 2), add_hp(search(limit - 3), search(limit - 3)));
    }
    return brain[limit - 1];
}

int main()
{
    brain[0] = "1";
    brain[1] = "3";
    range = 2;
    precalculate();
    int num;

    while (cin >> num)
    {
        if (num == 0)
            cout << "1"<<endl;
        else
            cout << search(num) << endl;
    }
    /*
    for (int i = 0; i <= 250; i++)
        cout << search(i) << endl;
        */
    return 0;
}