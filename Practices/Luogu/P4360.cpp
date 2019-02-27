// P4360.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 20200;
int n, wi[MAX_N], di[MAX_N], sumDist[MAX_N], sumAll[MAX_N], sumWeight[MAX_N], q[MAX_N << 1], head, tail, dp[MAX_N];
double slope(int j1, int j2)
{
    return (sumWeight[j2] * sumDist[j2] - sumWeight[j1] * sumDist[j1]) / (sumWeight[j2] - sumWeight[j1]);
}
int calc(int i, int j)
{
    return sumAll[i] - sumAll[j + 1] - sumDist[j] * (sumWeight[j] - sumWeight[i - 1]);
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &wi[i], &di[i]), sumWeight[i] = sumWeight[i - 1] + wi[i];
    for (int i = n; i >= 1; i--)
        sumDist[i] = sumDist[i + 1] + di[i], sumAll[i] = sumDist[i] * wi[i] + sumAll[i + 1];

    // calc(i, j) = sumAll(i)-sumAll(j+1)-sumDist[j]*(sumWeight[j]-sumWeight[i-1]);
    // so:
    // f[i] = calc(1,j)+calc(j+1, i)+calc(i+1,n+1);
    // f[i] = sumAll(1)-sumDist(i)*sumWeight(i)+sumWeight(j)*(sumDist(i)-sumDist(j))
    // given j1 < j2, get the exp of f[j1] < f[j2]:
    // sumWeight(j1)*(sumDist(i)-sumDist[j1]) < sumWeight(j2)*(sumDist(i)-sumDist[j2])
    // sumDist(i)*(sumWeight(j1)-sumWeight(j2)) < sumWeight(j1)*sumDist(j1) - sumWeight(j2)*sumDist(j2);
    // (sumWeight(j1)*sumDist(j1) - sumWeight(j2)*sumDist(j2))/(sumWeight(j1)-sumWeight(j2)) > sumDist(i)
    head = 1, tail = 0;
    int ans = 0x3f3f3f3f;
    for (int i = 1; i <= n; i++)
    {
        while (head < tail && slope(q[head], q[head + 1]) > sumDist[i])
            head++;
        dp[i] = calc(1, q[head]) + calc(q[head] + 1, i) + calc(i + 1, n + 1);
        while (head < tail && slope(q[tail - 1], q[tail]) < slope(q[tail], i))
            tail--;
        q[++tail] = i;
        ans = min(ans, dp[i]);
    }
    printf("%d", ans);
    return 0;
}