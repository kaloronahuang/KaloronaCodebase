// POJ3349.cpp
#include <cstdio>
#include <iostream>
#define ll long long
const int maxn = 100200;
const int P = 10000007;
ll n, arr[maxn][6];
struct node
{
    ll hash, idx;
    node *next;
};
node *nodes[P + 10000];
using namespace std;

bool equal(ll idx1, ll idx2)
{
    int rev[6];
    for (int i = 0; i < 6; i++)
        rev[i] = arr[idx1][5 - i];
    for (int bias = 0; bias < 6; bias++)
    {
        int rear = arr[idx2][5];
        for (int i = 5; i > 0; i--)
            arr[idx2][i] = arr[idx2][i - 1];
        arr[idx2][0] = rear;
        bool revflag = true, stflag = true;
        for (int i = 0; i < 6; i++)
        {
            if (arr[idx2][i] != rev[i])
                revflag = false;
            if (arr[idx2][i] != arr[idx1][i])
                stflag = false;
            if (!revflag && !stflag)
                break;
        }
        if (revflag || stflag)
            return true;
    }
    return false;
}

ll genHash(int idx)
{
    ll sum = 0, mul = 1;
    for (int i = 0; i < 6; i++)
        sum += arr[idx][i] % P, mul *= arr[idx][i] % P, sum %= P, mul %= P;
    return (sum + mul) % P;
}

bool insert(int idx)
{
    ll hs = genHash(idx);
    for (node *i = nodes[hs]; i != NULL; i = i->next)
        if (equal(i->idx, idx))
            return true;
    node *curt = new node();
    curt->hash = hs;
    curt->idx = idx;
    curt->next = nodes[hs];
    nodes[hs] = curt;
    return false;
}

int main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < 6; j++)
            scanf("%lld", &arr[i][j]);
        if (insert(i))
        {
            puts("Twin snowflakes found.");
            return 0;
        }
    }
    printf("No two snowflakes are alike.");
    return 0;
}