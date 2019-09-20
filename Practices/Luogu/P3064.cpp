// P3064.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110;

int m, n, seq[MAX_N], current_gang, current_siz, tmp[MAX_N];

void fight(int &gang, int &siz, int new_comer)
{
    if (siz == 0)
        gang = new_comer;
    if (gang == new_comer)
        siz++;
    else
        siz--;
}

int getResult(int gang, int siz)
{
    for (int i = 1; i <= m; i++)
        tmp[i] = seq[i];
    sort(tmp + 2, tmp + 1 + m);
    while (tmp[m])
        for (int i = m; i >= 2; i--)
        {
            fight(gang, siz, i);
            tmp[i]--;
            if (tmp[i] >= tmp[i - 1])
                break;
        }

    for (int i = 1; i <= tmp[1]; i++)
        fight(gang, siz, 1);
    if (gang == 1)
        return siz;
    else
        return 0;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d", &seq[i]);
    int num = getResult(0, 0);
    if (!num)
    {
        puts("NO");
        return 0;
    }
    printf("YES\n%d\n", num);
    for (int i = 1; i <= n; i++)
    {
        int tmp_gang = current_gang;
        int tmp_siz = current_siz;
        for (int j = 1; j <= m; j++)
        {
            if (!seq[j])
                continue;
            seq[j]--;
            fight(current_gang, current_siz, j);
            if (getResult(current_gang, current_siz) == num)
            {
                printf("%d\n", j);
                break;
            }
            seq[j]++;
            current_gang = tmp_gang, current_siz = tmp_siz;
        }
    }
    return 0;
}