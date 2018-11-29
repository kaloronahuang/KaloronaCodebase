// POJ1961.cpp
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1000000 + 1000;
int next[maxn];
string str;

int main()
{
    int siz = 0, cnt = 1;
    while (scanf("%d", &siz) && siz != 0)
    {
        cin >> str;
        // get the next array;
        next[0] = -1;
        for (int i = 1; i < siz; i++)
        {
            int j = next[i - 1];
            while (j >= 0 && str[i] != str[j + 1])
                j = next[j];
            if (str[i] == str[j + 1])
                next[i] = j + 1;
            else
                next[i] = -1;
        }
        for (int i = 0; i < siz; i++)
            ++next[i];
        // we have got it...;
        printf("Test case #%d\n", cnt++);
        for (int i = 1; i < siz; i++)
            if ((i + 1) % (i - next[i] + 1) == 0 && (i + 1) / (i - next[i] + 1) > 1)
                printf("%d %d\n", i + 1, (i + 1) / (i - next[i] + 1));
        puts("");
    }
    return 0;
}