// CF2B.cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#define ll long long
using namespace std;
const int MX_N = 1010;
ll mat[MX_N][MX_N], dp2[MX_N][MX_N], dp5[MX_N][MX_N], pow2[25], pow5[25], n, zeroFlag, zeroX, zeroY;
char ans[MX_N << 1];
struct vec
{
    ll x, y;
} f2[MX_N][MX_N], f5[MX_N][MX_N];
void preprocess()
{
    for (int i = 0; i < 25; i++)
        pow2[i] = 1 << i;
    pow5[0] = 1;
    for (int i = 1; i < 25; i++)
        pow5[i] = pow5[i - 1] * 5;
}
void processDp()
{
    // start to program dynamically;
    for (int i = 2; i <= n; i++)
        dp2[0][i] = dp2[i][0] = dp5[0][i] = dp5[i][0] = 2e9;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            ll vald = dp2[i - 1][j], valr = dp2[i][j - 1];
            dp2[i][j] += min(vald, valr);
            if (vald < valr)
                f2[i][j] = vec{i - 1, j};
            else
                f2[i][j] = vec{i, j - 1};
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            ll vald = dp5[i - 1][j], valr = dp5[i][j - 1];
            dp5[i][j] += min(vald, valr);
            if (vald < valr)
                f5[i][j] = vec{i - 1, j};
            else
                f5[i][j] = vec{i, j - 1};
        }
}
int main()
{
    scanf("%lld", &n);
    preprocess();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            scanf("%lld", &mat[i][j]);
            if (mat[i][j] == 0)
            {
                zeroFlag = true, zeroX = i, zeroY = j;
                continue;
            }
            int tmp = mat[i][j];
            for (int k = 24; k >= 0; k--)
                if (tmp % pow2[k] == 0)
                    dp2[i][j] += k, tmp /= pow2[k];
            if (tmp % 2 == 0)
                dp2[i][j]++;
            tmp = mat[i][j];
            for (int k = 24; k >= 0; k--)
                if (tmp % pow5[k] == 0)
                    dp5[i][j] += k, tmp /= pow5[k];
            if (tmp % 5 == 0)
                dp2[i][j]++;
        }
    processDp();
    // process the answer;
    if (zeroFlag && min(dp2[n][n], dp5[n][n]) > 1)
    {
        puts("1");
        for (int i = 2; i <= zeroX; i++)
            putchar('D');
        for (int j = 2; j <= zeroY; j++)
            putchar('R');
        for (int i = zeroX + 1; i <= n; i++)
            putchar('D');
        for (int j = zeroY + 1; j <= n; j++)
            putchar('R');
        return 0;
    }
    // secondary answer;
    printf("%d\n", min(dp2[n][n], dp5[n][n]));
    int cx = n, cy = n, tot = 0;
    for (int counter = 1; counter <= 2 * n - 1; counter++)
    {
        int fx = f2[cx][cy].x, fy = f2[cx][cy].y;
        if (dp2[n][n] > dp5[n][n])
            fx = f5[cx][cy].x, fy = f5[cx][cy].y;
        if (cx > fx)
            ans[counter] = 'D';
        else
            ans[counter] = 'R';
        cx = fx, cy = fy;
    }
    for (int i = 2 * n - 2; i >= 1; i--)
        printf("%c", ans[i]);
    return 0;
}