// F.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 200;

int n, ans[MAX_N];
bool tag[MAX_N];

int main()
{
    scanf("%d", &n);
    int ptr = n;
    for (int i = (n >> 1); i >= 1; i--)
        for (int j = (i << 1); j <= n; j += i)
            if (!tag[j])
            {
                tag[j] = true, ans[ptr--] = i;
                if (ptr == 1)
                    break;
            }
    for (int i = 2; i <= n; i++)
        printf("%d ", ans[i]);
    puts("");
    return 0;
}