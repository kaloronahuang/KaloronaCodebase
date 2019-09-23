// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_C = 30, MAX_N = 1010;

int T, ch[MAX_C];
string str1, str2;

int main()
{
    scanf("%d\n", &T);
    while (T--)
    {
        memset(ch, 0, sizeof(ch));
        getline(cin, str1, '\n');
        getline(cin, str2, '\n');
        int charNum1 = 0, charNum2 = 0;
        if (str1.length() != str2.length())
        {
            puts("0");
            continue;
        }
        swap(str1, str2);
        for (int i = 0; i < str1.length(); i++)
            if ('a' <= str1[i] && str1[i] <= 'z')
                charNum1++;
        for (int i = 0; i < str2.length(); i++)
            if ('a' <= str2[i] && str2[i] <= 'z')
                charNum2++;
        if (charNum1 != charNum2)
            puts("0");
        else
        {
            bool flag = true;
            for (int i = 0; i < str1.length(); i++)
                if (!('a' <= str1[i] && str1[i] <= 'z') && str1[i] != str2[i])
                {
                    flag = false, puts("0");
                    break;
                }
            if (flag == false)
                continue;
            for (int i = 0, j = 0; i < str1.length(); i++)
                if ('a' <= str1[i] && str1[i] <= 'z')
                {
                    while (!('a' <= str2[j] && str2[j] <= 'z') && j < str2.length())
                        j++;
                    if (ch[str2[j] - 'a' + 1] == 0)
                        ch[str2[j] - 'a' + 1] = str1[i] - 'a' + 1;
                    else if (ch[str2[j] - 'a' + 1] != str1[i] - 'a' + 1)
                    {
                        puts("0"), flag = false;
                        break;
                    }
                    j++;
                }
            if (flag)
                puts("1");
        }
    }
    return 0;
}