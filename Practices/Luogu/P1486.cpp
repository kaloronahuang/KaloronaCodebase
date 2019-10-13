// P1486.cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;

struct node
{
    int salary, id;
    bool operator>(const node &nd) const { return salary == nd.salary ? id > nd.id : salary > nd.salary; }
};

tree<node, null_type, greater<node>, rb_tree_tag, tree_order_statistics_node_update> T, tre;
char str[10];

int main()
{
    int cases, m, k, bias = 0, q, ans = 0;
    scanf("%d%d", &cases, &m);
    while (cases--)
    {
        scanf("%s%d", str, &k);
        if (str[0] == 'I')
        {
            k += bias;
            if (k >= m)
                T.insert(node{k, cases});
        }
        else if (str[0] == 'A')
            m -= k, bias -= k;
        else if (str[0] == 'S')
        {
            m += k, bias += k;
            T.split(node{m, -1}, tre);
            ans += tre.size();
        }
        else
            printf(k > T.size() ? "-1\n" : "%d\n", T.find_by_order(k - 1)->salary - bias);
    }
    printf("%d", ans);
    return 0;
}