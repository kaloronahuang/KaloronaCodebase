// P3444.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2020;

typedef long long ll;

int n, m, limit, mat[MAX_N][MAX_N];
ll prefix[MAX_N][MAX_N];

ll getArea(int x1, int y1, int x2, int y2) { return prefix[x2][y2] - prefix[x1 - 1][y2] - prefix[x2][y1 - 1] + prefix[x1 - 1][y1 - 1]; }

int calcHorizontal(int upper)
{
    int l = 1, r = m, u = 1, d = n, cnt = 0;
    while (l <= r && u <= d)
    {
        cnt++;
        if (getArea(u, l, d, l) <= limit)
            l++;
        else if (getArea(u, r, d, r) <= limit)
            r--;
        else if (getArea(u, l, u, r) <= limit && u < upper)
            u++;
        else if (getArea(d, l, d, r) <= limit)
            d--;
        else
            return 1e9;
    }
    return cnt;
}

int calcVertical(int lbound)
{
    int l = 1, r = m, u = 1, d = n, cnt = 0;
    while (l <= r && u <= d)
    {
        cnt++;
        if (getArea(u, l, u, r) <= limit)
            u++;
        else if (getArea(d, l, d, r) <= limit)
            d--;
        else if (getArea(u, l, d, l) <= limit && l < lbound)
            l++;
        else if (getArea(u, r, d, r) <= limit)
            r--;
        else
            return 1e9;
    }
    return cnt;
}

int main()
{
    scanf("%d%d%d", &limit, &m, &n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &mat[i][j]), prefix[i][j] = mat[i][j] + prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1];
    int ans = n + m;
    for (int i = 1; i <= n; i++)
        ans = min(ans, calcHorizontal(i));
    for (int i = 1; i <= m; i++)
        ans = min(ans, calcVertical(i));
    printf("%d\n", ans);
    return 0;
}