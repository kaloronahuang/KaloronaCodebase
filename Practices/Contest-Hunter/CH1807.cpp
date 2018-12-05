// CH1807.cpp
#include <iostream>
#include <cstdio>
using namespace std;
string str1, str2;
string getMinStr(string str)
{
    string seq = str + str;
    int i = 0, j = 1, siz = seq.length(), presiz = str.length(), k = 0;
    while (i < presiz && j < presiz)
    {
        for (k = 0; seq[i + k] == seq[j + k] && k<presiz; k++)
            ;
        if (k == presiz)
            break;
        if (seq[i + k] < seq[j + k])
        {
            j = j + k + 1;
            if (i == j)
                j++;
        }
        else
        {
            i = i + k + 1;
            if (i == j)
                i++;
        }
    }
    int ans = min(i, j);
    return seq.substr(ans, presiz);
}
int main()
{
    cin >> str1, cin >> str2;
    string st1 = getMinStr(str1), st2 = getMinStr(str2);
    if (st1 == st2)
        printf("Yes\n"), cout << st1;
    else
        printf("No");
    return 0;
}