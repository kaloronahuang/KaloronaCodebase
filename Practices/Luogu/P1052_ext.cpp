#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 10005;
int L, S, T, m, ans = MAXN;
int arr[MAXN], differ[MAXN], dp[MAXN];
bool flag[MAXN];
bool CMP(int a, int b)
{
    return a < b;
}
int read()
{
    int x = 0, f = 1;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            f = -1;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = (x << 3) + (x << 1) + c - '0';
    return x * f;
}
int main()
{
    //freopen("testdata.in","r",stdin);
    //freopen("ac.out","w",stdout);
    L = read();
    S = read();
    T = read();
    m = read();
    for (int i = 1; i <= m; ++i)
        arr[i] = read();
    sort(arr + 1, arr + m + 1, CMP);
    //for(int i=1;i<=m;++i) cout<<arr[i]<<" ";cout<<endl;
    arr[++m] = L;
    for (int i = 1; i <= m; ++i)
    {
        differ[i] = (arr[i] - arr[i - 1]) % T + T;
        if (arr[i - 1] + differ[i] > arr[i])
            differ[i] -= T;
    }
    for (int i = 1; i <= m; ++i)
    {
        flag[arr[i] = arr[i - 1] + differ[i]] = true;
        //cout<<arr[i]<<" ";
    }
    //cout<<endl;
    L = arr[m];
    if (arr[m] > arr[m - 1])
        flag[arr[m]] = false;
    for (int i = 1; i <= L; ++i)
        dp[i] = MAXN;
    for (int i = 0; i <= L; ++i)
    {
        for (int j = S; j <= T; ++j)
        {
            if (i + j <= L)
                dp[i + j] = min(dp[i + j], dp[i] + flag[i + j]);
            else
                dp[L] = min(dp[L], dp[i]);
        }
    }
    printf("%d", dp[L]);
    return 0;
}