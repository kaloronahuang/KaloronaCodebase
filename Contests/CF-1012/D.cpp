// D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e6 + 200;

int n, m, head[2], nxt[MAX_N], siz[MAX_N], len[2], color[MAX_N], ltot, A = 0, B = 1, anstot, ans[MAX_N][2];
char S[MAX_N], T[MAX_N];

int createListNode(int col)
{
    int p = ++ltot;
    color[p] = col, siz[p] = 1;
    return p;
}

void build(char *str, int id)
{
    int p = head[id] = createListNode(str[1] - 'a');
    len[id] = 1;
    for (int i = 2; str[i]; i++)
        if (str[i] == str[i - 1])
            siz[p]++;
        else
            p = nxt[p] = createListNode(str[i] - 'a'), len[id]++;
}

void update_ans(int x, int y) { ans[++anstot][0] = x, ans[anstot][1] = y; }

int f0(int x, int lena, int lenb) { return abs((lena - (x << 1) - 1) - (lenb + (x << 1))); }

int f1(int x, int lena, int lenb) { return abs((lena - (x << 1)) - (lenb + (x << 1) - 2)); }

int f2(int x, int lena, int lenb) { return abs((lena - (x << 1) - 1) - (lenb + (x << 1) - 1)); }

int calc(int id)
{
    int ret = 0;
    for (int i = head[id]; i; i = nxt[i])
        ret++;
    return ret;
}

int main()
{
    scanf("%s%s", S + 1, T + 1), build(S, 0), build(T, 1);
    while (max(len[A], len[B]) > 1)
    {
        if (len[A] < len[B])
            swap(A, B);
        if (color[head[A]] == color[head[B]] && len[B] > 1 && len[A] > 2)
        {
            int lena = len[A], lenb = len[B], x1 = (lena - lenb + 2) >> 2, x2 = x1 + 1;
            int x = max(1, min(f1(x1, lena, lenb) <= f1(x2, lena, lenb) ? x1 : x2, lena >> 1));
            int tot_siz = siz[head[A]], ptr = head[A];
            for (int i = 1; i <= (x << 1) - 1; i++)
                // go to the midpoint;
                ptr = nxt[ptr], tot_siz += siz[ptr];
            update_ans(tot_siz, siz[head[B]]);
            int ptrA = head[A], ptrB = head[B];
            head[A] = nxt[ptr], siz[head[A]] += siz[ptrB];
            head[B] = ptrA, nxt[ptr] = nxt[nxt[ptrB]];
            siz[ptr] += siz[nxt[ptrB]];
            len[A] -= (x << 1), len[B] += (x << 1) - 2;
        }
        else if (color[head[A]] == color[head[B]])
        {
            int lena = len[A], lenb = len[B], x1 = (lena - lenb - 1) >> 2, x2 = x1 + 1;
            int x = min(f0(x1, lena, lenb) <= f0(x2, lena, lenb) ? x1 : x2, (lena - 1) >> 1);
            int tot_siz = siz[head[A]], ptr = head[A];
            for (int i = 1; i <= (x << 1); i++)
                // go to the midpoint;
                ptr = nxt[ptr], tot_siz += siz[ptr];
            update_ans(tot_siz, 0);
            swap(head[B], head[A]), swap(nxt[ptr], head[A]);
            siz[ptr] += siz[nxt[ptr]], nxt[ptr] = nxt[nxt[ptr]];
            len[A] = (len[A] < 3) ? calc(A) : (len[A] - (x << 1 | 1));
            len[B] = (len[B] < 3) ? calc(B) : (len[B] + (x << 1));
        }
        else
        {
            int lena = len[A], lenb = len[B], x1 = (lena - lenb - 1) >> 2, x2 = x1 + 1;
            int x = min(f2(x1, lena, lenb) <= f2(x2, lena, lenb) ? x1 : x2, (lena - 1) >> 1);
            int tot_siz = siz[head[A]], ptr = head[A];
            for (int i = 1; i <= (x << 1); i++)
                // go to the midpoint;
                ptr = nxt[ptr], tot_siz += siz[ptr];
            update_ans(tot_siz, siz[head[B]]);
            siz[head[B]] += siz[nxt[ptr]], siz[ptr] += siz[nxt[head[B]]];
            swap(nxt[head[B]], nxt[ptr]);
            nxt[head[B]] = nxt[nxt[head[B]]], nxt[ptr] = nxt[nxt[ptr]];
            swap(head[B], head[A]);
            len[A] = (len[A] < 3) ? calc(A) : (len[A] - (x << 1 | 1));
            len[B] = (len[B] < 3) ? calc(B) : (len[B] + ((x << 1) - 1));
        }
    }
    printf("%d\n", anstot);
    for (int i = 1; i <= anstot; i++)
        printf("%d %d\n", ans[i][0], ans[i][1]);
    return 0;
}