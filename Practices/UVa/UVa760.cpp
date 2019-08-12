// UVa760.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3300;

int sa[MAX_N], height[MAX_N], rk[MAX_N], sc[MAX_N], bucket[MAX_N], wordset = 30, n, tag[MAX_N];
char str[MAX_N], str2[MAX_N];

void bucketSort()
{
    for (int i = 0; i <= wordset; i++)
        bucket[i] = 0;
    for (int i = 1; i <= n; i++)
        bucket[rk[i]]++;
    for (int i = 1; i <= wordset; i++)
        bucket[i] += bucket[i - 1];
    for (int i = n; i >= 1; i--)
        sa[bucket[rk[sc[i]]]--] = sc[i];
}

void suffixSort()
{
    for (int i = 1; i <= n; i++)
        rk[i] = str[i] - 'a' + 1, sc[i] = i;
    bucketSort();
    for (int step = 1, p = 0; p < n; wordset = p, step <<= 1)
    {
        p = 0;
        for (int i = n - step + 1; i <= n; i++)
            sc[++p] = i;
        for (int i = 1; i <= n; i++)
            if (sa[i] > step)
                sc[++p] = sa[i] - step;
        bucketSort();
        swap(rk, sc);
        rk[sa[1]] = p = 1;
        for (int i = 2; i <= n; i++)
            rk[sa[i]] = (sc[sa[i]] == sc[sa[i - 1]] && sc[sa[i] + step] == sc[sa[i - 1] + step]) ? p : ++p;
    }

    int k = 0;
    for (int i = 1; i <= n; i++)
    {
        if (k != 0)
            k--;
        int j = sa[rk[i] - 1];
        while (str[i + k] == str[j + k])
            k++;
        height[rk[i]] = k;
    }
}

int main()
{
    int ca = 0;
    while (scanf("%s%s", str + 1, str2 + 1) != EOF)
    {
        if (ca)
            puts("");
        ca++;
        memset(tag, 0, sizeof(tag));

        int m = strlen(str2 + 1);
        n = strlen(str + 1);

        for (int i = 1; i <= n; i++)
            tag[i] = 1;
        str[++n] = 'z' + 1;
        for (int i = 1; i <= m; i++)
            tag[++n] = 2, str[n] = str2[i];
        str[++n] = 'a' - 1;
        wordset = 30, suffixSort();

        int max_len = 0;
        for (int i = 1; i <= n; i++)
            if (tag[sa[i - 1]] + tag[sa[i]] == 3)
                max_len = max(max_len, height[i]);

        if (max_len == 0)
            puts("No common sequence.");
        else
        {
            vector<int> stpos;
            set<int> container;
            for (int i = 1, lastpos; i <= n; i++)
                if (height[i] >= max_len)
                    lastpos = sa[i], container.insert(tag[sa[i]]), container.insert(tag[sa[i - 1]]);
                else
                {
                    if (container.size() == 2)
                        stpos.push_back(lastpos);
                    container.clear();
                }

            for (int i = 0; i < stpos.size(); i++)
            {
                for (int st = stpos[i]; st < stpos[i] + max_len; st++)
                    printf("%c", str[st]);
                printf("\n");
            }
        }
    }
    return 0;
}