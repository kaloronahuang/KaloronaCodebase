#include <cstdio>
#include <algorithm>
using namespace std;
typedef struct n
{
    int num, ord;
} node;
node first_team[100010], second_team[100010];
int a[100010], b[100010], ans;
int compare(node x, node y)
{
    return x.num < y.num;
}
void Merge(int l, int r)
{
    if (l >= r)
        return;
    int mid = (l + r) / 2;
    Merge(l, mid);
    Merge(mid + 1, r);
    int i = l, j = mid + 1, k = l;
    while (i <= mid && j <= r)
    {
        if (a[i] > a[j])
        {
            b[k++] = a[j++];
            ans += mid - i + 1;
            ans %= 99999997;
        }
        else
            b[k++] = a[i++];
    }
    while (i <= mid)
        b[k++] = a[i++];
    while (j <= r)
        b[k++] = a[j++];
    for (int i = l; i <= r; i++)
        a[i] = b[i];
}
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &first_team[i].num);
        first_team[i].ord = i;
    }
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &second_team[i].num);
        second_team[i].ord = i;
    }
    sort(first_team + 1, first_team + n + 1, compare);
    sort(second_team + 1, second_team + n + 1, compare);
    for (int i = 1; i <= n; i++)
        a[first_team[i].ord] = second_team[i].ord;
    Merge(1, n);
    printf("%d", ans);
    return 0;
}