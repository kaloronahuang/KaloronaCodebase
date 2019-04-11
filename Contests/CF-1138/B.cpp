// B.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 50500;
int n;
char strA[MAX_N], strB[MAX_N];
int main()
{
    scanf("%d", &n);
    scanf("%s", strA + 1), scanf("%s", strB + 1);
    int uglyOnly = 0, both = 0, artOnly = 0, none = 0;
    for (int i = 1; i <= n; i++)
        if ((strA[i] - '0') && (strB[i] - '0'))
            both++;
        else if (strA[i] - '0')
            uglyOnly++;
        else if (strB[i] - '0')
            artOnly++;
        else
            none++;
    for (int a = 0; a <= uglyOnly; a++)
        for (int c = 0; c <= both; c++)
        {
            if (a + c > n / 2)
                continue;
            int b = artOnly + both - 2 * c - a;
            if (b > artOnly || b < 0)
                continue;
            int d = n / 2 - a - b - c;
            if (d < 0 || d > none)
                continue;
            for (int i = 1; i <= n; i++)
                if ((strA[i] - '0') && (strB[i] - '0') && c)
                    printf("%d ", i), c--;
                else if ((strA[i] - '0') && !(strB[i] - '0') && a)
                    printf("%d ", i), a--;
                else if ((strB[i] - '0') && !(strA[i] - '0') && b)
                    printf("%d ", i), b--;
                else if (!(strB[i] - '0') && !(strA[i] - '0') && d)
                    printf("%d ", i), d--;
            return 0;
        }
    printf("-1");
    return 0;
}