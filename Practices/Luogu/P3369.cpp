// P3369.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std;
const int MAX_N = 100020;
int ch[MAX_N][2], key[MAX_N], val[MAX_N], siz[MAX_N], tot;
void update(int p) { siz[p] = siz[ch[p][0]] + siz[ch[p][1]] + 1; }
int generate(int value)
{
    siz[++tot] = 1;
    ch[tot][0] = ch[tot][1] = 0;
    val[tot] = value, key[tot] = rand();
    return tot;
}
int main()
{
    srand(time(NULL));
    return 0;
}