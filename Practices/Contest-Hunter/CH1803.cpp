// CH1803.cpp
#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
using namespace std;
const int maxn = 1010;
int n, m, h[maxn], l[maxn], r[maxn], ans;
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            char ch;
            while (ch = getchar())
                if (ch == 'F' || ch == 'R')
                    break;
            if (ch == 'F')
                h[j]++;
            else
                h[j] = 0;
        }
        memset(l, 0, sizeof(l));
        memset(r, 0, sizeof(r));
        stack<int> st;
        for (int i = 1; i <= m; i++)
        {
            while (!st.empty() && h[i] <= h[st.top()])
                st.pop();
            if (!st.empty())
                l[i] = st.top();
            else
                l[i] = 0;
            st.push(i);
        }
        while (!st.empty())
            st.pop();
        for (int i = m; i >= 1; i--)
        {
            while (!st.empty() && h[i] <= h[st.top()])
                st.pop();
            if (!st.empty())
                r[i] = st.top();
            else
                r[i] = m + 1;
            st.push(i);
        }
        for (int i = 1; i <= m; i++)
            ans = max(ans, (h[i] * ((r[i] - 1) - (l[i] + 1) + 1)));
    }
    printf("%d\n", 3 * ans);
    return 0;
}