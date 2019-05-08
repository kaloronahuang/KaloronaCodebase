// P3810.cpp
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 101000, MAX_R = 201000;

int n, k, answer[MAX_R], tree[MAX_R], mx, tot;
struct element
{
    int a, b, c, weight, ans;
    bool operator<(const element &ele) const
    {
        if (a == ele.a)
            if (b == ele.b)
                return c < ele.c;
            else
                return b < ele.b;
        else
            return a < ele.a;
    }
} elements[MAX_N], elements_src[MAX_N];

bool compare_y(const element &A, const element &B)
{
    if (A.b == B.b)
        return A.c < B.c;
    else
        return A.b < B.b;
}
inline int lowbit(int x) { return x & (-x); }

void update(int x, int d)
{
    while (x <= k)
        tree[x] += d, x += lowbit(x);
}

int sum(int x)
{
    int ans = 0;
    while (x)
        ans += tree[x], x -= lowbit(x);
    return ans;
}

void cdq(int l, int r)
{
    int mid = (l + r) >> 1;
    if (l == r)
        return;
    cdq(l, mid), cdq(mid + 1, r);
    sort(elements + l, elements + 1 + mid, compare_y);
    sort(elements + mid + 1, elements + r + 1, compare_y);
    int ptr1 = l;
    for (int ptr2 = mid + 1; ptr2 <= r; ptr2++)
    {
        while (elements[ptr1].b <= elements[ptr2].b && ptr1 <= mid)
            update(elements[ptr1].c, elements[ptr1].weight), ptr1++;
        elements[ptr2].ans += sum(elements[ptr2].c);
    }
    for (int i = l; i < ptr1; i++)
        update(elements[i].c, -elements[i].weight);
}

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d%d%d", &elements_src[i].a, &elements_src[i].b, &elements_src[i].c);
    sort(elements_src + 1, elements_src + 1 + n);
    int c = 0;
    for (int i = 1; i <= n; i++)
    {
        c++;
        if (elements_src[i].a != elements_src[i + 1].a || elements_src[i].b != elements_src[i + 1].b || elements_src[i].c != elements_src[i + 1].c)
            elements[++tot] = elements_src[i], elements[tot].weight = c, c = 0;
    }
    cdq(1, tot);
    for (int i = 1; i <= tot; i++)
        answer[elements[i].ans + elements[i].weight - 1] += elements[i].weight;
    for (int i = 0; i < n; i++)
        printf("%d\n", answer[i]);
    return 0;
}