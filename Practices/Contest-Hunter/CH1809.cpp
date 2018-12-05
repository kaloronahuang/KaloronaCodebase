// CH1809.cpp
#include <cstdio>
#include <iostream>
using namespace std;
const int maxn = 200200;
int N, M, Q, nxt[maxn], f[maxn], counter[maxn];
string A, B;
int main()
{
    scanf("%d%d%d", &N, &M, &Q);
    cin >> A, cin >> B;
    A = " " + A, B = " " + B;
    // get the nxt of b;
    for (int i = 2, k = 0; i <= M; i++)
    {
        while (k > 0 && B[i] != B[k + 1])
            k = nxt[k];
        if (B[i] == B[k + 1])
            k++;
        nxt[i] = k;
    }
    for (int i = 1, k = 0; i <= N; i++)
    {
        while (k > 0 && (k == M || A[i] != B[k + 1]))
            k = nxt[k];
        if (A[i] == B[k + 1])
            k++;
        f[i] = k;
    }
    for (int i = 1; i <= N; i++)
        counter[f[i]]++;
    for (int i = N; i; i--)
        counter[nxt[i]] += counter[i];
    for (int i = 0, num; i < Q; i++)
        scanf("%d", &num), printf("%d\n", counter[num] - counter[num + 1]);
    return 0;
}