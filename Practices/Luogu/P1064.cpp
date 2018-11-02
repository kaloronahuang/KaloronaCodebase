// P1064.cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

struct Pics
{
    int price, impts;

    Pics()
    {
        price = 0;
        impts = 0;
    }
    Pics(int p, int i) : price(p), impts(i){};
};

struct Term
{
    int price, impts, pics_num;
    Pics affiliates[10];

    Term()
    {
        price = 0;
        impts = 0;
        pics_num = 0;
    }
    Term(int p, int i) : price(p), impts(i) { pics_num = 0; };
    bool operator<(const Term &t) const
    {
        return price > t.price;
    }
};

Term ts[70];
int DPTable[70][200010];
bool vis[70];
int n, m;

void Init()
{
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int price, impts, aff;
        cin >> price >> impts >> aff;
        if (aff == 0)
            ts[i] = Term(price, impts);
        else
            ts[aff].affiliates[ts[aff].pics_num++] = Pics(price, impts);
    }
    memset(DPTable, 0, sizeof(DPTable));
}

int getQuality(int i)
{
    return ts[i].price * ts[i].impts;
}

int getQuality(int i, int j)
{
    return ts[i].affiliates[j].price * ts[i].affiliates[j].impts;
}

int getPrice(int i)
{
    return ts[i].price;
}

int getPrice(int i, int j)
{
    return ts[i].affiliates[j].price;
}

int DP()
{
    for (int i = 1; i <= m; i++)
        for (int j = 0; j <= n; j++)
        {
            DPTable[i][j] = DPTable[i - 1][j];
            if (j >= ts[i].price)
            {
                int ans = max(DPTable[i][j], DPTable[i - 1][j - getPrice(i)] + getQuality(i));
                if (ts[i].pics_num >= 1 && j >= getPrice(i) + getPrice(i, 0))
                    ans = max(ans,
                              DPTable[i - 1][j - getPrice(i) - getPrice(i, 0)] + getQuality(i) + getQuality(i, 0));
                if (ts[i].pics_num >= 2 && j >= getPrice(i) + getPrice(i, 1))
                    ans = max(ans,
                              DPTable[i - 1][j - getPrice(i) - getPrice(i, 1)] + getQuality(i) + getQuality(i, 1));
                if (ts[i].pics_num >= 2 && j >= getPrice(i) + getPrice(i, 1) + getPrice(i, 0))
                    ans = max(ans,
                              DPTable[i - 1][j - getPrice(i) - getPrice(i, 0) - getPrice(i, 1)] + getQuality(i) + getQuality(i, 0) + getQuality(i, 1));
                DPTable[i][j] = ans;
            }
        }
    return DPTable[m][n];
}

int main()
{
    Init();
    sort(ts + 1, ts + m + 1);
    cout << DP();
    return 0;
}