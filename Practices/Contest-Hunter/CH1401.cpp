// CH1401.cpp
#include <iostream>
#define ull unsigned long long
using namespace std;
const int maxn = 1000200;
string DNAseq;
ull hs[maxn], bitNum = 133, pows[maxn];

int main()
{
    cin >> DNAseq;
    pows[0] = 1;
    for (int i = 1; i <= DNAseq.length(); i++)
        hs[i] = hs[i - 1] * bitNum + (DNAseq[i - 1] - 'a' + 1), pows[i] = pows[i - 1] * bitNum;
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int l1, l2, r1, r2;
        scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
        ull hash1 = hs[r1] - hs[l1 - 1] * pows[r1 - l1 + 1];
        ull hash2 = hs[r2] - hs[l2 - 1] * pows[r2 - l2 + 1];
        if (hash1 == hash2)
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}