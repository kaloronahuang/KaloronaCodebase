// CF1290D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e4 + 200;

int n, k, ans, block_siz, block_tot;
char cmdlet[20];
bool tag[MAX_N];

bool query(int x)
{
    printf("? %d\n", x), fflush(stdout);
    return (scanf("%s", cmdlet + 1), cmdlet[1] == 'Y');
}

void reset() { printf("R\n"), fflush(stdout); }

void processBlock(int id)
{
    for (int ptr = id * block_siz + 1; ptr <= (id + 1) * block_siz; ptr++)
        if (!tag[ptr] && query(ptr))
            tag[ptr] = true, ans--;
}

int main()
{
    scanf("%d%d", &n, &k), ans = n;
    block_siz = max(k >> 1, 1), block_tot = n / block_siz;
    for (int id = 0; id <= (n / k) - 1; id++)
    {
        if (id > 0)
            reset();
        // zig-zag shape;
        int delta = 0;
        for (int j = 1; j <= block_tot; j++)
            processBlock((id + block_tot + delta) % block_tot), delta = (delta <= 0) - delta;
    }
    printf("! %d\n", ans), fflush(stdout);
    return 0;
}