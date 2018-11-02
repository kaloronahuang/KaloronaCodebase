#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>

using namespace std;

struct Term
{
    int price, impts;
    Term() {}
    Term(int v, int p) : price(v), impts(p) {}
    bool operator<(const Term &t) const
    {
        return price < t.price;
    }
};

const int maxn = 25;
int N, m;
Term ts[maxn];
int DPTable[maxn + 1][30010];

void DP()
{
    memset(DPTable, 0, sizeof(DPTable));
    for (int i = 1; i < m + 1; i++)
        for (int j = 0; j < N + 1; j++)
            if (j >= ts[i - 1].price)
                DPTable[i][j] = max(DPTable[i - 1][j], DPTable[i - 1][j - ts[i - 1].price] + ts[i - 1].price * ts[i - 1].impts);
            else
                DPTable[i][j] = DPTable[i - 1][j];
}

int main()
{
    cin >> N >> m;
    for (int i = 0; i < m; i++)
    {
        int v, p;
        cin >> v >> p;
        ts[i] = Term(v, p);
    }
    sort(ts, ts + m);
    DP();
    cout << DPTable[m][N];
    return 0;
}