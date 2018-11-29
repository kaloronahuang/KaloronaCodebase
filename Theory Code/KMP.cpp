// KMP.cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int maxn = 1000200;
int next[maxn];

void get_next(string str)
{
    int siz = str.length();
    next[0] = -1;
    for (int i = 1; i < siz; i++)
    {
        int j = next[i - 1];
        while (j >= 0 && str[i] != str[j + 1])
            j = next[j];
        if (str[j + 1] == str[i])
            next[i] = j + 1;
        else
            next[i] = -1;
    }
}

int main()
{
    string str1, str2;
    cin >> str1, cin >> str2;
    get_next(str2);
    int i = 0, j = 0;
    while (i < str1.length())
        if (str1[i] == str2[j])
        {
            i++, j++;
            if (j == str2.length())
                printf("%d\n", i - str2.length() + 1), j = next[j - 1] + 1;
        }
        else if (j == 0)
            i++;
        else
            j = next[j - 1] + 1;
    for (int i = 0; i < str2.length(); i++)
        printf("%d ", next[i] + 1);
    return 0;
}