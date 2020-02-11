// CF1299A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, seq[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]);
    for (int b = 30; b >= 0; b--)
    {
        int pos = -1;
        for (int i = 1; i <= n; i++)
            if (seq[i] & (1 << b) && pos == -1)
                pos = i;
            else if (seq[i] & (1 << b))
                pos = 0;
        if (pos != -1 && pos != 0)
        {
            printf("%d ", seq[pos]);
            for (int i = 1; i <= n; i++)
                if (i != pos)
                    printf("%d ", seq[i]);
            return 0;
        }
    }
    for (int i = 1; i <= n; i++)
        printf("%d ", seq[i]);
    return 0;
}