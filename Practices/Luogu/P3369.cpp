// P3369.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std;
const int MAX_N = 100020;
int ch[MAX_N][2], key[MAX_N], val[MAX_N], siz[MAX_N], tot, root;
void update(int p) { siz[p] = siz[ch[p][0]] + siz[ch[p][1]] + 1; }
int generate(int value)
{
    siz[++tot] = 1;
    val[tot] = value, key[tot] = rand();
    return tot;
}
void split(int u, int &a, int &b, int value)
{
    if (!u)
        a = b = 0;
    else
    {
        if (val[u] <= value)
            a = u, split(ch[u][1], ch[u][1], b, value);
        else
            b = u, split(ch[u][0], a, ch[u][0], value);
        update(u);
    }
}
int merge(int x, int y)
{
    if (!x || !y)
        return x + y;
    update(x), update(y);
    if (key[x] < key[y])
    {
        ch[x][1] = merge(ch[x][1], y);
        update(x);
        return x;
    }
    else
    {
        ch[y][0] = merge(x, ch[y][0]);
        update(y);
        return y;
    }
}
void insert(int value)
{
    int a, b;
    split(root, a, b, value);
    root = merge(merge(a, generate(value)), b);
}
void remove(int value)
{
    int a, b, c;
    split(root, a, c, value), split(a, a, b, value - 1);
    b = merge()
}
int main()
{
    srand(time(NULL));
    return 0;
}