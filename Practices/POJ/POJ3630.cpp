// POJ3630.cpp
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int trie[10][200000], curt = 2, weight[400000], siz;
char current[200000][20];
void insert(char *str)
{
    int p = 1;
    for (int i = 0; i < strlen(str); i++)
    {
        if (trie[str[i] - '0'][p] == 0)
            trie[str[i] - '0'][p] = curt++;
        p = trie[str[i] - '0'][p];
        if (i == strlen(str) - 1)
            weight[p]++;
    }
}
bool check(char *str)
{
    int p = 1;
    for (int i = 0; i < strlen(str); i++)
        if (weight[p])
            return false;
        else if (trie[str[i] - '0'][p] == 0)
            return true;
        else
            p = trie[str[i] - '0'][p];
    return true;
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        memset(trie, 0, sizeof(trie)), curt = 2;
        memset(weight, 0, sizeof(weight));
        scanf("%d", &siz);
        for (int i = 0; i < siz; i++)
            scanf("%s", current[i]);
        bool res = true;
        for (int i = 0; i < siz; i++)
            insert(current[i]);
        for (int i = 0; i < siz; i++)
            if (!(res = check(current[i])))
                break;
        printf((res) ? "YES\n" : "NO\n");
    }
    return 0;
}