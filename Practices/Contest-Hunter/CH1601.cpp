// POJ1601.cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int maxn = 2000000;
struct tnode
{
    int cnt, next;
} trie[30][maxn];
bool end[maxn];
int current = 2;

void insert(string str)
{
    int pnode = 1;
    for (int i = 0; i < str.length(); i++)
    {
        int charval = str[i] - 'a';
        if (trie[charval][pnode].next == 0)
            trie[charval][pnode].next = current++;
        if (i == str.length() - 1)
            trie[charval][pnode].cnt++;
        pnode = trie[charval][pnode].next;
    }
}

int count(string str)
{
    int tot = 0, pnode = 1;
    for (int i = 0; i < str.length(); i++)
    {
        int ch = str[i] - 'a';
        if (pnode == 0)
            break;
        tot += trie[ch][pnode].cnt;
        pnode = trie[ch][pnode].next;
    }
    return tot;
}

int main()
{
    int n, m;
    scanf("%d %d\n", &n, &m);
    string tmp;
    for (int i = 0; i < n; i++)
        cin >> tmp, insert(tmp);
    for (int i = 0; i < m; i++)
        cin >> tmp, printf("%d\n", count(tmp));
    return 0;
}
