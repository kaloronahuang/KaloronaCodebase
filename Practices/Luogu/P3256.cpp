// P3256.cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#define ll long long
using namespace std;
const ll MX_N = 10200;
struct car
{
    ll pos, velocity, id;
    bool operator<(const car &cr) const
    {
        if (cr.pos == pos)
            return velocity < cr.velocity;
        return pos > cr.pos;
    }
} crs[MX_N];
ll n, st[MX_N << 1], head = 1;
bool llersect(ll a, ll b, ll c)
{
    return (crs[a].pos - crs[c].pos) * (crs[b].velocity - crs[a].velocity) >=
           (crs[c].velocity - crs[a].velocity) * (crs[a].pos - crs[b].pos);
}
int main()
{
    scanf("%lld", &n);
    for (ll i = 1; i <= n; i++)
        scanf("%lld", &crs[i].pos), crs[i].id = i;
    for (ll i = 1; i <= n; i++)
        scanf("%lld", &crs[i].velocity);
    sort(crs + 1, crs + 1 + n);
    st[head] = 1;
    vector<ll> vec;
    for (ll i = 2; i <= n; i++)
        if (crs[i].velocity > crs[st[head]].velocity)
        {
            while (head > 1 && !llersect(st[head - 1], st[head], i))
                head--;
            st[++head] = i;
        }
        else if (crs[i].velocity == crs[st[head]].velocity && crs[i].pos == crs[st[head]].pos)
            vec.push_back(crs[i].id);
    while (head)
        vec.push_back(crs[st[head--]].id);
    sort(vec.begin(), vec.end());
    ll siz = vec.size();
    printf("%lld\n", siz);
    for (ll i = 0; i < siz; i++)
        printf("%lld ", vec[i]);
    return 0;
}