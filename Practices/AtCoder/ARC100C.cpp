// ARC100C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = (1 << 18) + 200;

int n, ai[MAX_N], bit, ans[MAX_N], max_val[MAX_N][2];

int main()
{
    scanf("%d", &bit), n = 1 << bit;
    for (int i = 0; i < n; i++)
        scanf("%d", &ai[i]), max_val[i][0] = i, max_val[i][1] = n;
    for (int i = 0; i < n; i++)
    {
        for (int b = bit - 1; b >= 0; b--)
            if (!(i & (1 << b)))
            {
                int dst = i | (1 << b);
                if (ai[max_val[i][0]] > ai[max_val[dst][0]])
                    swap(max_val[dst][0], max_val[dst][1]), max_val[dst][0] = max_val[i][0];
                else if (ai[max_val[i][0]] > ai[max_val[dst][1]] && max_val[i][0] != max_val[dst][0])
                    max_val[dst][1] = max_val[i][0];
                if (ai[max_val[i][1]] > ai[max_val[dst][0]])
                    swap(max_val[dst][0], max_val[dst][1]), max_val[dst][0] = max_val[i][1];
                else if (ai[max_val[i][1]] > ai[max_val[dst][1]] && max_val[i][1] != max_val[dst][0])
                    max_val[dst][1] = max_val[i][1];
            }
        if (i != 0)
            printf("%d\n", ans[i] = max(ans[i - 1], ai[max_val[i][0]] + ai[max_val[i][1]]));
    }
    return 0;
}